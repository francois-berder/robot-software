#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include <blocking_uart_driver.h>
#include "motor_pwm.h"

BlockingUARTDriver blocking_uart_stream;
BaseSequentialStream* stderr = (BaseSequentialStream*)&blocking_uart_stream;
BaseSequentialStream* stdout;


#define ADC_MAX         4096
#define ADC_TO_AMPS     0.001611328125f
#define ADC_TO_VOLTS    0.005283043033f

static THD_WORKING_AREA(quad_task_wa, 128);
static THD_FUNCTION(quad_task, arg)
{
    (void)arg;
    chRegSetThreadName("encoder read");
    rccEnableTIM4(FALSE);           // enable timer 4
    rccResetTIM4();
    STM32_TIM4->CR2    = 0;
    STM32_TIM4->PSC    = 0;                         // Prescaler value.
    STM32_TIM4->SR     = 0;                         // Clear pending IRQs.
    STM32_TIM4->DIER   = 0;                         // DMA-related DIER bits.
    STM32_TIM4->SMCR   = STM32_TIM_SMCR_SMS(3);     // count on both edges
    STM32_TIM4->CCMR1  = STM32_TIM_CCMR1_CC1S(1);   // CC1 channel is input, IC1 is mapped on TI1
    STM32_TIM4->CCMR1 |= STM32_TIM_CCMR1_CC2S(1);   // CC2 channel is input, IC2 is mapped on TI2
    STM32_TIM4->CCER   = 0;
    STM32_TIM4->ARR    = 0xFFFF;
    STM32_TIM4->CR1    = 1;                         // start

    while(42){
        chThdSleepMilliseconds(100);
    }
    return 0;
}

static THD_WORKING_AREA(ext_quad_task_wa, 128);
static THD_FUNCTION(ext_quad_task, arg)
{
    (void)arg;
    chRegSetThreadName("external encoder read");
    palSetPadMode(GPIOB, GPIOB_GPIO_A, PAL_MODE_ALTERNATE(2));
    palSetPadMode(GPIOB, GPIOB_GPIO_B, PAL_MODE_ALTERNATE(2));

    rccEnableTIM3(FALSE);           // enable timer 3
    rccResetTIM3();
    STM32_TIM3->CR2    = 0;
    STM32_TIM3->PSC    = 0;                         // Prescaler value.
    STM32_TIM3->SR     = 0;                         // Clear pending IRQs.
    STM32_TIM3->DIER   = 0;                         // DMA-related DIER bits.
    STM32_TIM3->SMCR   = STM32_TIM_SMCR_SMS(3);     // count on both edges
    STM32_TIM3->CCMR1  = STM32_TIM_CCMR1_CC1S(1);   // CC1 channel is input, IC1 is mapped on TI1
    STM32_TIM3->CCMR1 |= STM32_TIM_CCMR1_CC2S(1);   // CC2 channel is input, IC2 is mapped on TI2
    STM32_TIM3->CCER   = 0;
    STM32_TIM3->ARR    = 0xFFFF;
    STM32_TIM3->CR1    = 1;                         // start

    while(42){
        chThdSleepMilliseconds(100);
    }
    return 0;
}


static THD_WORKING_AREA(adc_task_wa, 256);
static THD_FUNCTION(adc_task, arg)
{
    (void)arg;
    chRegSetThreadName("adc read");
    static adcsample_t adc_samples[4];
    static const ADCConversionGroup adcgrpcfg1 = {
        FALSE,                  // circular?
        4,                      // nb channels
        NULL,                   // callback fn
        NULL,                   // error callback fn
        0,                      // CFGR
        0,                      // TR1
        6,                      // CCR : DUAL=regualar,simultaneous
        {ADC_SMPR1_SMP_AN1(0), 0},                          // SMPRx : sample time minimum
        {ADC_SQR1_NUM_CH(2) | ADC_SQR1_SQ1_N(1) | ADC_SQR1_SQ2_N(1), 0, 0, 0}, // SQRx : ADC1_CH1 2x
        {ADC_SMPR1_SMP_AN2(0) | ADC_SMPR1_SMP_AN3(0), 0},   // SSMPRx : sample time minimum
        {ADC_SQR1_NUM_CH(2) | ADC_SQR1_SQ1_N(2) | ADC_SQR1_SQ2_N(3), 0, 0, 0}, // SSQRx : ADC2_CH2, ADC2_CH3
    };

    while (1) {
        int i;
        float mean_current = 0.0f;
        for(i = 0; i < 1000; i++){
            adcConvert(&ADCD1, &adcgrpcfg1, adc_samples, 1);
            mean_current += (adc_samples[1]-ADC_MAX/2)*ADC_TO_AMPS;
        }
        mean_current /= 1000;

        chprintf(stdout, "%f A\n", mean_current);
        chThdSleepMilliseconds(100);
    }
    return 0;
}

void panic_hook(const char* reason)
{
    palClearPad(GPIOA, GPIOA_LED);      // turn on LED (active low)
    blocking_uart_init(&blocking_uart_stream, USART3, 115200);
    int i;
    while(42){
        for(i = 10000000; i>0; i--){
            __asm__ volatile ("nop");
        }
        chprintf(stderr, "%s\n", reason);
    }
}


int main(void) {
    halInit();
    chSysInit();


    sdStart(&SD3, NULL);
    stdout = (BaseSequentialStream*)&SD3;

    motor_pwm_setup();
    motor_pwm_enable();
    motor_pwm_set(0.0);

    adcStart(&ADCD1, NULL);

    chprintf(stdout, "boot\n");

    chThdCreateStatic(adc_task_wa, sizeof(adc_task_wa), LOWPRIO, adc_task, NULL);
    chThdCreateStatic(quad_task_wa, sizeof(quad_task_wa), LOWPRIO, quad_task, NULL);
    chThdCreateStatic(ext_quad_task_wa, sizeof(ext_quad_task_wa), LOWPRIO, ext_quad_task, NULL);

    while (1) {
        palSetPad(GPIOA, GPIOA_LED);
        motor_pwm_set(-0.2);
        chThdSleepMilliseconds(1000);
        palClearPad(GPIOA, GPIOA_LED);
        motor_pwm_set(0.2);
        chThdSleepMilliseconds(1000);
    }
}

#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_NB_MOTOR_DRIVERS            20
#define MAX_NB_BUS_ENUMERATOR_ENTRIES   21

#include "motor_manager.h"
#include "msgbus/messagebus.h"

/** Robot wide interthread bus. */
extern messagebus_t bus;

extern motor_manager_t motor_manager;

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H */

#ifndef _GFXCONF_H
#define _GFXCONF_H

///////////////////////////////////////////////////////////////////////////
// GDISP                                                                 //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GDISP GFXON
#define GDISP_NEED_VALIDATION GFXON
#define GDISP_NEED_CLIP GFXON
#define GDISP_NEED_CONTROL GFXON
#define GDISP_NEED_MULTITHREAD GFXON
#define GDISP_NEED_TEXT GFXON
#define GDISP_INCLUDE_FONT_DEJAVUSANS12 GFXON
#define GDISP_INCLUDE_FONT_DEJAVUSANS32 GFXON
//    #define GDISP_INCLUDE_FONT_DEJAVUSANSBOLD12      GFXOFF
//    #define GDISP_INCLUDE_FONT_FIXED_10X20           GFXOFF
//    #define GDISP_INCLUDE_FONT_FIXED_7X14            GFXOFF
//    #define GDISP_INCLUDE_FONT_FIXED_5X8             GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS12_AA       GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS16_AA       GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS20_AA       GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS24_AA       GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANS32_AA       GFXOFF
//    #define GDISP_INCLUDE_FONT_DEJAVUSANSBOLD12_AA   GFXOFF
//    #define GDISP_INCLUDE_USER_FONTS                 GFXOFF

// #define GDISP_NEED_PIXMAP                            GFXOFF
//    #define GDISP_NEED_PIXMAP_IMAGE                  GFXOFF

#define GDISP_NEED_CONVEX_POLYGON GFXON
#define GDISP_DEFAULT_ORIENTATION GDISP_ROTATE_270
// #define GDISP_LINEBUF_SIZE                           128
// #define GDISP_STARTUP_COLOR                          Black
#define GDISP_NEED_STARTUP_LOGO GFXON

///////////////////////////////////////////////////////////////////////////
// GWIN                                                                  //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GWIN GFXON

#define GWIN_NEED_WINDOWMANAGER GFXON
#define GWIN_NEED_CONSOLE GFXON
//    #define GWIN_CONSOLE_USE_HISTORY                 GFXOFF
//        #define GWIN_CONSOLE_HISTORY_AVERAGING       GFXOFF
//        #define GWIN_CONSOLE_HISTORY_ATCREATE        GFXOFF
#define GWIN_CONSOLE_ESCSEQ GFXON
//    #define GWIN_CONSOLE_USE_BASESTREAM              GFXOFF
//    #define GWIN_CONSOLE_USE_FLOAT                   GFXOFF
// #define GWIN_NEED_GRAPH                              GFXOFF
// #define GWIN_NEED_GL3D                               GFXOFF

#define GWIN_NEED_WIDGET GFXON
// #define GWIN_FOCUS_HIGHLIGHT_WIDTH                   1
#define GWIN_NEED_LABEL GFXON
#define GWIN_NEED_BUTTON GFXON
//        #define GWIN_BUTTON_LAZY_RELEASE             GFXOFF
#define GWIN_NEED_SLIDER GFXON
#define GWIN_SLIDER_NOSNAP GFXON
//        #define GWIN_SLIDER_DEAD_BAND                5
//        #define GWIN_SLIDER_TOGGLE_INC               20
#define GWIN_NEED_CHECKBOX GFXON
//    #define GWIN_NEED_RADIO                          GFXOFF
//    #define GWIN_NEED_PROGRESSBAR                    GFXOFF
//        #define GWIN_PROGRESSBAR_AUTO                GFXOFF
//    #define GWIN_FLAT_STYLING GFXON
//    #define GWIN_WIDGET_TAGS                         GFXOFF

#define GWIN_NEED_CONTAINERS GFXON
#define GWIN_NEED_CONTAINER GFXON
//    #define GWIN_NEED_FRAME                          GFXOFF
//    #define GWIN_NEED_TABSET                         GFXOFF
//        #define GWIN_TABSET_TABHEIGHT                18

#define GWIN_REDRAW_IMMEDIATE GFXON


///////////////////////////////////////////////////////////////////////////
// GEVENT                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GEVENT GFXON

// #define GEVENT_ASSERT_NO_RESOURCE                    GFXOFF
// #define GEVENT_MAXIMUM_SIZE                          32
// #define GEVENT_MAX_SOURCE_LISTENERS                  32

///////////////////////////////////////////////////////////////////////////
// GTIMER                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GTIMER GFXON

#define GTIMER_THREAD_PRIORITY 1
#define GTIMER_THREAD_WORKAREA_SIZE 2048

///////////////////////////////////////////////////////////////////////////
// GQUEUE                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GQUEUE GFXON

#define GQUEUE_NEED_ASYNC GFXON
// #define GQUEUE_NEED_GSYNC                            GFXOFF
// #define GQUEUE_NEED_FSYNC                            GFXOFF
// #define GQUEUE_NEED_BUFFERS                          GFXOFF

///////////////////////////////////////////////////////////////////////////
// GINPUT                                                                //
///////////////////////////////////////////////////////////////////////////
#define GFX_USE_GINPUT GFXON

#define GINPUT_NEED_MOUSE GFXON
#define GINPUT_TOUCH_STARTRAW GFXOFF
//    #define GINPUT_TOUCH_NOTOUCH                     GFXOFF
//    #define GINPUT_TOUCH_NOCALIBRATE                 GFXON
//    #define GINPUT_TOUCH_NOCALIBRATE_GUI             GFXOFF
//    #define GINPUT_MOUSE_POLL_PERIOD                 25
//    #define GINPUT_MOUSE_CLICK_TIME                  300
//    #define GINPUT_TOUCH_CXTCLICK_TIME               700
#define GINPUT_TOUCH_USER_CALIBRATION_LOAD GFXOFF
#define GINPUT_TOUCH_USER_CALIBRATION_SAVE GFXOFF
//    #define GMOUSE_DRIVER_LIST                       GMOUSEVMT_Win32, GMOUSEVMT_Win32
// #define GINPUT_NEED_TOGGLE                           GFXOFF
// #define GINPUT_NEED_DIAL                             GFXOFF

///////////////////////////////////////////////////////////////////////////
// GADC                                                                  //
///////////////////////////////////////////////////////////////////////////
// #define GFX_USE_GADC                                 GFXOFF
//    #define GADC_MAX_LOWSPEED_DEVICES                4
#define GOS_NEED_X_THREADS GFXOFF
#define GOX_NEED_X_HEAP GFXOFF

#define SCREEN_WIDTH GDISP_SCREEN_WIDTH
#define SCREEN_HEIGHT GDISP_SCREEN_HEIGHT


#define GFX_COMPAT_V2 GFXOFF
#endif /* _GFXCONF_H */

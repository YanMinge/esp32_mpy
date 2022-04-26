#ifndef _MT_MODULE_CONFIG_H_
#define _MT_MODULE_CONFIG_H_

/* common items */
#define MT_MODULE_NOT_INITIALIZE                 (0x00)
#define MT_MODULE_INITIALIZED                    (0x01)
#define MT_MODULE_DEINITIALIZED                  (0x02)
#define MT_MODULE_FATAL_ERROR                    (0xff)

typedef int32_t mt_module_status_t;


#define MODULE_DRIVER_ENABLE                     1
#if MODULE_DRIVER_ENABLE
    #define MODULE_BUTTON_ENABLE                 1
    // #define MODULE_GYRO_ENABLE                   1
    // #define MODULE_LEDMATRIX_ENABLE              1
    // #define MODULE_TOUCHPAD_ENABLE               1
    // #define MODULE_VIBRATION_MOTOR_ENABLE        1
    // #define MODULE_PIN_ENABLE                    1
    // #define MODULE_POWER_BOARD_CHECK_ENABLE      1
    // #define MODULE_CLOCK_ENABLE                  1
#endif

/*
 * event mechanism
 */
#define MODULE_BUTTON_ENABLE                 1
#define MODULE_EVENT_ENABLE                  1
#define MODULE_GYRO_ENABLE                   1
#define MODULE_TOF_ENABLE                    0
#define MODULE_LIGHT_SENSOR_ENABLE           1
/* module slect */
/*
 * driver
 */
//#define MODULE_LEDS_ENABLE                     1
//#define MODULE_MOTION_ENABLE                   1

#endif
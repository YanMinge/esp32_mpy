// Options to control how MicroPython is built for this port,
// overriding defaults in py/mpconfig.h.

// Board-specific definitions
#include "mpconfigboard.h"

#include <stdint.h>
#include <alloca.h>
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "driver/i2s.h"

#ifndef MICROPY_CONFIG_ROM_LEVEL
#define MICROPY_CONFIG_ROM_LEVEL            (MICROPY_CONFIG_ROM_LEVEL_EXTRA_FEATURES)
#endif

// object representation and NLR handling
#define MICROPY_OBJ_REPR                    (MICROPY_OBJ_REPR_A)
#define MICROPY_NLR_SETJMP                  (1)
#if CONFIG_IDF_TARGET_ESP32C3
#define MICROPY_GCREGS_SETJMP               (1)
#endif

// memory allocation policies
#define MICROPY_ALLOC_PATH_MAX              (128)

// emitters
#define MICROPY_PERSISTENT_CODE_LOAD        (1)
#if !CONFIG_IDF_TARGET_ESP32C3
#define MICROPY_EMIT_XTENSAWIN              (1)
#endif

// optimisations
#define MICROPY_OPT_COMPUTED_GOTO           (1)

// Python internal features
#define MICROPY_READER_VFS                  (1)
#define MICROPY_ENABLE_GC                   (1)
#define MICROPY_ENABLE_EMERGENCY_EXCEPTION_BUF (1)
#define MICROPY_LONGINT_IMPL                (MICROPY_LONGINT_IMPL_MPZ)
#define MICROPY_ERROR_REPORTING             (MICROPY_ERROR_REPORTING_NORMAL)
#define MICROPY_WARNINGS                    (1)
#define MICROPY_FLOAT_IMPL                  (MICROPY_FLOAT_IMPL_FLOAT)
#define MICROPY_STREAMS_POSIX_API           (1)
#define MICROPY_MODULE_FROZEN_STR           (0)
#define MICROPY_MODULE_FROZEN_MPY           (1)
#define MICROPY_QSTR_EXTRA_POOL             mp_qstr_frozen_const_pool
#define MICROPY_USE_INTERNAL_ERRNO          (0) // errno.h from xtensa-esp32-elf/sys-include/sys
#define MICROPY_USE_INTERNAL_PRINTF         (0) // ESP32 SDK requires its own printf
#define MICROPY_SCHEDULER_DEPTH             (8)
#define MICROPY_VFS                         (1)

// control over Python builtins
#define MICROPY_PY_STR_BYTES_CMP_WARN       (1)
#define MICROPY_PY_ALL_INPLACE_SPECIAL_METHODS (1)
#define MICROPY_PY_BUILTINS_HELP_TEXT       esp32_help_text
#define MICROPY_PY_IO_BUFFEREDWRITER        (1)
#define MICROPY_PY_UTIME_MP_HAL             (1)
#define MICROPY_PY_THREAD                   (1)
#define MICROPY_PY_THREAD_GIL               (1)
#define MICROPY_PY_THREAD_GIL_VM_DIVISOR    (32)

// extended modules
#ifndef MICROPY_PY_BLUETOOTH
#define MICROPY_PY_BLUETOOTH                (0)
#define MICROPY_PY_BLUETOOTH_ENABLE_CENTRAL_MODE (0)
#define MICROPY_BLUETOOTH_NIMBLE            (0)
#define MICROPY_BLUETOOTH_NIMBLE_BINDINGS_ONLY (0)
#endif
#define MICROPY_PY_UTIMEQ                   (1)
#define MICROPY_PY_UHASHLIB_SHA1            (1)
#define MICROPY_PY_UHASHLIB_SHA256          (1)
#define MICROPY_PY_UCRYPTOLIB               (1)
#define MICROPY_PY_URANDOM_SEED_INIT_FUNC   (esp_random())
#define MICROPY_PY_OS_DUPTERM               (1)
#define MICROPY_PY_MACHINE                  (1)
#define MICROPY_PY_MACHINE_PIN_MAKE_NEW     mp_pin_make_new
#define MICROPY_PY_MACHINE_BITSTREAM        (1)
#define MICROPY_PY_MACHINE_PULSE            (1)
#define MICROPY_PY_MACHINE_PWM              (1)
#define MICROPY_PY_MACHINE_PWM_INIT         (1)
#define MICROPY_PY_MACHINE_PWM_DUTY         (1)
#define MICROPY_PY_MACHINE_PWM_DUTY_U16_NS  (1)
#define MICROPY_PY_MACHINE_PWM_INCLUDEFILE  "ports/esp32/machine_pwm.c"
#define MICROPY_PY_MACHINE_I2C              (1)
#define MICROPY_PY_MACHINE_SOFTI2C          (1)
#define MICROPY_PY_MACHINE_SPI              (1)
#define MICROPY_PY_MACHINE_SPI_MSB          (0)
#define MICROPY_PY_MACHINE_SPI_LSB          (1)
#define MICROPY_PY_MACHINE_SOFTSPI          (1)
#ifndef MICROPY_PY_MACHINE_DAC
#define MICROPY_PY_MACHINE_DAC              (1)
#endif
#ifndef MICROPY_PY_MACHINE_I2S
#define MICROPY_PY_MACHINE_I2S              (1)
#endif
#ifndef MICROPY_PY_NETWORK_WLAN
#define MICROPY_PY_NETWORK_WLAN             (1)
#endif
#ifndef MICROPY_HW_ENABLE_SDCARD
#define MICROPY_HW_ENABLE_SDCARD            (1)
#endif
#define MICROPY_HW_SOFTSPI_MIN_DELAY        (0)
#define MICROPY_HW_SOFTSPI_MAX_BAUDRATE     (ets_get_cpu_frequency() * 1000000 / 200) // roughly
#define MICROPY_PY_USSL                     (1)
#define MICROPY_SSL_MBEDTLS                 (1)
#define MICROPY_PY_USSL_FINALISER           (1)
#define MICROPY_PY_UWEBSOCKET               (1)
#define MICROPY_PY_WEBREPL                  (1)
#define MICROPY_PY_BTREE                    (1)
#define MICROPY_PY_ONEWIRE                  (1)
#define MICROPY_PY_UPLATFORM                (1)
#define MICROPY_PY_USOCKET_EVENTS           (MICROPY_PY_WEBREPL)
#define MICROPY_PY_BLUETOOTH_RANDOM_ADDR    (1)
#define MICROPY_PY_BLUETOOTH_DEFAULT_GAP_NAME ("ESP32")

// fatfs configuration
#define MICROPY_FATFS_ENABLE_LFN            (1)
#define MICROPY_FATFS_RPATH                 (2)
#define MICROPY_FATFS_MAX_SS                (4096)
#define MICROPY_FATFS_LFN_CODE_PAGE         437 /* 1=SFN/ANSI 437=LFN/U.S.(OEM) */
#define mp_type_fileio                      mp_type_vfs_fat_fileio
#define mp_type_textio                      mp_type_vfs_fat_textio

// use vfs's functions for import stat and builtin open
#define mp_import_stat mp_vfs_import_stat
#define mp_builtin_open mp_vfs_open
#define mp_builtin_open_obj mp_vfs_open_obj

// extra built in names to add to the global namespace
#define MICROPY_PORT_BUILTINS \
    { MP_OBJ_NEW_QSTR(MP_QSTR_input), (mp_obj_t)&mp_builtin_input_obj }, \
    { MP_OBJ_NEW_QSTR(MP_QSTR_open), (mp_obj_t)&mp_builtin_open_obj },

// extra built in modules to add to the list of known ones
extern const struct _mp_obj_module_t esp_module;
extern const struct _mp_obj_module_t esp32_module;
extern const struct _mp_obj_module_t utime_module;
extern const struct _mp_obj_module_t uos_module;
extern const struct _mp_obj_module_t mp_module_usocket;
extern const struct _mp_obj_module_t mp_module_network;
extern const struct _mp_obj_module_t mp_module_onewire;

#define MICROPY_PORT_BUILTIN_MODULES \
    { MP_OBJ_NEW_QSTR(MP_QSTR_esp), (mp_obj_t)&esp_module }, \
    { MP_OBJ_NEW_QSTR(MP_QSTR_esp32), (mp_obj_t)&esp32_module }, \
    { MP_OBJ_NEW_QSTR(MP_QSTR_utime), (mp_obj_t)&utime_module }, \
    { MP_OBJ_NEW_QSTR(MP_QSTR_uos), (mp_obj_t)&uos_module }, \
    { MP_OBJ_NEW_QSTR(MP_QSTR_usocket), (mp_obj_t)&mp_module_usocket }, \
    { MP_OBJ_NEW_QSTR(MP_QSTR_network), (mp_obj_t)&mp_module_network }, \
    { MP_OBJ_NEW_QSTR(MP_QSTR__onewire), (mp_obj_t)&mp_module_onewire }, \

#define MP_STATE_PORT MP_STATE_VM

struct _machine_timer_obj_t;

#if MICROPY_BLUETOOTH_NIMBLE
struct mp_bluetooth_nimble_root_pointers_t;
#define MICROPY_PORT_ROOT_POINTER_BLUETOOTH_NIMBLE struct _mp_bluetooth_nimble_root_pointers_t *bluetooth_nimble_root_pointers;
#else
#define MICROPY_PORT_ROOT_POINTER_BLUETOOTH_NIMBLE
#endif

#define MICROPY_PORT_ROOT_POINTERS \
    const char *readline_hist[8]; \
    mp_obj_t machine_pin_irq_handler[40]; \
    struct _machine_timer_obj_t *machine_timer_obj_head; \
    struct _machine_i2s_obj_t *machine_i2s_obj[I2S_NUM_MAX]; \
    MICROPY_PORT_ROOT_POINTER_BLUETOOTH_NIMBLE

// type definitions for the specific machine

#define MICROPY_MAKE_POINTER_CALLABLE(p) ((void *)((mp_uint_t)(p)))
void *esp_native_code_commit(void *, size_t, void *);
#define MP_PLAT_COMMIT_EXEC(buf, len, reloc) esp_native_code_commit(buf, len, reloc)
#define MP_SSIZE_MAX (0x7fffffff)

// Note: these "critical nested" macros do not ensure cross-CPU exclusion,
// the only disable interrupts on the current CPU.  To full manage exclusion
// one should use portENTER_CRITICAL/portEXIT_CRITICAL instead.
#include "freertos/FreeRTOS.h"
#define MICROPY_BEGIN_ATOMIC_SECTION() portENTER_CRITICAL_NESTED()
#define MICROPY_END_ATOMIC_SECTION(state) portEXIT_CRITICAL_NESTED(state)

#if MICROPY_PY_USOCKET_EVENTS
#define MICROPY_PY_USOCKET_EVENTS_HANDLER extern void usocket_events_handler(void); usocket_events_handler();
#else
#define MICROPY_PY_USOCKET_EVENTS_HANDLER
#endif

#if MICROPY_PY_THREAD
#define MICROPY_EVENT_POLL_HOOK \
    do { \
        extern void mp_handle_pending(bool); \
        mp_handle_pending(true); \
        MICROPY_PY_USOCKET_EVENTS_HANDLER \
        MP_THREAD_GIL_EXIT(); \
        ulTaskNotifyTake(pdFALSE, 1); \
        MP_THREAD_GIL_ENTER(); \
    } while (0);
#else
#define MICROPY_EVENT_POLL_HOOK \
    do { \
        extern void mp_handle_pending(bool); \
        mp_handle_pending(true); \
        MICROPY_PY_USOCKET_EVENTS_HANDLER \
        asm ("waiti 0"); \
    } while (0);
#endif

// Functions that should go in IRAM
#define MICROPY_WRAP_MP_BINARY_OP(f) IRAM_ATTR f
#define MICROPY_WRAP_MP_EXECUTE_BYTECODE(f) IRAM_ATTR f
#define MICROPY_WRAP_MP_LOAD_GLOBAL(f) IRAM_ATTR f
#define MICROPY_WRAP_MP_LOAD_NAME(f) IRAM_ATTR f
#define MICROPY_WRAP_MP_MAP_LOOKUP(f) IRAM_ATTR f
#define MICROPY_WRAP_MP_OBJ_GET_TYPE(f) IRAM_ATTR f
#define MICROPY_WRAP_MP_SCHED_EXCEPTION(f) IRAM_ATTR f
#define MICROPY_WRAP_MP_SCHED_KEYBOARD_INTERRUPT(f) IRAM_ATTR f

#define UINT_FMT "%u"
#define INT_FMT "%d"

typedef int32_t mp_int_t; // must be pointer size
typedef uint32_t mp_uint_t; // must be pointer size
typedef long mp_off_t;
// ssize_t, off_t as required by POSIX-signatured functions in stream.h
#include <sys/types.h>

// board specifics
#define MICROPY_PY_SYS_PLATFORM "esp32"

// ESP32-S3 extended IO for 47 & 48
#ifndef MICROPY_HW_ESP32S3_EXTENDED_IO
#define MICROPY_HW_ESP32S3_EXTENDED_IO      (1)
#endif

#ifndef MICROPY_HW_ENABLE_MDNS_QUERIES
#define MICROPY_HW_ENABLE_MDNS_QUERIES      (1)
#endif

#ifndef MICROPY_HW_ENABLE_MDNS_RESPONDER
#define MICROPY_HW_ENABLE_MDNS_RESPONDER    (1)
#endif

#ifndef MICROPY_BOARD_STARTUP
#define MICROPY_BOARD_STARTUP boardctrl_startup
#endif

void boardctrl_startup(void);
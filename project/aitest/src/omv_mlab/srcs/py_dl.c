/*
 * This file is part of the OpenMV project.
 *
 * Copyright (c) 2013-2021 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * Copyright (c) 2013-2021 Kwabena W. Agyeman <kwagyeman@openmv.io>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * Sensor Python module.
 */
#include <stdarg.h>
#include "py/mphal.h"
#include "py/runtime.h"
//#include "pin.h"

//#if MICROPY_PY_SENSOR

//#include "cambus.h"
#include "omv_sensor.h"
#include "imlib.h"
#include "xalloc.h"
#include "py_assert.h"
#include "py_image.h"
#if MICROPY_PY_IMU
#include "py_imu.h"
#endif
#include "omv_boardconfig.h"
#include "py_helper.h"
#include "framebuffer.h"

#include "py_dl.h"

//extern omv_sensor_t sensor;
//static mp_obj_t vsync_callback = mp_const_none;

STATIC MP_DEFINE_CONST_FUN_OBJ_1(py_dl_test_obj,          py_dl_test);
STATIC MP_DEFINE_CONST_FUN_OBJ_KW(py_dl_detect_obj, 1, py_dl_detect);

STATIC const mp_map_elem_t globals_dict_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__),            MP_OBJ_NEW_QSTR(MP_QSTR_dl)},

    { MP_OBJ_NEW_QSTR(MP_QSTR_test),          (mp_obj_t)&py_dl_test_obj },
    //{MP_ROM_QSTR(MP_QSTR_to_bytes),            MP_ROM_PTR(&py_image_to_bytes_obj)},
    {MP_ROM_QSTR(MP_QSTR_detect),            MP_ROM_PTR(&py_dl_detect_obj)}
};

STATIC MP_DEFINE_CONST_DICT(globals_dict, globals_dict_table);

const mp_obj_module_t dl_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_t)&globals_dict,
};

//#endif // MICROPY_PY_SENSOR

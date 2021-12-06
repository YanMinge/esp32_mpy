#include "image.hpp"
#include "human_face_detect_msr01.hpp"
#include "human_face_detect_mnp01.hpp"
#include "dl_tool.hpp"
//#include "imlib.h"


extern "C" {
#include <py_dl.h>

//#include "imlib.h"

/*
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <arm_math.h>
#include "py/nlr.h"
#include "py/obj.h"
#include "py/objlist.h"
#include "py/objstr.h"
#include "py/objtuple.h"
#include "py/objtype.h"
#include "py/objarray.h"
#include "py/runtime.h"
#include "py/mphal.h"
#include "py/binary.h"

#include "imlib.h"
#include "array.h"
#include "ff_wrapper.h"
#include "xalloc.h"
#include "fb_alloc.h"
#include "framebuffer.h"
#include "py_assert.h"
#include "py_helper.h"
#include "py_image.h"
#include "omv_boardconfig.h"
#if defined(IMLIB_ENABLE_IMAGE_IO)
#include "py_imageio.h"
#endif
//*/

typedef struct image {
    int w;
    int h;
    int bpp;
    union {
        uint8_t *pixels;
        uint8_t *data;
    };
} image_t;

typedef enum image_bpp
{
    IMAGE_BPP_BINARY,       // BPP = 0
    IMAGE_BPP_GRAYSCALE,    // BPP = 1
    IMAGE_BPP_RGB565,       // BPP = 2
    IMAGE_BPP_BAYER,        // BPP = 3
    IMAGE_BPP_JPEG          // BPP > 3
}
image_bpp_t;

extern void *py_image_cobj(mp_obj_t img_obj);
mp_obj_t py_dl_test(mp_obj_t enable)
{
    //sensor_set_ir_led(mp_obj_is_true(enable));
    ESP_LOGI("PY_DL", "PY_DL Test!");
    return mp_const_none;
}

#define TWO_STAGE 0 /*<! 1: detect by two-stage which is more accurate but slower(with keypoints). */
                    /*<! 0: detect by one-stage which is less accurate but faster(without keypoints). */
/*
void *py_image_cobj(mp_obj_t img_obj)
{
    PY_ASSERT_TYPE(img_obj, &py_image_type);
    return &((py_image_obj_t *)img_obj)->_cobj;
}
*/
mp_obj_t py_dl_detect(size_t n_args, const mp_obj_t *args, mp_map_t *kw_args)
{
    //image_t *arg_img = py_image_cobj(args[0]);
    //mp_uint_t size = 0;
    /*
    switch(arg_img->bpp) {
        case IMAGE_BPP_BINARY: {
            //size = ((arg_img->w + UINT32_T_MASK) >> UINT32_T_SHIFT) * arg_img->h;
            break;
        }
        case IMAGE_BPP_GRAYSCALE: {
            size = (arg_img->w * arg_img->h) * sizeof(uint8_t);
            break;
        }
        case IMAGE_BPP_RGB565: {
            size = (arg_img->w * arg_img->h) * sizeof(uint16_t);
            break;
        }
        default: {
            size = arg_img->bpp;
            }
            break;
    }
    //*/
    dl::tool::Latency latency;

    // initialize
#if TWO_STAGE
    HumanFaceDetectMSR01 s1(0.1F, 0.5F, 10, 0.2F);
    HumanFaceDetectMNP01 s2(0.5F, 0.3F, 5);
#else // ONE_STAGE
    HumanFaceDetectMSR01 s1(0.3F, 0.5F, 10, 0.2F);
#endif

    // inference
    latency.start();
#if TWO_STAGE
    std::list<dl::detect::result_t> &candidates = s1.infer((uint8_t *)IMAGE_ELEMENT, {IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_CHANNEL});
    std::list<dl::detect::result_t> &results = s2.infer((uint8_t *)IMAGE_ELEMENT, {IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_CHANNEL}, candidates);
#else // ONE_STAGE
    //std::list<dl::detect::result_t> &results = s1.infer((uint8_t *)arg_img->pixels, {IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_CHANNEL});
    std::list<dl::detect::result_t> &results = s1.infer((uint8_t *)IMAGE_ELEMENT, {IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_CHANNEL});
#endif
    latency.end();
    latency.print("Inference latency");

    // display
    int i = 0;
    for (std::list<dl::detect::result_t>::iterator prediction = results.begin(); prediction != results.end(); prediction++, i++)
    {
        printf("[%d] score: %f, box: [%d, %d, %d, %d]\n", i, prediction->score, prediction->box[0], prediction->box[1], prediction->box[2], prediction->box[3]);

#if TWO_STAGE
        printf("    left eye: (%3d, %3d), ", prediction->keypoint[0], prediction->keypoint[1]);
        printf("right eye: (%3d, %3d)\n", prediction->keypoint[6], prediction->keypoint[7]);
        printf("    nose: (%3d, %3d)\n", prediction->keypoint[4], prediction->keypoint[5]);
        printf("    mouth left: (%3d, %3d), ", prediction->keypoint[2], prediction->keypoint[3]);
        printf("mouth right: (%3d, %3d)\n\n", prediction->keypoint[8], prediction->keypoint[9]);
#endif
    }
}
}
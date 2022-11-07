//
// Created by jinyf on 2022/9/13.
//


/** Bitmap pixel format. */
//enum AndroidBitmapFormat {
//    /** No format. */
//    ANDROID_BITMAP_FORMAT_NONE      = 0,
//    /** Red: 8 bits, Green: 8 bits, Blue: 8 bits, Alpha: 8 bits. **/
//    ANDROID_BITMAP_FORMAT_RGBA_8888 = 1,
//    /** Red: 5 bits, Green: 6 bits, Blue: 5 bits. **/
//    ANDROID_BITMAP_FORMAT_RGB_565   = 4,
//    /** Deprecated in API level 13. Because of the poor quality of this configuration, it is advised to use ARGB_8888 instead. **/
//    ANDROID_BITMAP_FORMAT_RGBA_4444 = 7,
//    /** Alpha: 8 bits. */
//    ANDROID_BITMAP_FORMAT_A_8       = 8,
//};

#include <jni.h>
# include <stdio.h>
#include <android/bitmap.h>
#include "AndroidLog.h"


extern "C" {

}

JavaVM *javaVM = NULL;

extern "C"
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    jint result = -1;
    javaVM = vm;
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return result;
    }
    return JNI_VERSION_1_4;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_yfjin_bitmap_MainActivity_changeBitmap(JNIEnv *env, jobject thiz, jobject _bitmap) {

    AndroidBitmapInfo bitmapInfo;
    // 获取图片信息
    int result = AndroidBitmap_getInfo(env, _bitmap, &bitmapInfo);

    if (result != ANDROID_BITMAP_RESULT_SUCCESS) {
        INFO("LOAD ERROR!")
        return;
    }
    INFO("width:%d", bitmapInfo.width)
    INFO("height:%d", bitmapInfo.height)
    //stride=width*4
    //4等于是1个像素（RGBA）
    INFO("stride:%d", bitmapInfo.stride)
    INFO("format:%d", bitmapInfo.format)
    // 获取像素信息
    unsigned char *pixels;
    result = AndroidBitmap_lockPixels(env, _bitmap, reinterpret_cast<void **>(&pixels));
    if (result != ANDROID_BITMAP_RESULT_SUCCESS) {
        INFO("LOAD PIXELS ERROR!")
        return;
    }
    //stride=width*4
    for (int i = 0; i < bitmapInfo.height * bitmapInfo.stride; i = i + 4) {
        unsigned char r = pixels[i];
        unsigned char g = pixels[i + 1];
        unsigned char b = pixels[i + 2];
        unsigned char a = pixels[i + 3];
        //转灰度(低精度)test
        int gray = (r * 1 + g * 2 + b * 1) >> 2;
        pixels[i] = gray;
        pixels[i + 1] = gray;
        pixels[i + 2] = gray;
//        INFO("index:%d---%x%x%x%x",i,r,g,b,a);
    }

    AndroidBitmap_unlockPixels(env, _bitmap);

    INFO("CHANGE FINISH");


}

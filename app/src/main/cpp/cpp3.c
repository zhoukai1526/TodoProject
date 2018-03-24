
#include <jni.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <android/log.h>
#include "cpp2.h"

#define TAG "TODO" // 这个是自定义的LOG的标识

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型




JNIEXPORT jstring Java_com_iwintrue_todoproject_ndk_JNI2_callJNIBack(JNIEnv *env, jobject obj) {

    jstring  str  = Java_com_iwintrue_todoproject_ndk_JNI_getCString(env,obj);


    return str;

}








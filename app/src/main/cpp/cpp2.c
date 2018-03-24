////
//// Created by 周凯 on 2018/3/19.
////
//
//
#include <jni.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <android/log.h>

#define TAG "TODO" // 这个是自定义的LOG的标识

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型

jint sum(jint a, jint b) {
    return a + b;
}

/**

* 工具方法

* 作用: 把java中的string 转化成一个c语言中的char数组

* 接受的参数 envjni环境的指针

* jstr 代表的是要被转化的java的string 字符串

* 返回值 : 一个c语言中的char数组的首地址 (char 字符串)

*/

char *Jstring2CStr(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = (*env)->FindClass(env, "java/lang/String");

    //jstring strencode = (*env)->NewStringUTF(env,"GB2312");
    jstring strencode = (*env)->NewStringUTF(env, "utf-8");

    jmethodID mid =

            (*env)->GetMethodID(env, clsstring, "getBytes", "(Ljava/lang/String;)[B");

// String.getByte("GB2312");

    jbyteArray barr =

            (jbyteArray) (*env)->CallObjectMethod(env, jstr, mid, strencode);

    jsize alen = (*env)->GetArrayLength(env, barr);

    jbyte *ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);

    if (alen > 0) {

        rtn = (char *) malloc(alen + 1); //"\0"

        memcpy(rtn, ba, alen);

        rtn[alen] = 0;

    }

    (*env)->ReleaseByteArrayElements(env, barr, ba, 0); //

    return rtn;

}





/**
 * 返回c语言字符串
 * @param env
 * @param obj
 * @return
 */

JNIEXPORT jstring Java_com_iwintrue_todoproject_ndk_JNI_getCString(
        JNIEnv *env,
        jobject obj) {
    char *d;
    char str[20] = "c返回的str";
    d = str;
    return (*env)->NewStringUTF(env, d);

}


/**
 * 返回c语言字符串
 * @param env
 * @param obj
 * @return
 */

JNIEXPORT jint Java_com_iwintrue_todoproject_ndk_JNI_getSum(
        JNIEnv *env,
        jobject obj, jint a, jint b) {


    jint total = sum(a, b);

    return total;

}

JNIEXPORT jstring Java_com_iwintrue_todoproject_ndk_JNI_getCatString
        (JNIEnv *env, jobject obj, jstring javaString) {


    char *cstr = Jstring2CStr(env, javaString);
    char *hellostr = "这是c的字符串";
    strcat(cstr, hellostr); //拼接两个字符串

    LOGI("%s", cstr);


    return (*env)->NewStringUTF(env, cstr);


}


/**
 * 返回c数组
 * @param env
 * @param instance
 * @return
 */

JNIEXPORT jintArray JNICALL
Java_com_iwintrue_todoproject_ndk_JNI_getCArray(JNIEnv *env, jobject instance) {

    //创建数组
    jintArray array = (*env)->NewIntArray(env, 10);
    //获取数组指针
    jint *array_pi = (*env)->GetIntArrayElements(env, array, NULL);

    for (int i = 0; i < 10; i++) {
        array_pi[i] = i;
    }
    //4.释放资源
    (*env)->ReleaseIntArrayElements(env, array, array_pi, 0);
    return array;


}


JNIEXPORT jobjectArray JNICALL
Java_com_iwintrue_todoproject_ndk_JNI_getCStringArray(JNIEnv *env, jobject instance, jstring str_) {

    jsize len = 10;
    //获取java中的String类
    jclass objClass = (*env)->FindClass(env, "java/lang/String");
    //获取concat方法
    jmethodID concat_methodID = (*env)->GetMethodID(env, objClass, "concat",
                                                    "(Ljava/lang/String;)Ljava/lang/String;");

    //invoke-virtual {p0, v1}, Ljava/lang/String;->concat(Ljava/lang/String;)Ljava/lang/String;
    ///====================================

//    LOGD("拼接后字符 ===> %s ", chars);
//    //释放内存
//    (*env)->DeleteLocalRef(env,str);
//    (*env)->ReleaseStringUTFChars(env,(jstring)str1,chars);


    //创建数组
    jobjectArray array = (*env)->NewObjectArray(env, len, objClass, 0);

    for (int i = 0; i < 10; i++) {

        char index[25];
        //将整数转化为string
        sprintf(index, " %d", i);

        jstring strObject = (*env)->NewStringUTF(env, "字符串");
        jstring str = (*env)->NewStringUTF(env, index);

        jobject str1 = (*env)->CallObjectMethod(env, strObject, concat_methodID, str);

        const char *chars = (*env)->GetStringUTFChars(env, (jstring) str1, 0);

        jstring jstring1 = (*env)->NewStringUTF(env, chars);
        (*env)->SetObjectArrayElement(env, array, i, jstring1);
        (*env)->ReleaseStringUTFChars(env, str1, chars);

    }

    return array;

}

JNIEXPORT jcharArray JNICALL
Java_com_iwintrue_todoproject_ndk_JNI_getCCharArray(JNIEnv *env, jobject instance) {

    jcharArray charArray = (*env)->NewCharArray(env, 10);
    jchar *pi = (*env)->GetCharArrayElements(env, charArray, 0);

    for (int i = 0; i < 10; i++) {
        pi[i] = "e";
    }
    //数组释放
    (*env)->ReleaseCharArrayElements(env, charArray, pi, 0);

    return charArray;

}

JNIEXPORT jboolean JNICALL
Java_com_iwintrue_todoproject_ndk_JNI_checkPassWord(JNIEnv *env, jobject instance,jstring pass) {

    jstring  originPass = (*env)->NewStringUTF(env,"12345");
    char* s1 = (*env)->GetStringUTFChars(env,originPass,JNI_FALSE);
    char* s2 = (*env)->GetStringUTFChars(env,pass,0);
    LOGI("s1:%s",s1);
    LOGI("s2:%s",s2);
    int equ =  strcmp(s1,s2);
    (*env)->ReleaseStringChars(env,originPass,s1);
    (*env)->ReleaseStringChars(env,pass,s2);

    if(equ==0){
        return 1;
    } else{
        return 0;
    }

}

/**
 * 使用java方法
 * @param env
 * @param instance
 * javap -s class
 */

JNIEXPORT void JNICALL
Java_com_iwintrue_todoproject_ndk_JNI_useJavaMethod(JNIEnv *env, jobject instance) {

    //获取java Class
    jclass jniUtils = (*env)->FindClass(env,"com/iwintrue/todoproject/ndk/JniUtils");

    //获取要调用的方法Id
    jmethodID methodId = (*env)->GetMethodID(env,jniUtils,"add","(II)I");
    //获取jobject
    jobject  job = (*env)->AllocObject(env,jniUtils);
    //调用该方法
    jint  sum = (*env)->CallIntMethod(env,job,methodId,10,20);

    LOGI("%d",sum);

}
/**
 * 刷新ui
 * @param env
 * @param instance
 */

JNIEXPORT void JNICALL
Java_com_iwintrue_todoproject_ndk_Main2Activity_refreshUi(JNIEnv *env, jobject instance) {

   //获取class
    jclass  objClass = (*env)->FindClass(env,"com/iwintrue/todoproject/ndk/Main2Activity");
    //执行环境  方法名 方法签名
    jmethodID  methodId = (*env)->GetMethodID(env,objClass,"toastText","()V");

    (*env)->CallVoidMethod(env,instance,methodId);
}

/**
 * 返回结构体
 * @param env
 * @param instance
 * @return
 */

JNIEXPORT jobject JNICALL
Java_com_iwintrue_todoproject_ndk_JNI_callBackJavaObj(JNIEnv *env, jobject instance) {

    //btn_callback_stuct
    //获取class
    jclass  javaStruct = (*env)->FindClass(env,"com/iwintrue/todoproject/ndk/JavaStruct");
    jobject javaStructObj = (*env)->AllocObject(env,javaStruct);

    jfieldID age = (*env)->GetFieldID(env,javaStruct,"age","I");
    jfieldID name = (*env)->GetFieldID(env,javaStruct,"name","Ljava/lang/String;");
    jstring  nameValue = (*env)->NewStringUTF(env,"张三");

    (*env)->SetIntField(env,javaStructObj,age,19);
    (*env)->SetObjectField(env,javaStructObj,name,nameValue);

    return javaStructObj;

}
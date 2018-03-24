package com.iwintrue.todoproject.ndk;

/**
 * Created by zhoukai on 2018/3/21.
 */

public class JNI2 {
//
    {

        System.loadLibrary("cpp-lib");
        System.loadLibrary("cpp2-lib");
    }


    public native String  callJNIBack();

}

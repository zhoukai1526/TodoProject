package com.iwintrue.todoproject.ndk;

import android.util.Log;

/**
 * Created by zhoukai on 2018/3/20.
 */

public class JniUtils {

    /**
     *
     * public class com.iwintrue.todoproject.ndk.JniUtils {
     public com.iwintrue.todoproject.ndk.JniUtils();
     descriptor: ()V

     public static void staticMethod();
     descriptor: ()V

     public int add(int, int);
     descriptor: (II)I
     }
     */


    public static void staticMethod(){
        Log.i("staic","这是java静态方法");
    }

    public int  add(int x,int y){
        return  x+y;
    }
}

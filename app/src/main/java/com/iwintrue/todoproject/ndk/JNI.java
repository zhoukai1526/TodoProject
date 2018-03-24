package com.iwintrue.todoproject.ndk;

/**
 * Created by zhoukai on 2018/3/19.
 */

public class JNI {

    {
        System.loadLibrary("cpp-lib");
    }

    public native String getCString();

    //利用c返回计算的和
    public  native int  getSum(int a,int b);
    //将java字符串与c字符串相加
    public  native String getCatString(String javaString);
    //回调c的数组运算
    public  native  int[] getCArray();

    //返回c中的字符串数组
    public  native  String[] getCStringArray(String _str);
    //返回c中的char数组
    public  native  char[] getCCharArray();
    //检查密码是否正确
    public  native  boolean checkPassWord(String pass);
    //使用java方法
    public  native  void useJavaMethod();
    //返回结构体
    public  native  JavaStruct callBackJavaObj();


}

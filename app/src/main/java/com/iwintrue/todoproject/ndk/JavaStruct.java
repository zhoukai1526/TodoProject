package com.iwintrue.todoproject.ndk;

/**
 * Created by zhoukai on 2018/3/21.
 *
 *  public int age;
 descriptor: I
 public java.lang.String name;
 descriptor: Ljava/lang/String;
 public com.iwintrue.todoproject.ndk.JavaStruct();
 descriptor: ()V

 */

public class JavaStruct {


    public  int age;
    public  String name;

    @Override
    public String toString() {
        return "JavaStruct{" +
                "age=" + age +
                ", name='" + name + '\'' +
                '}';
    }
}

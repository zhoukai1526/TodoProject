package com.iwintrue.todoproject.ndk;

/**
 * Created by zhoukai on 2018/3/22.
 */

public class FfmUtils {

    static{
        System.loadLibrary("avutil-54");
        System.loadLibrary("swresample-1");
        System.loadLibrary("avcodec-56");
        System.loadLibrary("avformat-56");
        System.loadLibrary("swscale-3");
        System.loadLibrary("postproc-53");
        System.loadLibrary("avfilter-5");
        System.loadLibrary("avdevice-56");
        System.loadLibrary("ffempg-utils");
    }

    public native String  getFfempegConfig();

    public native String  getAvCodeConfig();

    public native String  getAvFormatConfig();

    public  native String getAvCodecInfo();

    public  native String getAvFilter();

    public native  int mp4Toyuv(String input,String output);
}

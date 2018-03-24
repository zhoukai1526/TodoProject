//
// Created by 周凯 on 2018/3/21.
//


#include <jni.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <android/log.h>
#include "ffempgutil.h"
#include <time.h>


#include "include/libavcodec/avcodec.h"  //引入lib
#include "include/libavformat/avformat.h"
#include "include/libavfilter/avfilter.h"
#include "include/libswscale/swscale.h"
#include "include/libavutil/log.h"
#include "include/libavutil/imgutils.h"


#define TAG "TODO" // 这个是自定义的LOG的标识

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGI类型


JNIEXPORT jstring Java_com_iwintrue_todoproject_ndk_JNI2_callJNIBack(JNIEnv *env, jobject obj) {

//    jstring  str1 = (*env)->NewStringUTF(env,"jin2字符串");
//    jstring  str2  = Java_com_iwintrue_todoproject_ndk_JNI_getCString(env,obj);
//    char* str1 = "字符串";
//    char* str2 = "拼接字符串2";
//    char* catStr = malloc(strlen(str1)+strlen(str2));
//    strcat(catStr,str1);
//    strcat(catStr,str2);


    return (*env)->NewStringUTF(env, "返回字符串");

}

/**
 * 获取封装协议info
 * @param env
 * @param instance
 */

struct URLProtocol;

JNIEXPORT jstring
Java_com_iwintrue_todoproject_ndk_FfmUtils_getFfempegConfig(JNIEnv *env, jobject instance) {

    char info[40000] = {0};
    //使用编解码
    av_register_all();


    struct URLProtocol *pup = NULL;
    //Input
    struct URLProtocol **p_temp = &pup;

    avio_enum_protocols((void **) p_temp, 0);
    while ((*p_temp) != NULL) {
        //系统流出10个空格的输出空间存放目标变量的值，默认情况下是右对齐，
        //info = info[in]
        sprintf(info, "%s[In ][%10s]\n", info, avio_enum_protocols((void **) p_temp, 0));
    }
    pup = NULL;
    //Output
    avio_enum_protocols((void **) p_temp, 1);
    while ((*p_temp) != NULL) {
        sprintf(info, "%s[Out][%10s]\n", info, avio_enum_protocols((void **) p_temp, 1));
    }

    //LOGE("%s", info);
    return (*env)->NewStringUTF(env, info);

}

/**
 * 获取Protocol Support Information
 * @param env
 * @param instance
 * @return
 */
JNIEXPORT jstring JNICALL
Java_com_iwintrue_todoproject_ndk_FfmUtils_getAvCodeConfig(JNIEnv *env, jobject instance) {

//    char* info ;
//    info = avcodec_configuration();

    char array[4000] = {};
    sprintf(array, "%s", avcodec_configuration());

    return (*env)->NewStringUTF(env, array);

}


JNIEXPORT jstring JNICALL
Java_com_iwintrue_todoproject_ndk_FfmUtils_getAvFormatConfig(JNIEnv *env, jobject instance) {


    char info[40000] = {0};
    //注册编解码方法
    av_register_all();
    //获取类库支持的封装格式
    AVInputFormat *if_temp = av_iformat_next(NULL);
    AVOutputFormat *of_temp = av_oformat_next(NULL);

    while (if_temp != NULL) {
        sprintf(info, "%s[读取流][%10s]\n", info, if_temp->name);
        if_temp = if_temp->next;
    }

    //Output
    while (of_temp != NULL) {
        sprintf(info, "%s[输出流][%10s]\n", info, of_temp->name);
        of_temp = of_temp->next;
    }
    //LOGE("%s", info);
    return (*env)->NewStringUTF(env, info);
}

/**
 *  AVCodec Support Information
 * @param env
 * @param instance
 * @return
 */


JNIEXPORT jstring JNICALL
Java_com_iwintrue_todoproject_ndk_FfmUtils_getAvCodecInfo(JNIEnv *env, jobject instance) {

    char info[40000] = {0};

    av_register_all();

    AVCodec *c_temp = av_codec_next(NULL);

    while (c_temp != NULL) {
        if (c_temp->decode != NULL) {
            sprintf(info, "%s[Dec]", info);
        } else {
            sprintf(info, "%s[Enc]", info);
        }
        switch (c_temp->type) {
            case AVMEDIA_TYPE_VIDEO:
                sprintf(info, "%s[Video]", info);
                break;
            case AVMEDIA_TYPE_AUDIO:
                sprintf(info, "%s[Audio]", info);
                break;
            default:
                sprintf(info, "%s[Other]", info);
                break;
        }
        sprintf(info, "%s[%10s]\n", info, c_temp->name);


        c_temp = c_temp->next;
    }
    //LOGE("%s", info);

    return (*env)->NewStringUTF(env, info);
}

JNIEXPORT jstring JNICALL
Java_com_iwintrue_todoproject_ndk_FfmUtils_getAvFilter(JNIEnv *env, jobject instance) {

    char info[400000] = {0};
    avfilter_register_all();
    AVFilter *f_temp = (AVFilter *) avfilter_next(NULL);
    while (f_temp != NULL) {
        sprintf(info, "%s[%10s]\n", info, f_temp->name);
        f_temp = f_temp->next;
    }
    //LOGE("%s", info);

    return (*env)->NewStringUTF(env, info);
}

//Output FFmpeg's av_log()
void custom_log(void *ptr, int level, const char *fmt, va_list vl) {
    FILE *fp = fopen("/storage/emulated/0/av_log.txt", "a+");
    if (fp) {
        vfprintf(fp, fmt, vl);
        fflush(fp);
        fclose(fp);
    }
}

/**
 * 视频解码器
 * 将MP4视频解码为yuv格式
 */

JNIEXPORT jint JNICALL
Java_com_iwintrue_todoproject_ndk_FfmUtils_mp4Toyuv(JNIEnv *env, jobject obj, jstring input_jstr,
                                                    jstring output_jstr) {

    LOGE("c开始解码mp4视频");

    //声明音视频格式化上下文
    AVFormatContext *pFormatCtx;
    int i, videoindex;
    //视音频编解码器上下文
    AVCodecContext *pCodecCtx;
    //音视频编码
    AVCodec *pCodec;
    //音视频帧信息
    AVFrame *pFrame, *pFrameYUV;
    uint8_t *out_buffer;
    AVPacket *packet;
    int y_size;
    int ret, got_picture;
    struct SwsContext *img_convert_ctx;
    FILE *fp_yuv;
    int frame_cnt;
    clock_t time_start, time_finish;
    double time_duration = 0.0;

    char input_str[500] = {0};
    char output_str[500] = {0};
    char info[1000] = {0};

    //获取到输入文件路劲和保存文件路径并存储到input_str与output_str
    sprintf(input_str, "%s", (*env)->GetStringUTFChars(env, input_jstr, NULL));
    sprintf(output_str, "%s", (*env)->GetStringUTFChars(env, output_jstr, NULL));

    //FFmpeg av_log() callback  //将log输出到指定文件
    av_log_set_callback(custom_log);
    //注册
    av_register_all();
    //1．加载socket库以及网络加密协议相关的库，为后续使用网络相关提供支持
    avformat_network_init();
    //初始化音视频上下文
    pFormatCtx = avformat_alloc_context();
    //打开音视频流
//    ps：函数调用成功之后处理过的AVFormatContext结构体。
//    file：打开的视音频流的URL。
//    fmt：强制指定AVFormatContext中AVInputFormat的。这个参数一般情况下可以设置为NULL，这样FFmpeg可以自动检测AVInputFormat。
//    dictionay：附加的一些选项，一般情况下可以设置为NULL。
//    函数执行成功的话，其返回值大于等于0。
    if (avformat_open_input(&pFormatCtx, input_str, NULL, NULL) != 0) {
        LOGE("Couldn't open input stream");
        return -1;
    }
   // 该函数可以读取一部分视音频数据并且获得一些相关的信息
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        LOGE("Couldn't find stream information");
        return -1;
    }
    videoindex = -1;
    // Number of elements in AVFormatContext.streams
    //获取pFormatCtx中的流,然后获取到视频流
    for (i = 0; i < pFormatCtx->nb_streams; i++)
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoindex = i;
            break;
        }
    if (videoindex == -1) {
        LOGE("Couldn't find a video stream");
        return -1;
    }
    //获取到视频流的编解码封装格式上下文
    pCodecCtx = pFormatCtx->streams[videoindex]->codec;
    //获取到音视频解码
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if (pCodec == NULL) {
        LOGE("Couldn't find Codec");
        return -1;
    }
    //该函数用于初始化一个视音频编解码器的AVCodecContext。
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        LOGE("Couldn't open codec");
        return -1;
    }

    //分配存储视频帧信息的结构体
    pFrame = av_frame_alloc();
    pFrameYUV = av_frame_alloc();

    out_buffer = (unsigned char *) av_malloc(
            av_image_get_buffer_size(AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height, 1));

    av_image_fill_arrays(pFrameYUV->data, pFrameYUV->linesize, out_buffer,
                         AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height, 1);


    packet = (AVPacket *) av_malloc(sizeof(AVPacket));

    img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
                                     pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUV420P,
                                     SWS_BICUBIC, NULL, NULL, NULL);


    sprintf(info, "[Input     ]%s\n", input_str);
    sprintf(info, "%s[Output    ]%s\n", info, output_str);
    sprintf(info, "%s[Format    ]%s\n", info, pFormatCtx->iformat->name);
    sprintf(info, "%s[Codec     ]%s\n", info, pCodecCtx->codec->name);
    sprintf(info, "%s[Resolution]%dx%d\n", info, pCodecCtx->width, pCodecCtx->height);
    LOGE("判断yuv");

    //打开文件
    fp_yuv = fopen(output_str, "wb+");
    if (fp_yuv == NULL) {
        printf("Cannot open output file");
        LOGE("Cannot open output file");
        LOGE("Cannot open output file%s", info);


        return -1;
    }

    frame_cnt = 0;
    //获取当前时间
    time_start = clock();
    LOGE("Cannot open output file%l", time_start);

    while (av_read_frame(pFormatCtx, packet) >= 0) {
        //获取到压缩音视频帧信息,packet
        if (packet->stream_index == videoindex) {

            ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
            if (ret < 0) {
                LOGE("Decode Error");
                return -1;
            }
            if (got_picture) {
                //sws_scale()：处理图像数据。
//                从图中可以看出，libswscale处理数据有两条最主要的方式：unscaled和scaled。unscaled用于处理不需要拉伸的像素数据（属于比较特殊的情况），scaled用于处理需要拉伸的像素数据。Unscaled只需要对图像像素格式进行转换；而Scaled则除了对像素格式进行转换之外，还需要对图像进行缩放。Scaled方式可以分成以下几个步骤：
//                XXX to YUV Converter：首相将数据像素数据转换为8bitYUV格式；
//                Horizontal scaler：水平拉伸图像，并且转换为15bitYUV；
//                Vertical scaler：垂直拉伸图像；
//                Output converter：转换为输出像素格式

                sws_scale(img_convert_ctx, (const uint8_t *const *) pFrame->data, pFrame->linesize,
                          0, pCodecCtx->height,
                          pFrameYUV->data, pFrameYUV->linesize);

                y_size = pCodecCtx->width * pCodecCtx->height;
                fwrite(pFrameYUV->data[0], 1, y_size, fp_yuv);    //Y
                fwrite(pFrameYUV->data[1], 1, y_size / 4, fp_yuv);  //U
                fwrite(pFrameYUV->data[2], 1, y_size / 4, fp_yuv);  //V
                //Output info
                char pictype_str[10] = {0};
                switch (pFrame->pict_type) {
                    case AV_PICTURE_TYPE_I:
                        sprintf(pictype_str, "I");
                        break;
                    case AV_PICTURE_TYPE_P:
                        sprintf(pictype_str, "P");
                        break;
                    case AV_PICTURE_TYPE_B:
                        sprintf(pictype_str, "B");
                        break;
                    default:
                        sprintf(pictype_str, "Other");
                        break;
                }
                LOGI("Frame Index: %5d. Type:%s", frame_cnt, pictype_str);
                frame_cnt++;
            }
        }
        av_free_packet(packet);
    }
    //flush decoder
    //FIX: Flush Frames remained in Codec
    while (1) {
        ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
        if (ret < 0)
            break;
        if (!got_picture)
            break;
        sws_scale(img_convert_ctx, (const uint8_t *const *) pFrame->data, pFrame->linesize, 0,
                  pCodecCtx->height,
                  pFrameYUV->data, pFrameYUV->linesize);
        int y_size = pCodecCtx->width * pCodecCtx->height;
        fwrite(pFrameYUV->data[0], 1, y_size, fp_yuv);    //Y
        fwrite(pFrameYUV->data[1], 1, y_size / 4, fp_yuv);  //U
        fwrite(pFrameYUV->data[2], 1, y_size / 4, fp_yuv);  //V
        //Output info
        char pictype_str[10] = {0};
        switch (pFrame->pict_type) {
            case AV_PICTURE_TYPE_I:
                sprintf(pictype_str, "I");
                break;
            case AV_PICTURE_TYPE_P:
                sprintf(pictype_str, "P");
                break;
            case AV_PICTURE_TYPE_B:
                sprintf(pictype_str, "B");
                break;
            default:
                sprintf(pictype_str, "Other");
                break;
        }
        LOGI("Frame Index: %5d. Type:%s", frame_cnt, pictype_str);
        frame_cnt++;
    }
    time_finish = clock();
    time_duration = (double) (time_finish - time_start);

    sprintf(info, "%s[Time      ]%fms\n", info, time_duration);
    sprintf(info, "%s[Count     ]%d\n", info, frame_cnt);

    sws_freeContext(img_convert_ctx);

    fclose(fp_yuv);

    av_frame_free(&pFrameYUV);
    av_frame_free(&pFrame);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);

    return 0;
}




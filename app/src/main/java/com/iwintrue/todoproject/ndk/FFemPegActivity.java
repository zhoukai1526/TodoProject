package com.iwintrue.todoproject.ndk;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.iwintrue.todoproject.R;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FFemPegActivity extends AppCompatActivity {

    FfmUtils ffmUtils = new FfmUtils();
    private static final String TAG = "FFemPegActivity";
    TextView tv_show_config;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ffem_peg);
        initView();
    }

    private void initView() {
        tv_show_config = findViewById(R.id.tv_show_config);
    }

    public void onClick(View view) {

        switch (view.getId()) {
            case R.id.btn_ffempeg_config:
                String config = ffmUtils.getFfempegConfig();
                Log.i(TAG, config);
                tv_show_config.setText("config:" + config);
                break;
            case R.id.btn_avcode_config:
                String avConfig = ffmUtils.getAvCodeConfig();
                Log.i(TAG, avConfig);
                tv_show_config.setText("avConfig:" + avConfig);
                break;
            case R.id.btn_avformat_config:
                String avFormatConfig = ffmUtils.getAvFormatConfig();
                Log.i(TAG, avFormatConfig);
                tv_show_config.setText("avformatConfig:" + avFormatConfig);
                break;
            case R.id.btn_avcodec_config:
                String avCodecInfo = ffmUtils.getAvCodecInfo();
                Log.i(TAG, avCodecInfo);
                tv_show_config.setText("avCodecInfo:" + avCodecInfo);
                break;
            case R.id.btn_avfilter_config:
                String avFilterInfo = ffmUtils.getAvFilter();
                Log.i(TAG, avFilterInfo);
                tv_show_config.setText("avFilterInfo:" + avFilterInfo);
                break;
            case R.id.btn_mp4_to_yuv:

                ///storage/emulated/0/11.mp4  yuv大约是MP3封装格式的几百倍
                Log.i(TAG,"开始解码");
                String storeagePath = Environment.getExternalStorageDirectory().getAbsolutePath();
                String input = storeagePath+"/11.mp4";
                int code = ffmUtils.mp4Toyuv(input,storeagePath+"/11.yuv");
                Toast.makeText(FFemPegActivity.this,"解码成功"+code,Toast.LENGTH_SHORT).show();
                break;
        }
    }

    public String readSDFile(String fileName) throws IOException {

        File file = new File(fileName);

        FileInputStream fis = new FileInputStream(file);

        int length = fis.available();

        byte [] buffer = new byte[length];
        fis.read(buffer);


        fis.close();
        return new String(buffer,"utf-8");
    }


    public void savaFileToSD(String filename, String filecontent) throws Exception {
        //如果手机已插入sd卡,且app具有读写sd卡的权限
        if(Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED)) {
            filename = Environment.getExternalStorageDirectory().getCanonicalPath() + "/" + filename;

            //这里就不要用openFileOutput了,那个是往手机内存中写数据的
            FileOutputStream output = new FileOutputStream(filename);
            output.write(filecontent.getBytes());
            //将String字符串以字节流的形式写入到输出流中
            output.close();
            //关闭输出流
        } else Toast.makeText(this, "SD卡不存在或者不可读写", Toast.LENGTH_SHORT).show();
    }
}

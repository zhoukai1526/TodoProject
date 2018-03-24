package com.iwintrue.todoproject.ndk;

import android.nfc.Tag;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import com.iwintrue.todoproject.R;

public class Main2Activity extends AppCompatActivity implements View.OnClickListener {

    JNI jni = new JNI();
    JNI2 jni2 = new JNI2();
    private static final String TAG = "Main2Activity";

    /**
     * public class com.iwintrue.todoproject.ndk.Main2Activity extends android.support.v7.app.AppCompatActivity implements android.view.View$OnClickListener {
     * com.iwintrue.todoproject.ndk.JNI jni;
     * descriptor: Lcom/iwintrue/todoproject/ndk/JNI;
     * public com.iwintrue.todoproject.ndk.Main2Activity();
     * descriptor: ()V
     * <p>
     * protected void onCreate(android.os.Bundle);
     * descriptor: (Landroid/os/Bundle;)V
     * <p>
     * public void onClick(android.view.View);
     * descriptor: (Landroid/view/View;)V
     * <p>
     * public native void refreshUi();
     * descriptor: ()V
     * <p>
     * public void toastText();
     * descriptor: ()V
     * }
     *
     * @param savedInstanceState
     */

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);
        findViewById(R.id.btn_cStr).setOnClickListener(this);
        findViewById(R.id.btn_sum).setOnClickListener(this);
        findViewById(R.id.btn_cat).setOnClickListener(this);
        findViewById(R.id.btn_carray).setOnClickListener(this);
        findViewById(R.id.btn_check_pass).setOnClickListener(this);
        findViewById(R.id.btn_use_java).setOnClickListener(this);
        findViewById(R.id.btn_refresh_ui).setOnClickListener(this);
        findViewById(R.id.btn_callback_stuct).setOnClickListener(this);
        findViewById(R.id.btn_callback_jni).setOnClickListener(this);

    }

    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.btn_cStr:
                String cStr = jni.getCString();
                Log.i(TAG, cStr);
                break;
            case R.id.btn_sum:
                int sum = jni.getSum(10, 90);
                Log.i(TAG, "计算的结果为：" + sum);
                break;
            case R.id.btn_cat:
                String catStr = jni.getCatString("wo是java");
                Log.i(TAG, catStr);
                break;
            case R.id.btn_carray:
                //int[] carray = jni.getCArray();
//                char[] charArray = jni.getCCharArray();
                String[] strArray = jni.getCStringArray("a");
                Log.i(TAG, "返回字符串数组[0]==" + strArray[0]);
                Log.i(TAG, "返回字符串数组[1]==" + strArray[1]);
                break;
            case R.id.btn_check_pass:

                boolean flag = jni.checkPassWord("12345");
                if (flag) {
                    Log.i(TAG, "密码正确");
                } else {
                    Log.i(TAG, "密码错误");
                }
                break;
            case R.id.btn_use_java:
                jni.useJavaMethod();
                break;
            case R.id.btn_refresh_ui:
                refreshUi();
                break;
            case R.id.btn_callback_stuct:
                JavaStruct javaStruct = jni.callBackJavaObj();
                Log.i(TAG,javaStruct.toString());
                break;
            case R.id.btn_callback_jni:
                Log.i(TAG,jni2.callJNIBack());
                break;

        }
    }

    //c刷新ui
    public native void refreshUi();

    public void toastText() {
        Toast.makeText(this, "吐司", Toast.LENGTH_SHORT).show();
    }
}

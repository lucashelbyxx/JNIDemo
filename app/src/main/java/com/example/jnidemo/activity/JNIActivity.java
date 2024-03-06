package com.example.jnidemo.activity;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import com.example.jnidemo.databinding.ActivityJniactivityBinding;
import com.example.jnidemo.jni.JNIDemo;

public class JNIActivity extends AppCompatActivity {
    private final String TAG = "JNIActivity";

    private ActivityJniactivityBinding binding;

    // 实现一个 JNIDemo 实例对象
    private JNIDemo mJNIDemo = new JNIDemo();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityJniactivityBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // 通过 JNIDemo 实例对象调用 java native 方法，
        // 从而调用 JNI 方法，实现对 JNI 字符串的获取
        binding.tvJni.setText(mJNIDemo.JavaGetStringFromJNI());
    }
}
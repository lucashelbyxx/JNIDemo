package com.example.jnidemo.jni;

public class JNIDemo {
    private static final String TAG = "JNIDemo";

    // 应用启动时，load 编译 JNI 生成的 so 库
    static {
        System.loadLibrary("jnidemo");
    }

    // Java 从 JNI 获取 String
    public native String JavaGetStringFromJNI();
}

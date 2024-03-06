#include <jni.h>    // 引入jni.h头文件，它定义了 JNI 编程所需的所有类型和函数
#include <string>
#include <android/log.h>    // 引入 Android 日志打印的头文件
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "jnidemo.h"

// 定义用于 Android 日志打印的宏，使得可以在 C++ 代码中方便地打印日志到 Android 的 logcat
#define TAG "JNITEST"   // 自定义日志的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL, TAG, __VA_ARGS__)

using namespace std;

#ifdef __cplusplus  // 兼容C++代码
extern "C" {    // 兼容C代码，告诉C++编译器，其中的代码应当以C语言的方式进行链接

// 定义一个名为 Java_com_example_jnidemo_jni_JNIDEMO_getStringFromJNI 的函数
// 这个函数的命名方式是 JNI 的规定，它表示这个函数可以被名为 com.example.jnidemo.jni.JNIDEMO 的 Java 类调用，函数名为 getStringFromJNI
JNIEXPORT jstring JNICALL
Java_com_example_jnidemo_jni_JNIDemo_JavaGetStringFromJNI(
        JNIEnv *env,    // Java虚拟机内存的地址指针，可以通过它来调用JNI的各种函数
        jobject instance ) { // 当前Java对象的引用
    string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str()); // 将C++字符串转换为Java字符串

}
}
#endif
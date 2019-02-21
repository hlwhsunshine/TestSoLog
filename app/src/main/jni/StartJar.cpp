#include "StartJar.h"
#include<stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <string>
#include <string.h>
#include<jni.h>
#include<android/log.h>



#define TAG    "TestJniLog" // 这个是自定义的LOG的标识
#define LOGD(...)  __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__) // 定义LOGD类型


jobject getGlobalContext(JNIEnv *env);

int main()
{
        jint res;
        JavaVM *jvm;
        JNIEnv *env;
        JavaVMInitArgs vm_args;
        JavaVMOption options[3];
        /*设置初始化参数*/
        options[0].optionString = "-Djava.compiler=NONE";
        options[1].optionString = "-Djava.class.path=/data/SDK.jar";  //这里指定了要使用的第三方Jar包
        options[2].optionString = "-verbose:NONE"; //用于跟踪运行时的信息




        vm_args.version=JNI_VERSION_1_6;//jdk版本目前有1.1，1.2，1.4 只要比你的jdk的版本低就可以 我用的是jdk1.5.0的版本
        vm_args.nOptions = 3;
        vm_args.options = options;
        vm_args.ignoreUnrecognized = JNI_TRUE;
        res = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
        if (res < 0 || jvm == NULL || env == NULL) {
                LOGD("Can't create Java VM\n");
                return -1;
        }
        LOGD( "ok 调用JNI_CreateJavaVM创建虚拟机\n");

        /*获取实例的类定义*/
        jclass cls = env->FindClass("com/ib/mob/AdGlobalMgr");    //这里是jar包内JymProduce类的具体路径
        if (cls == 0) {
                 LOGD("FindClass failed\n");
                jvm->DestroyJavaVM();
                 LOGD("Java VM destory.\n");
                return -1;
        }
         LOGD("ok 返回JAVA类的CLASS对象\n");

        /*获取构造函数,用于创建对象*/
        /***1.1可用""作为构造函数, 1.2用"<init>"参数中不能有空格
        "(Ljava/lang/String;)V"*/
        //jmethodID mid = (*env)->GetMethodID(env, cls, "getGertWord",
        //        "(Ljava/lang/String;Ljava/lang/String;JLjava/lang/String;Ljava/lang/String;)Ljava/lang/String;");

        jmethodID init =env->GetStaticMethodID(cls, "init","(Landroid/content/Context;Ljava/lang/String;)V");


        jstring str = env->NewStringUTF( "f7237cca4e1766c7714dafd6affcd627");
        //调用静态方法使用的是jclass，而不是jobject
        env->CallStaticVoidMethod( cls, init, getGlobalContext(env),str);
        LOGD( "CallStaticVoidMethod\n");
        /*销毁JAVA虚拟机*/
        jvm->DestroyJavaVM();
        LOGD( "Java VM destory.\n");



	return 0;
}

/**
*获取context
*/
jobject getGlobalContext(JNIEnv *env)
{
    //获取Activity Thread的实例对象
    jclass activityThread = env->FindClass("android/app/ActivityThread");
    jmethodID currentActivityThread = env->GetStaticMethodID(activityThread, "currentActivityThread", "()Landroid/app/ActivityThread;");
    jobject at = env->CallStaticObjectMethod(activityThread, currentActivityThread);
    //获取Application，也就是全局的Context
    jmethodID getApplication = env->GetMethodID(activityThread, "getApplication", "()Landroid/app/Application;");
    jobject context = env->CallObjectMethod(at, getApplication);
    return context;
}




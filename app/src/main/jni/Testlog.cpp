//
// Created by 123 on 2019/1/2.
#include<stdio.h>
#include<jni.h>
#include<stdlib.h>
#include<android/log.h>
#include <stdarg.h>
#include <dlfcn.h>

#include "com_annotion_ruiyi_testsolog_JniHelper.h"

#define TAG    "TestJniLog" // 这个是自定义的LOG的标识
#define LOGD(...)  __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__) // 定义LOGD类型


JNIEXPORT void JNICALL Java_com_annotion_ruiyi_testsolog_JniHelper_showLog
  (JNIEnv *env, jobject jo){
       //const char *s = env->GetStringUTFChars(js, 0);
       // FILE *pFile;
        char* a;
	    void *filehandle  = dlopen("/system/lib/libhellolog.so", RTLD_LAZY);

        if(filehandle){
            LOGD("filehandle不为空");

            typedef char * (*hellologg)();
            hellologg hellolog = (hellologg) dlsym(filehandle, "hellolog");

            if(hellolog){
                LOGD("hellolog不为空");
                a = hellolog();
                LOGD("第一个log: %s", a);
            }



             typedef char * (*Second)();
                Second secondlog = (Second) dlsym(filehandle, "secondLog");

                if(secondlog){
                    LOGD("secondlog不为空");
                    a = secondlog();
                    LOGD("第二个log: %s", a);
                }


            dlclose(filehandle);
            filehandle = NULL;
          }

      // pFile = fopen("/storage/emulated/0/test.txt", "rw");
       //unsigned short write_result = fwrite(s, 6, 1, pFile); // 返回值是成功写入的项目数
  }





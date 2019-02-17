//
// Created by 123 on 2019/1/2.
#include<stdio.h>
#include<jni.h>
#include<stdlib.h>
#include<android/log.h>
#include <stdarg.h>
#include <dlfcn.h>

#include<string>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/time.h>
#include<fcntl.h>

#include "com_annotion_ruiyi_testsolog_JniHelper.h"


void *filehandle = NULL;

#define TAG    "TestJniLog" // 这个是自定义的LOG的标识
#define LOGD(...)  __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__) // 定义LOGD类型


JNIEXPORT void JNICALL Java_com_annotion_ruiyi_testsolog_JniHelper_showLog
  (JNIEnv *env, jobject jo){
       //const char *s = env->GetStringUTFChars(js, 0);
      // FILE *pFile;
        //string b;
        char* a;
	    filehandle = dlopen("/system/lib/libhellolog.so", RTLD_LAZY);

            if(filehandle)
            {
                LOGD("filehandle不为空");
                char* log = (char *)dlsym(filehandle, "hellolog");
                if(log){
                    LOGD("log不为空");
                   a = log;
                   LOGD("log2: %s", log);
                }
                LOGD("log3");
                dlclose(filehandle);
                LOGD("log4");
                filehandle = NULL;
                LOGD("log5");
          }
          LOGD("log6");

          LOGD("%s",a);
          LOGD("log7");


      // pFile = fopen("/storage/emulated/0/test.txt", "rw");

       //unsigned short write_result = fwrite(s, 6, 1, pFile); // 返回值是成功写入的项目数
  }





#include "StartJar.h"
#include<stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <string>
#include <string.h>
#include<jni.h>
#include<android/log.h>
#include <sys/wait.h>

#include<sys/types.h>
#include<fcntl.h>
#include<limits.h>



#define TAG    "TestJniLog" // 这个是自定义的LOG的标识
#define LOGD(...)  __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__) // 定义LOGD类型
#define BUFSZ PIPE_BUF

jobject getGlobalContext(JNIEnv *env);

int main(){
        char buf[BUFSZ];
                FILE *fp;
        LOGD("C程序pid=%d", getpid());
        LOGD("C程序ppid=%d", getppid());
        LOGD("C程序uid=%d", getuid());
        LOGD("开始调用脚本");

        execl("/system/bin/su", "su", "-c", "./system/bin/startJar.sh", (char *)0);


        char cmd[150] = "./data/startJar.sh";
        //const char *sysCommand = cmd.data();
        if ((fp = popen(cmd, "r")) == NULL) {
            LOGD("调用失败");
            return 0;
        }
        if((fgets(buf,BUFSZ,fp))!= NULL )
        {
        LOGD("调用成功");
        int count = atoi(buf);
        LOGD("count:%d",count);
        pclose(fp);
        }else{
            LOGD("调用失败");
        }
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




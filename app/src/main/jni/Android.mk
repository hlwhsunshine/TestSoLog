
LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)

LOCAL_LDLIBS :=-llog



LOCAL_MODULE    := StartJar

LOCAL_SRC_FILES := StartJar.c



include $(BUILD_EXECUTABLE)
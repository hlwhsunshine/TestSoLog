
LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)

LOCAL_LDLIBS :=-llog



LOCAL_MODULE    := jartest

LOCAL_SRC_FILES := StartJar.cpp



include $(BUILD_EXECUTABLE)
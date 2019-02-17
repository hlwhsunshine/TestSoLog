
LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)

LOCAL_LDLIBS :=-llog



LOCAL_MODULE    := testlog

LOCAL_SRC_FILES := Testlog.cpp



include $(BUILD_SHARED_LIBRARY)
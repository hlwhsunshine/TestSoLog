package com.annotion.ruiyi.testsolog;

/**
 * Function:
 * Project:TestSoLog
 * Date:2019/2/17
 * Created by xiaojun .
 */

public class JniHelper {
    static {
        System.loadLibrary("testlog");
    }

    public static native void showLog();
}

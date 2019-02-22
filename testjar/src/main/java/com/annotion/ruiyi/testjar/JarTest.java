package com.annotion.ruiyi.testjar;

import android.util.Log;

import java.io.File;

/**
 * Function:
 * Project:TestSoLog
 * Date:2019/2/22
 * Created by xiaojun .
 */

public class JarTest {
    public static void main(String args[]){
        //Log.e("JarTest","------------this is test！！！！！！");
        new File("/storage/emulated/0/ARM/AAA").mkdir();
        for (int i = 0; i < 100; i++) {

            try {
                System.out.println("-------------------JarTest--------------------");
                Thread.sleep(5000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

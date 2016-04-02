package com.h6ah4i.android.example.ndklibrary;

/**
 * Created by hasegawa on 4/2/16.
 */
public class MyNdkLibrary {
    public static void loadModule() {
        System.loadLibrary("MyNdkLibrary"); // See src/main/jni/Android.mk
    }
}

package com.h6ah4i.android.example.ndklibrary.cxxdasp;

/**
 * Created by hasegawa on 4/2/16.
 */
@SuppressWarnings("JniMissingFunction")
public class FFTReal {
    private long mNativeHandle;
    private int mSize;
    private int mInputBufferSize;
    private int mOutputBufferSize;

    public FFTReal() {
    }

    public void setup(int size) {
        if (mNativeHandle != 0) {
            throw new IllegalStateException();
        }

        mNativeHandle = nativeSetup(size);
        if (mNativeHandle != 0) {
            mSize = size;
            mInputBufferSize = size;
            mOutputBufferSize = forwardFftRealNumOutputs(size) * 2; // *2: complex number
        }
    }

    public void doFft(float[] input, float[] output) {
        if (mNativeHandle == 0) {
            throw new IllegalStateException();
        }
        if (input == null || output == null || input.length < mInputBufferSize || output.length < mOutputBufferSize) {
            throw new IllegalArgumentException();
        }

        nativeDoFft(mNativeHandle, input, output);
    }

    public void release() {
        if (mNativeHandle == 0) {
            return;
        }

        nativeRelease(mNativeHandle);
        mNativeHandle = 0;
        mSize = 0;
        mInputBufferSize = 0;
        mOutputBufferSize = 0;
    }

    public int size() {
        return mSize;
    }

    public int inputBufferSize() {
        return mInputBufferSize;
    }

    public int outputBufferSize() {
        return mOutputBufferSize;
    }

    private static native long nativeSetup(int size);

    private static native void nativeDoFft(long handle, float[] input, float[] output);

    private static native void nativeRelease(long handle);

    // cxxdasp::utils::forward_fft_real_num_outputs()
    private static int forwardFftRealNumOutputs(int n) {
        if ((n % 2) == 0) {
            return (n / 2) + 1;
        } else {
            return (n + 1) / 2;
        }
    }
}

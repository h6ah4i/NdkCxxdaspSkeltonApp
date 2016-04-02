//
//    Copyright (C) 2014 Haruki Hasegawa
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//

#include <cstring>

#include <jni.h>

#include <cxxporthelper/memory>
#include <cxxporthelper/aligned_memory.hpp>
#include <cxxdasp/fft/fft.hpp>
#include <cxxdasp/utils/utils.hpp>

namespace MyNdkLibrary {

class NativeFFTReal {
public:
    typedef float fft_input_t;
    typedef std::complex<float> fft_output_t;
    typedef cxxporthelper::aligned_memory<fft_input_t> fft_input_memory_t;
    typedef cxxporthelper::aligned_memory<fft_output_t> fft_output_memory_t;
    typedef cxxdasp::fft::fft<fft_input_t, fft_output_t, cxxdasp::fft::backend::f::pffft::forward_real> fft_obj_t;

    NativeFFTReal(std::size_t size);

    size_t size() const noexcept { return size_; }
    size_t input_size() const noexcept { return in_data_.size(); }
    size_t output_size() const noexcept { return out_data_.size(); }

    fft_input_t *input_buffer() noexcept { return in_data_.get(); }
    const fft_output_t *output_buffer() noexcept { return out_data_.get(); }

    void execute() { fftobj_.execute(); }

private:
    const std::size_t size_;

    fft_input_memory_t in_data_;
    fft_output_memory_t out_data_;
    fft_obj_t fftobj_;
};

NativeFFTReal::NativeFFTReal(std::size_t size)
 : size_(size), in_data_(), out_data_(), fftobj_()
{
    try {
        fft_input_memory_t in_data(size);
        fft_output_memory_t out_data(cxxdasp::utils::forward_fft_real_num_outputs(size));
        fft_obj_t fftobj;


        fftobj.setup(size, &in_data[0], &out_data[0]);

        in_data_ = std::move(in_data);
        out_data_ = std::move(out_data);
        fftobj_ = std::move(fftobj);
    } catch (const std::bad_alloc &e) {
        throw e;
    }
}

} /* namespace MyNdkLibrary */

extern "C" {
using namespace MyNdkLibrary;

JNIEXPORT jlong JNICALL
Java_com_h6ah4i_android_example_ndklibrary_cxxdasp_FFTReal_nativeSetup(JNIEnv *env, jclass clazz, jint size)
{
    std::unique_ptr<NativeFFTReal> fft;

    try {
        fft.reset(new NativeFFTReal(size));
    } catch (const std::bad_alloc &e) {
    }

    return reinterpret_cast<jlong>(fft.release());
}

JNIEXPORT void JNICALL
Java_com_h6ah4i_android_example_ndklibrary_cxxdasp_FFTReal_nativeDoFft(JNIEnv *env, jclass clazz, jlong handle, jfloatArray in, jfloatArray out)
{
    if (!handle)
        return;

    NativeFFTReal *fft = reinterpret_cast<NativeFFTReal *>(handle);

    // copy input data
    {
        jfloat *in_ptr = static_cast<jfloat *>(env->GetPrimitiveArrayCritical(in, nullptr));
        (void) ::memcpy(fft->input_buffer(), in_ptr, sizeof(NativeFFTReal::fft_input_t) * fft->input_size());
        env->ReleasePrimitiveArrayCritical(in, in_ptr, JNI_ABORT);
    }

    // perform FFT
    fft->execute();

    // copy output data
    {
        jfloat *out_ptr = static_cast<jfloat *>(env->GetPrimitiveArrayCritical(out, nullptr));
        (void) ::memcpy(out_ptr, fft->output_buffer(), sizeof(NativeFFTReal::fft_output_t) * fft->output_size());
        env->ReleasePrimitiveArrayCritical(out, out_ptr, 0);
    }
}


JNIEXPORT void JNICALL
Java_com_h6ah4i_android_example_ndklibrary_cxxdasp_FFTReal_nativeRelease(JNIEnv *env, jclass clazz, jlong handle)
{
    if (!handle)
        return;

    NativeFFTReal *fft = reinterpret_cast<MyNdkLibrary::NativeFFTReal *>(handle);
    delete fft;
}

} /* extern "C" */

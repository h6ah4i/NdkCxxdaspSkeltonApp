#
#    Copyright (C) 2014 Haruki Hasegawa
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#

PROJ_LOCAL_PATH := $(call my-dir)

#
# Common
#
# enumerate all *.cpp files in the /source directory
OSLMP_LOCAL_SRC_FILES := $(wildcard $(PROJ_LOCAL_PATH)/source/*.cpp)
# remove unnecessary $(LOCAL_PATH)
OSLMP_LOCAL_SRC_FILES := $(subst $(PROJ_LOCAL_PATH)/,, $(OSLMP_LOCAL_SRC_FILES))

OSLMP_LOCAL_EXPORT_C_INCLUDES := $(PROJ_LOCAL_PATH)/include


#
# MyNdkLibary
#
LOCAL_PATH := $(PROJ_LOCAL_PATH)

include $(CLEAR_VARS)

LOCAL_MODULE    := MyNdkLibrary
LOCAL_C_INCLUDES := $(OSLMP_LOCAL_C_INCLUDES)
LOCAL_EXPORT_C_INCLUDES := $(OSLMP_LOCAL_EXPORT_C_INCLUDES)
LOCAL_SRC_FILES := $(OSLMP_LOCAL_SRC_FILES)
LOCAL_CFLAGS += $(OSLMP_LOCAL_CFLAGS)
LOCAL_STATIC_LIBRARIES := \
    cxxdasp_static \
    cxxdasp_$(TARGET_ARCH_ABI)_static \
    $(CXXDASP_FFT_BACKEND_LIBS_$(TARGET_ARCH_ABI))

ifneq (, $(filter armeabi-v7a armeabi-v7a-hard, $(TARGET_ARCH_ABI)))
    LOCAL_ARM_NEON  := true
endif

include $(BUILD_SHARED_LIBRARY)


#
# MyNdkLibary-no-neon
#
LOCAL_PATH := $(PROJ_LOCAL_PATH)

include $(CLEAR_VARS)

LOCAL_MODULE    := MyNdkLibary-no-neon

ifneq (, $(filter armeabi-v7a armeabi-v7a-hard, $(TARGET_ARCH_ABI)))
LOCAL_C_INCLUDES := $(OSLMP_LOCAL_C_INCLUDES)
LOCAL_EXPORT_C_INCLUDES := $(OSLMP_LOCAL_EXPORT_C_INCLUDES)
LOCAL_SRC_FILES := $(OSLMP_LOCAL_SRC_FILES)
LOCAL_CFLAGS += $(OSLMP_LOCAL_CFLAGS)
LOCAL_STATIC_LIBRARIES := \
    cxxdasp_static \
    cxxdasp_$(TARGET_ARCH_ABI)-no-neon_static \
    cxxporthelper_static \
    $(CXXDASP_FFT_BACKEND_LIBS_$(TARGET_ARCH_ABI)-no-neon)

include $(BUILD_SHARED_LIBRARY)
else
# dummy
include $(BUILD_STATIC_LIBRARY)
endif


#
# Clear variables
#
OSLMP_LOCAL_C_INCLUDES :=
OSLMP_LOCAL_SRC_FILES :=
OSLMP_LOCAL_CFLAGS :=
OSLMP_LOCAL_EXPORT_C_INCLUDES :=

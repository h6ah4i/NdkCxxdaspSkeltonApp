Demo Android Studio project integrated with cxxdasp library
===

This is a demonstration purpose project how to use my Digital Signal Processing C++ library ([cxxdasp](https://github.com/h6ah4i/cxxdasp)) from Java Android app.

## Getting Started

1. Install some tools which are required to build [cxxdasp](https://github.com/h6ah4i/cxxdasp) library.
Please check the [WiKi of cxxdasp](https://github.com/h6ah4i/cxxdasp/wiki/getting_started#required-softwares-1).

2. Download source codes

  ```bash
  # clone this repository
  git clone git@github.com:h6ah4i/NdkCxxdaspSkeltonApp.git
  cd NdkCxxdaspSkeltonApp

  # clone submodule project (cxxdasp)
  git submodule init
  git submodule update

  # setup cxxdasp library
  ./ndklibrary/src/main/thirdparty/cxxdasp/android/dep_libs/download_dep_libs.sh
  ```

3. Build or import this project to Android Studio

  ```bash
  # build from terminal
  ./gradlew assembleRelease

  # --- OR ---

  # You can import this project to Android Studio!
  ```

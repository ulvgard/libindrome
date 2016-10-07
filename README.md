# Indrome library

Indrome library is a support- and warpper library for OpenCV. It provides 
convenient command line tools for executing a pipeline of image procesing. 

This library only provides partial wrapping of OpenCV. Abstractions are leaky.

# Building

To build libindrome you require

* CMake, tested with CMake 3.6
* C++ compiler (C++11 compatible). Tested with Clang 3.8

## Dependencies

libindrome depends on

* OpenCV
* [optional] gtest

Download the source code

```
git clone https://github.com/ulvgard/libindrome.git
cd libindrome
git submodule update --init
```

Configure and generate with CMake to a build directory.

```
mkdir build-indrome # do this out-of-source
cd build-indrome
cmake ../libindrome
```

There is one library target:

```
make indrome
```

There is a meta-target `tools` that build:

* `catvid`: a tool for opening a video and output frames to the pipeline
* `catimg`: a tool for opening an image and output the frame to the pipeline
* `chesscalib`: a tool for computing the intrinsic camera matrix from frames and output to the pipeline
* `baw`: a tool for converting frames in the pipeline to grey scale
* `resizevid`: a tool for resizing frames and output to the pipeline
* `showimg`: a tool for displaying a single frame and output to the pipeline
* `showvid`: a tool for displaying frames and output to the pipeline

# Examples

## Convert an image to grey and resize it

```
./catimg keypoints.jpg | ./baw | ./resizevid 480 320 | ./showimg
```

## Compute the intrinsic camera matrixk

```
./catvid MyChessboardRecording.mp4 | ./baw | ./resizevid 480 320 | ./chesscalib 9 7 | ./showvid > /dev/null
```


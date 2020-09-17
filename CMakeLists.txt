# 按惯例，cmake的版本
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# 项目名称
PROJECT(Cuda_function)
# cmake寻找cuda，这个要现在系统里面装好cuda，设置好cuda的环境参数啥的
FIND_PACKAGE(CUDA REQUIRED)
# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# 头文件路径，按需
INCLUDE_DIRECTORIES(
   /usr/local/include
   /home/cx/libtorch/include
    /usr/local/cuda/include
    /usr/include
    cudakenel/
    )
# 库文件路径，按需
LINK_DIRECTORIES(
    /usr/local/lib
    /home/cx/libtorch/lib
    /usr/local/cuda/lib64
    /usr/local/lib
    cudakenel/
    )

add_subdirectory(cudakenel)
set (EXTRA_LIBS ${EXTRA_LIBS} cudakenel)

ADD_EXECUTABLE(Cuda_function infer.cpp)

# add_library(Cuda_function SHARED infer.cpp) # 生成动态库或共享库

# 链接外部库，按需

TARGET_LINK_LIBRARIES(Cuda_function cudakenel )

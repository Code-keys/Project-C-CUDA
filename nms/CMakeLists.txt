# CMakeLists.txt for G4CU project
# 单独生成 一个NVCC文件 的动态链接库 文件 名字  ：       cuda_kenel

set(CU_name "nms_kernel")
project(${CU_name})

# required cmake version
cmake_minimum_required(VERSION 2.8)

# packages
find_package(CUDA)
# find_package(Numcpp)

include_directories ("${PROJECT_SOURCE_DIR}")
# include_directories ("${PROJECT_SOURCE_DIR}")

# nvcc flags
set(CUDA_NVCC_FLAGS -O3;-G;-g)

# SET(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS}; -gencode arch=compute_61,code=sm_61; -std=c++11;)
#set(CUDA_NVCC_FLAGS -gencode arch=compute_52,code=sm_52;-G;-g)

file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp *.cuh)
file(GLOB CURRENT_SOURCES  *.cpp *.cu)

source_group("Include" FILES ${CURRENT_HEADERS}) 
source_group("Source" FILES ${CURRENT_SOURCES}) 

message("builded with cuda mode")


#cuda_add_library(gpu STATIC ${CURRENT_HEADERS} ${CURRENT_SOURCES})
cuda_add_library(${CU_name} SHARED ${CURRENT_HEADERS} ${CURRENT_SOURCES})

CUDA_ADD_EXECUTABLE(${CU_name}.out  ${CURRENT_HEADERS} ${CURRENT_SOURCES})


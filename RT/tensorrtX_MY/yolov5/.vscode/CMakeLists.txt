cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(infer)


SET(CMAKE_BUILD_TYPE "Debug")
# SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/home/cx/libtorch/")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/home/cx/TensorRT/")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/local/")

find_package(Torch REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED)

# find_package(PythonLibs REQUIRED)


add_executable(infer infer.cpp)


target_link_libraries(infer "${TORCH_LIBRARIES}" "${OpenCV_LIBS}" "${Boost_LIBRARIES}")
set_property(TARGET infer PROPERTY CXX_STANDARD 11)

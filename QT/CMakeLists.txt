CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# 项目名称
set(project_name QT)

project(${project_name})
add_definitions(-fPIC)
add_definitions(-g)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Qt5 REQUIRED Widgets)
FIND_PACKAGE(CUDA REQUIRED)
FIND_PACKAGE(OpenCV 3  REQUIRED)

INCLUDE_DIRECTORIES(/usr /usr/local/Qt-5.9.0/include /usr/local/include /usr/local/cuda/include ${OpenCV_INCLUDE_DIRS} )
LINK_DIRECTORIES(../extra_lib ./extra_lib /usr/bin /usr/local/lib /usr/local/cuda/lib64 /usr/local/Qt-5.9.0/lib )
file(GLOB_RECURSE QRC_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/names.qrc)
set(QRC_SOURCE_FILES names.qrc)


SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON)
SET(CMAKE_AUTOUIC ON)

qt5_add_resources(RCC ${QRC_SOURCE_FILES})

qt5_wrap_cpp(mocfile mainwindow.h)
qt5_wrap_ui(uifiles mainwindow.ui)

add_executable(${project_name} 
        main.cpp darknet.h yolo_v2_class.hpp
        mainwindow.cpp mainwindow.h mainwindow.ui ${mocfile} ${RCC})

target_link_libraries(${project_name} 
        Qt5::Widgets 
        ${OpenCV_LIBS}
        ${CUDA_LIBS}
        libpthread.so.0
        darknet
        )











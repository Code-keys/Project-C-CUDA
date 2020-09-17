TEMPLATE = app 
# lib - 表示该工程建立一个库的makefile

DESTDIR += ../bin # 生成MAKEFILE目录

TARGET = qtest

CONFIG += console c++11\network #编译选项
CONFIG -= qt

OBJECTS_DIR += ../

HEADERS += \
    libcurl/curl/curl.h \
    libcurl/curl/curlbuild.h \
    libcurl/curl/curlrules.h \

SOURCES += mytest.cpp\
           main.cpp

RESOURCES += names.qrc

INCLUDEPATH += ./boost/include\
               src/thirdpart/include
LIBS += -LD:/codetest/libcurlcpp/opencv/lib/ -lopencv\
        -LD:/codetest/libcurlcpp/libcurl/lib/ -lws2_32\
        -LD:/codetest/libcurlcpp/libcurl/lib/ -lwldap32\
        -LD:/codetest/libcurlcpp/libcurl/lib/ -lopencv\
        -LD:/codetest/libcurlcpp/libcurl/lib/ -lzmq
LIBS += D:/codetest/libcurlcpp/libcurl/lib/libcurl.lib
LIBS += $$PWD/libcurl/lib/libcurl.lib\  # 只适用于windows静态库

DEFINES += USE_OPENSSL\
           CURL_STATICLIB



win32
{
    SOURCES += windows.cpp
}
else
{
    SOURCES += linux.cpp
}


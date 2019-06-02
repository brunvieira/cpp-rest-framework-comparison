cmake_minimum_required(VERSION 3.7)

set(PROJECT "cpputils")
project(${PROJECT})
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES cpputils.cpp cpputils.h)
add_library(${PROJECT} STATIC ${SOURCE_FILES})
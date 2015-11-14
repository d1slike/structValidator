cmake_minimum_required(VERSION 3.3)
project(StructValidator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp files/FileReader.cpp files/FileReader.h handlers/ErrorHandler.cpp handlers/ErrorHandler.h handlers/Validator.cpp handlers/Validator.h strings/StringUtil.cpp strings/StringUtil.h holders/KeyWordsArray.cpp holders/KeyWordsArray.h)
add_executable(StructValidator ${SOURCE_FILES})
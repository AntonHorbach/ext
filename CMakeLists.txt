cmake_minimum_required(VERSION 3.16)
project(filesystem)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(filesystem src/filesystem_utils.cpp src/EntryType.cpp src/EntryInfo.cpp)
cmake_minimum_required(VERSION 3.5)

project(multithread_file_write LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(multithread_file_write
    src/main.cpp
    src/taskthread.cpp
    src/taskthread.h
    src/datagenerator.cpp
    src/datagenerator.h
    src/filewriter.cpp
    src/filewriter.h
    src/thread_shared_data.h)

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
    src/threadshareddata.cpp
    src/threadshareddata.h
    src/data.h)

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(multithread_file_write Threads::Threads)
endif()

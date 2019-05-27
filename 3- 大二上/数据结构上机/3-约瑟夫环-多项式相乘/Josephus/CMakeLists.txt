cmake_minimum_required(VERSION 3.12)
project(Josephus)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Josephus
        CMakeLists.txt
        List_IDX.c
        List_IDX.h
        main.c)

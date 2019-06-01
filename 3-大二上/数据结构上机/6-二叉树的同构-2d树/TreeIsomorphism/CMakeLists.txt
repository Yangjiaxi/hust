cmake_minimum_required(VERSION 3.0.0)
project(TreeIsomorphic VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(TreeIsomorphic 
                Utils/Utils.h
                Utils/Utils.c 
                Tree/Tree.h 
                Tree/Tree.c
                main.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

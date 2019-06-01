cmake_minimum_required(VERSION 3.0.0)
project(Tran2Tree VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Tran2Tree 
        main.c
        Tree/Tree.h
        Tree/Tree.c
        utils.h
        utils.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

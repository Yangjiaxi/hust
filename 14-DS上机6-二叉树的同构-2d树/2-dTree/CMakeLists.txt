cmake_minimum_required(VERSION 3.0.0)
project(2-dTree VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(2-dTree 
                2-dTree/Tree.h 
                2-dTree/Tree.c 
                Utils/Utils.h 
                Utils/Utils.c 
                main.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

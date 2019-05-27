cmake_minimum_required(VERSION 3.0.0)
project(TreePlot VERSION 6655.1551.114514)

include(CTest)
enable_testing()

add_executable(TreePlot
            main.c 
            Tree/Tree.h
            Tree/Tree.c
            AvlTree/AvlTree.h 
            AvlTree/AvlTree.c
            # BST/BST.h
            # BST/BST.c
            TreePlot.h
            TreePlot.c
            UsefulFunc.h
            UsefulFunc.c)
        
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

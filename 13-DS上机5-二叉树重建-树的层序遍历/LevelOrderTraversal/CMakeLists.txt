cmake_minimum_required(VERSION 3.0.0)
project(LevelOrderTraversal VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(LevelOrderTraversal 
                Tree/tree.h 
                Tree/tree.c 
                AvlTree/AvlTree.h 
                AvlTree/AvlTree.c
                Queue/queue.h 
                Queue/queue.c 
                DoublyList/DoublyList.h 
                DoublyList/DoublyList.c 
                Utils/Utils.h 
                Utils/Utils.c
                main.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

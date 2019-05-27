cmake_minimum_required(VERSION 3.12)
project(PolyMultiply C)

set(CMAKE_C_STANDARD 11)

add_executable(PolyMultiply main.c list_ptr.c list_ptr.h Polynomial.c Polynomial.h)
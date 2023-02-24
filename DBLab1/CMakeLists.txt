cmake_minimum_required(VERSION 3.20)
project(DBLab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(DBLab1 main.cpp customer.cpp customer.h order.cpp order.h fileio.cpp fileio.h)

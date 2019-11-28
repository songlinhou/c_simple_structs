cmake_minimum_required(VERSION 3.14)
project(SimpleCStructures C)

set(CMAKE_C_STANDARD 11)

add_executable(SimpleCStructures main.c SPArrayList.c SPArrayList.h SPLinkedList.c SPLinkedList.h SPHashMap.c SPHashMap.h)
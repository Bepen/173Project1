cmake_minimum_required(VERSION 3.7)
project(Project1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp dfa.c nfa.c)
add_executable(Project1 ${SOURCE_FILES})
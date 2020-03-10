cmake_minimum_required(VERSION 3.15)
project(FileCleaner)

set(CMAKE_CXX_STANDARD 20)


add_executable(FileCleaner main.cpp)

target_link_libraries(FileCleaner stdc++fs)


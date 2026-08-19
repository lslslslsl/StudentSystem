cmake_minimum_required(VERSION 3.10)

project(StudentSystem)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(StudentSystem
    src/main.cpp
    src/Student.cpp
    src/StudentManager.cpp
    src/Menu.cpp
)
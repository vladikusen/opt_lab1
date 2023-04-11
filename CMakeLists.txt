cmake_minimum_required(VERSION 3.15)

project("lab1")

enable_language(CXX)
set(CMAKE_BUILD_TYPE Debug)
add_executable(lab1 
    main.cpp   
    analyser.cpp 
    analyser.h
    parser.h
    parser.cpp
)
cmake_minimum_required(3.8)

project(serialized-linked-list VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRCS
    src/main.cpp
    src/LinkedList.hpp
    src/LinkedList.cpp
    src/Parser.hpp
    src/Parser.cpp
)

add_executable(serializer ${SRCS})
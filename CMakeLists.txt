cmake_minimum_required(VERSION 3.8)

project(serialized-linked-list VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRCS
    src/main.cpp
    src/App.hpp
    src/App.cpp
    src/LinkedList.hpp
    src/LinkedListSerializer.hpp
    src/LinkedListSerializer.cpp
    src/Parser.hpp
    src/Parser.cpp
)

set(PTEST_SRCS
    test/TestParser.cpp
    test/TestUtils.hpp
    src/LinkedList.hpp
    src/LinkedListSerializer.hpp
    src/LinkedListSerializer.cpp
    src/Parser.hpp
    src/Parser.cpp
    include/TestFramework.h
)

set(STEST_SRCS
    test/TestSerializer.cpp
    test/TestUtils.hpp
    src/LinkedList.hpp
    src/LinkedListSerializer.hpp
    src/LinkedListSerializer.cpp
    src/Parser.hpp
    src/Parser.cpp
    include/TestFramework.h
)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra \
                        -O0 -g")
    if(NOT MINGW)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra-semi -fsanitize=address -fno-omit-frame-pointer")
    endif()
endif()


add_executable(serializer ${SRCS})
add_executable(parser_tests ${PTEST_SRCS})
add_executable(serializer_tests ${STEST_SRCS})
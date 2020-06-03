cmake_minimum_required(VERSION 3.9)

if(NOT CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

set(CMAKE_CXX_STANDARD 17)

project(openal-shortcircuit)

set(SOURCES
    src/ShortCircuit.cpp
    src/Router.cpp
)

add_library(openal-shortcircuit SHARED ${SOURCES})

if (MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
endif()

message (${PROJECT_SOURCE_DIR})
target_include_directories(openal-shortcircuit
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
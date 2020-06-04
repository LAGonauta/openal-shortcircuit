cmake_minimum_required(VERSION 3.9.4)
project(openal-shortcircuit VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE STREQUAL Debug)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT supported OUTPUT error)

    if(supported)
        message(STATUS "IPO / LTO enabled")
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    else()
        message(STATUS "IPO / LTO not supported: <${error}>")
    endif()
endif()

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
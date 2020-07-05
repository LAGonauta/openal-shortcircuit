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
    src/ALRouter.cpp
    src/ALManager.cpp
    src/ShortCircuitedALMethods.cpp
    src/ALCRouter.cpp
    src/ShortCircuitedALCMethods.cpp
    src/Utils.cpp
    src/XRamManager.cpp
)

add_library(openal-shortcircuit SHARED ${SOURCES})

add_definitions(-DBUILDING_DLL)

if (MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
endif()

target_include_directories(openal-shortcircuit
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

if (BUILD_TESTER)
    add_executable(tester src/tester.cpp)
    target_include_directories(tester
        PRIVATE
            ${PROJECT_SOURCE_DIR}/include
    )
    target_link_libraries(tester openal-shortcircuit)
endif()

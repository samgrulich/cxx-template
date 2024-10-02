cmake_minimum_required(VERSION 3.10)

project(alg_hw01
    VERSION 0.0.1
    DESCRIPTION "Algoritmizace homework 01"
    LANGUAGES CXX
)

include(CTest)
add_subdirectory(libs/googletest)

if (NOT CMAKE_BUILD_TYPE) 
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_library(cxx_setup INTERFACE)
target_compile_options(cxx_setup INTERFACE -Wpedantic -Wextra)
target_compile_features(cxx_setup INTERFACE cxx_std_20)
target_include_directories(cxx_setup INTERFACE "${PROJECT_SOURCE_DIR}/src/")

add_subdirectory(src)
add_subdirectory(tests)

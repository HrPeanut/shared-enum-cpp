cmake_minimum_required(VERSION 3.16)
project(trak)

set(CMAKE_CXX_STANDARD 17)

add_library(trak INTERFACE)
target_sources(trak INTERFACE
        ${PROJECT_SOURCE_DIR}/include/trak/shared_enum.hpp
        ${PROJECT_SOURCE_DIR}/include/trak/shared_enum.hpp)
target_include_directories(trak INTERFACE include)

add_subdirectory(test)
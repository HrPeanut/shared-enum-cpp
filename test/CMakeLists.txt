cmake_minimum_required(VERSION 3.15)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG        release-1.10.0)
FetchContent_MakeAvailable(googletest)

add_executable(trak_test shared_enum_test.cpp)
target_link_libraries(trak_test PRIVATE gtest_main trak)
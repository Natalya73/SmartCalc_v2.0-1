cmake_minimum_required(VERSION 3.22)
project(CPP3_s21_SmartCalc_0)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
       googletest
       URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(.)

add_executable(CPP3_s21_SmartCalc_0
       ../Smart_calculator_Qt/model/model.h
       ../Smart_calculator_Qt/model/model.cpp
       ../test.cpp

)

set_target_properties(CPP3_s21_SmartCalc_0 PROPERTIES LINKER_LANGUAGE CXX)

target_compile_options(CPP3_s21_SmartCalc_0 PRIVATE -g -std=c++17 -Wall -Werror -Wextra -Wpedantic -O3)

target_link_libraries(
       CPP3_s21_SmartCalc_0
       GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(CPP3_s21_SmartCalc_0)

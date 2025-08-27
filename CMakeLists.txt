cmake_minimum_required(VERSION 3.16)
project(StackProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------
# Source files
# ---------------------------
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

set(SOURCES
    ${SRC_DIR}/stack.cpp
)

add_library(stack_lib ${SOURCES})
target_include_directories(stack_lib PUBLIC ${SRC_DIR})

# ---------------------------
# Executables (main programs)
# ---------------------------
add_executable(simple_stack simple_stack.cpp)
target_link_libraries(simple_stack PRIVATE stack_lib)

add_executable(stack_array_scatch stack_array_scatch.cpp)
target_link_libraries(stack_array_scatch PRIVATE stack_lib)

# ---------------------------
# GoogleTest (cross-platform)
# ---------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.15.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(stack_test ${TEST_DIR}/stack_test.cpp)
target_link_libraries(stack_test PRIVATE stack_lib GTest::gtest_main)

add_test(NAME StackUnitTest COMMAND stack_test)

# ---------------------------
# Optional warnings
# ---------------------------
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(stack_lib PRIVATE -Wall -Wextra -pedantic -O2)
    target_compile_options(stack_test PRIVATE -Wall -Wextra -pedantic -O2)
endif()

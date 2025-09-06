cmake_minimum_required(VERSION 3.16)
project(StackProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----- Paths
set(SRC_DIR  ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

# ----- Library berisi semua implementasi stack
add_library(stack_lib
    ${SRC_DIR}/stack.cpp
    ${SRC_DIR}/stack_linked_list.cpp
    ${SRC_DIR}/stack_templates_implement.cpp
)

# kalau ada header di src/, publish include path-nya
target_include_directories(stack_lib PUBLIC ${SRC_DIR})

# ----- (Opsional) Warning flags
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(stack_lib PRIVATE -Wall -Wextra -pedantic -O2)
endif()

# ----- GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.15.0.zip
)
# Hindari install step dari gtest
set(INSTALL_GTEST OFF CACHE BOOL "Disable install" FORCE)
FetchContent_MakeAvailable(googletest)

# enable_testing()

# test/stack_test.cpp harus ada
#add_executable(stack_test ${TEST_DIR}/stack_test.cpp)
#target_link_libraries(stack_test PRIVATE stack_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(stack_test)

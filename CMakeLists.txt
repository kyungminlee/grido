cmake_minimum_required(VERSION 3.27)
project(grido)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(GRIDO_BUILD_TESTS "Build tests" ON)

include(cmake/CPM.cmake)
CPMAddPackage("gh:boost-ext/ut@2.1.1")

if(GRIDO_BUILD_TESTS)
  enable_testing()
endif()

add_subdirectory(src)

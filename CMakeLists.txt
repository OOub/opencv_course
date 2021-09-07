cmake_minimum_required(VERSION 3.12)
project(opencvcourse LANGUAGES CXX)

# setting default build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/build)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# build with C++14
set(CMAKE_CXX_STANDARD 14)
add_subdirectory(applications)

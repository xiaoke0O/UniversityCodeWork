cmake_minimum_required(VERSION 3.15)
project(forward_intersection)

set(CMAKE_CXX_STANDARD 14)

add_executable(forward_intersection main.cpp)

find_package( OpenCV REQUIRED )
target_link_libraries( forward_intersection ${OpenCV_LIBS} )
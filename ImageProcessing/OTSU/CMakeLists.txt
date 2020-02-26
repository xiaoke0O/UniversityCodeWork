cmake_minimum_required(VERSION 3.15)
project(OTSU)
set(CMAKE_CXX_STANDARD 14)
find_library(OpenCV REQUIRD)
add_executable(OTSU OTSU.cpp OTSU.h main.cpp)

target_link_libraries(OTSU ${OpenCV_LIBS})
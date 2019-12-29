cmake_minimum_required(VERSION 3.15)
project(relative_orientation)


set(CMAKE_CXX_STANDARD 14)
add_executable(relative_orientation main.cpp)
find_package(OpenCV REQUIRED)
target_link_libraries(relative_orientation ${OpenCV_LIBS})
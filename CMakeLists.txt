cmake_minimum_required(VERSION 3.16)
project(order)

set(CMAKE_CXX_STANDARD 17)

add_executable(order main.cpp)

add_executable(Divide_Merge Divide_Merge.cpp)
add_executable(linear_time_select linear_time_select.cpp)
add_executable(kth_element kth_element.cpp)
add_executable(generate_data generate_data.cpp)
cmake_minimum_required(VERSION 2.8)
project(boost_test)

add_compile_options(-std=c++14)

find_package(Boost REQUIRED COMPONENTS timer)
find_package(Eigen3 REQUIRED)

include_directories(
${Boost_INCLUDE_DIRS}
)

add_executable(cpu_timer_w_qr cpu_timer_w_qr.cpp)

target_link_libraries(cpu_timer_w_qr
${Boost_LIBRARIES}
)


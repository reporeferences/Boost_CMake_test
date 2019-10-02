cmake_minimum_required(VERSION 2.8)
project(boost_test)

add_compile_options(-std=c++14)

find_package(Boost REQUIRED COMPONENTS timer)

include_directories(
${Boost_INCLUDE_DIRS}
)

add_executable(Main main.cpp)

target_link_libraries(Main
${Boost_LIBRARIES}
)


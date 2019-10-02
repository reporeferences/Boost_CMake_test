cmake_minimum_required(VERSION 2.8)
project(boost_test)

add_compile_options(-std=c++14)

find_package(Boost REQUIRED COMPONENTS timer)

include_directories(
${Boost_INCLUDE_DIRS}
)

add_executable(test_mine test_mine.cpp)
add_executable(cpu_timer_info cpu_timer_info.cpp)
target_link_libraries(test_mine
${Boost_LIBRARIES}
)
target_link_libraries(cpu_timer_info
${Boost_LIBRARIES}
)

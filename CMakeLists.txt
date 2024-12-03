cmake_minimum_required(VERSION 3.30)

project(
        AoC2024
        VERSION 1.0.0
        DESCRIPTION ""
        LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 26)

add_subdirectory(vendor)
add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)

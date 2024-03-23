cmake_minimum_required(VERSION 3.20)

project(algo_arena LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(benchmark CONFIG REQUIRED)

add_subdirectory(benchmarks)
cmake_minimum_required(VERSION 3.16)
project(fast_csv_normalizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(csv_normalizer src/main.cpp)
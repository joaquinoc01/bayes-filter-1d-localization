cmake_minimum_required(VERSION 3.10)
project(bayes_filter)

set(CMAKE_CXX_STANDARD 17)

# Add the include directory
include_directories(include)

# Add the executable
add_executable(bayes_filter
    src/bayes_filter.cpp
)
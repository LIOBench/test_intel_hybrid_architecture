cmake_minimum_required(VERSION 3.21)
project(test_intel_hybrid_architecture)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -g -Wall")
set(CMAKE_CXX_STANDARD 17)
#SET(CMAKE_BUILD_TYPE "Debug")

find_package(OpenMP QUIET)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})

add_executable(baseline baseline.cpp)
target_link_libraries(baseline armadillo)

add_executable(baseline_native baseline.cpp)
target_link_libraries(baseline_native armadillo)
target_compile_options(baseline_native PRIVATE -march=native)
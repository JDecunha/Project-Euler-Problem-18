#CMakeLists file for JigRBEFitting
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project (SamsCodingProblem VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD "17")

include_directories(${CMAKE_SOURCE_DIR}/include)

### Configure executable
add_executable(SamsCodingProblem SamsCodingProblem.cc)



cmake_minimum_required(VERSION 3.12)

project(concepts VERSION 0.1 DESCRIPTION "Testing out C++ concepts" LANGUAGES CXX)

add_executable(concepts concepts.cpp)
target_compile_features(concepts PUBLIC cxx_std_20)

find_package(fmt)
target_link_libraries(concepts fmt::fmt)

add_custom_target(run COMMAND ${CMAKE_BINARY_DIR}/concepts DEPENDS concepts)

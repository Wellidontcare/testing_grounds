cmake_minimum_required(VERSION 3.14)

project(test_eigen)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
add_executable(test_eigen test_eigen.cpp)

target_link_libraries(test_eigen Eigen3::Eigen)

add_custom_target(run COMMAND ${CMAKE_BINARY_DIR}/test_eigen DEPENDS ${CMAKE_BINARY_DIR}/test_eigen)

cmake_minimum_required(VERSION 3.12)
set(LIBRARY_NAME add_lib)

project(${LIBRARY_NAME})

add_library(${LIBRARY_NAME} SHARED ${LIBRARY_NAME}/src/add.cpp)

execute_process(COMMAND ctypesgen -lbuild/lib${LIBRARY_NAME}.so ${LIBRARY_NAME}/include/add.h -o ${LIBRARY_NAME}.py)

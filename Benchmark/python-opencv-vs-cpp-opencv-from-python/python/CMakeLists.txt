pybind11_add_module(pythonopencvvscppopencvfrompython_python python-opencv-vs-cpp-opencv-from-python_python.cpp)

find_package(OpenCV REQUIRED)

target_link_libraries(pythonopencvvscppopencvfrompython_python PUBLIC python-opencv-vs-cpp-opencv-from-python ${OpenCV_LIBS})

target_include_directories(pythonopencvvscppopencvfrompython_python PUBLIC ${OpenCV_INCLUDE_DIRS})
set_target_properties(pythonopencvvscppopencvfrompython_python PROPERTIES OUTPUT_NAME pythonopencvvscppopencvfrompython)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_custom_command(TARGET pythonopencvvscppopencvfrompython_python POST_BUILD
  COMMAND ln -sf ${CMAKE_BINARY_DIR}/compile_commands.json . 
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Linking compile commands for target python-opencv-vs-cpp-opencv-from-python_python"
)

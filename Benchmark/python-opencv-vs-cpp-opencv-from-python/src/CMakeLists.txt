add_library(python-opencv-vs-cpp-opencv-from-python python-opencv-vs-cpp-opencv-from-python.cpp)
target_include_directories(python-opencv-vs-cpp-opencv-from-python PUBLIC
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_custom_command(TARGET python-opencv-vs-cpp-opencv-from-python POST_BUILD
  COMMAND ln -sf ${CMAKE_BINARY_DIR}/compile_commands.json .
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Linking compile commands for target python-opencv-vs-cpp-opencv-from-python"
)

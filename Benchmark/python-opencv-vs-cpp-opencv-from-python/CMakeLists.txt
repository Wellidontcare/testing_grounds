cmake_minimum_required(VERSION 3.9)

# Set a name and a version number for your project:
project(python-opencv-vs-cpp-opencv-from-python VERSION 0.0.1 LANGUAGES CXX)

# Initialize some default paths
include(GNUInstallDirs)

# Define the minimum C++ standard that is required
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Compilation options
set(BUILD_PYTHON ON CACHE BOOL "Enable building of Python bindings")

# compile the library
add_subdirectory(src)

if(BUILD_PYTHON)
  # Add Python bindings
  find_package(pybind11)
  add_subdirectory(python)
endif()

# Add an alias target for use if this project is included as a subproject in another project
add_library(python-opencv-vs-cpp-opencv-from-python::python-opencv-vs-cpp-opencv-from-python ALIAS python-opencv-vs-cpp-opencv-from-python)

# Install targets and configuration
install(
  TARGETS python-opencv-vs-cpp-opencv-from-python
  EXPORT python-opencv-vs-cpp-opencv-from-python-config
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
  EXPORT python-opencv-vs-cpp-opencv-from-python-config
  NAMESPACE python-opencv-vs-cpp-opencv-from-python::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/python-opencv-vs-cpp-opencv-from-python
)

install(
  DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# This prints a summary of found dependencies
include(FeatureSummary)
feature_summary(WHAT ALL)

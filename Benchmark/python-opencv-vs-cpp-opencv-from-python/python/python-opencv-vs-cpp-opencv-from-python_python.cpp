#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "python-opencv-vs-cpp-opencv-from-python/python-opencv-vs-cpp-opencv-from-python.hpp"

namespace py = pybind11;

namespace pythonopencvvscppopencvfrompython {

PYBIND11_MODULE(pythonopencvvscppopencvfrompython, m)
{
  m.doc() = "Python Bindings for python_opencv_vs_cpp_opencv_from_python";
  m.def("image_process", &image_process, "Counts the connected components of the image");
}

} // namespace pythonopencvvscppopencvfrompython

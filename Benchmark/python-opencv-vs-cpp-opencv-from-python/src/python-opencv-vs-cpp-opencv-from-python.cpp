#include "python-opencv-vs-cpp-opencv-from-python/python-opencv-vs-cpp-opencv-from-python.hpp"
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>

namespace pythonopencvvscppopencvfrompython {

int image_process(std::string file_path)
{
  auto image = cv::imread(file_path, cv::IMREAD_GRAYSCALE);
  cv::Mat threshholded;
  cv::threshold(image, threshholded, 255, 255, cv::THRESH_OTSU);
  cv::Mat labels;
  return cv::connectedComponents(threshholded, labels);
}

} // namespace pythonopencvvscppopencvfrompython

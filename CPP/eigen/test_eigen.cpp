#include <Eigen/Core>
#include <Eigen/SVD>
#include <Eigen/src/Core/Matrix.h>
#include <Eigen/src/SVD/SVDBase.h>
#include <iostream>

auto main() -> int {
  Eigen::Matrix2d T;
  // clang-format off
  T << 1, 2,
       3, 4;
  auto SVD = T.bdcSvd();
  std::cout << SVD.computeU() << "\n" << SVD.singularValues() << "\n" << SVD.computeV();
}

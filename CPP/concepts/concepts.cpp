#include <algorithm>
#include <bits/chrono.h>
#include <cassert>
#include <chrono>
#include <concepts>
#include <execution>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iostream>
#include <iterator>
#include <pstl/glue_execution_defs.h>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

static auto allocations = 0;
static auto allocations_total = 0;

void* operator new(size_t bytes){
  std::cout << "Allocating " << bytes << " bytes!\n";
  allocations++;
  allocations_total++;
  return malloc(bytes);
}

void operator delete(void* mem) noexcept {
  free(mem);
  allocations--;
}

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <typename T>
concept HasColumns = requires(T object) {
                     { object.cols() } -> std::integral;
                   };

template <typename T>
concept HasRows = requires(T object) {
                      { object.rows() } -> std::integral;
                    };

template <typename T>
concept ArithmeticReference =
    std::is_reference_v<T> && std::is_arithmetic_v<std::remove_reference_t<T>>;

template <typename T>
concept HasRandomAccess = requires(T object) {
                            { object(0, 0) } -> ArithmeticReference;
                          };

template <typename T>
concept Matrix2DLike = HasColumns<T> && HasRows<T> && HasRandomAccess<T> &&
                       std::is_copy_assignable_v<T>;

auto exec_policy = std::execution::par_unseq;

template <std::integral SizeType, Arithmetic ValueType> class Matrix2D {
  SizeType width_;
  SizeType height_;

  ValueType *data_;

public:
  Matrix2D() : width_(0), height_(0), data_(nullptr){};
  Matrix2D(SizeType rows, SizeType cols, ValueType value)
      : width_(cols), height_(rows), data_(new ValueType[rows * cols]) {
    std::fill_n(exec_policy, data_, rows * cols, value);
  }

  Matrix2D(SizeType rows, SizeType cols,
           std::initializer_list<ValueType> values)
      : width_(cols), height_(rows), data_(new ValueType[rows * cols]) {
    assert(values.size() == rows * cols && "Matrix size does not match data");
    std::copy(exec_policy, std::begin(values), std::end(values), data_);
  }

  Matrix2D(const Matrix2D &other)
      : width_(other.width_), height_(other.height_),
        data_(new decltype(other(0, 0))[other.width_ * other.height_]){
    std::copy_n(other.data_, size(), data_);
  };

  Matrix2D(Matrix2D &&other)
      : width_(std::move(other.width_)), height_(std::move(other.height_)),
        data_(std::move(other.data_)){};
  ~Matrix2D() {
    delete[] data_;
  }

  friend void swap(Matrix2D& first, Matrix2D& second){
    std::swap(first.width_, second.width_);
    std::swap(first.height_, second.height_);
    std::swap(first.data_, second.data_);
  }

  auto operator=(Matrix2D other) -> Matrix2D& {
    if(this == &other){
      return *this;
    }
    swap(*this, other);
    return *this;
  }

  auto size() -> SizeType { return width_ * height_; }

  auto begin() {
    return this->data_;
  }
  
  auto begin() const {
    return this->data_;
  }

  auto end() {
    return this->data_ + (this->width_ * this->height_);
  }
  
  auto end() const {
    return this->data_ + (this->width_ * this->height_);
  }

  auto rows() const -> SizeType {
    return width_;
  }
  auto cols() const -> SizeType {
    return height_;
  }

  auto operator()(SizeType x, SizeType y) const -> ValueType& {
    return data_[x + y * width_];
  }

  auto dot(const Matrix2D &other) -> Matrix2D {
    assert(this->rows() == other.cols() && "Matrix sizes do not match");
    Matrix2D result(rows(), other.cols(), ValueType{});
    for (SizeType col = 0; col < other.cols(); ++col) {
      for (SizeType row = 0; row < rows(); ++row) {
        for (SizeType k = 0; k < other.cols(); ++k) {
          result(row, col) += (*this)(row, k) * other(k, col);
        }
      }
    }
    return result;
  }

  auto operator+(const Matrix2D &other) -> Matrix2D {
    assert(this->rows() == other.rows() && this->cols() == other.cols() &&
           "Matrix size missmatch on addition (matrices must be equal size)");
    return binary_op_copy(other, ::std::plus<ValueType>());
  }

  auto operator-(const Matrix2D &other) -> Matrix2D {
    assert(this->rows() == other.rows() && this->cols() == other.cols() &&
           "Matrix size missmatch on addition (matrices must be equal size)");
    return binary_op_copy(other, ::std::minus<ValueType>());
  }

  auto operator*(const Matrix2D &other) -> Matrix2D {
    assert(this->rows() == other.rows() && this->cols() == other.cols() &&
           "Matrix size missmatch on addition (matrices must be equal size)");
    return binary_op_copy(other, ::std::multiplies<ValueType>());
  }

  auto operator/(const Matrix2D &other) -> Matrix2D {
    assert(this->rows() == other.rows() && this->cols() == other.cols() &&
           "Matrix size missmatch on addition (matrices must be equal size)");
    return binary_op_copy(other, ::std::divides<ValueType>());
  }

  auto operator-() -> Matrix2D {
    Matrix2D result(rows(), cols(), ValueType{});
    std::transform(exec_policy, std::begin(result), std::end(result), [](auto v){return -v;});
    return result;
  }
  
  auto operator+=(const Matrix2D& other) -> Matrix2D& {
      return binary_op_in_place(other, ::std::plus<ValueType>());
  }
  
  auto operator-=(const Matrix2D& other) -> Matrix2D& {
      return binary_op_in_place(other, ::std::minus<ValueType>());
  }

  auto operator*=(const Matrix2D &other) -> Matrix2D & {
      return binary_op_in_place(other, ::std::multiplies<ValueType>());
  }

  auto operator/=(const Matrix2D &other) -> Matrix2D & {
      return binary_op_in_place(other, ::std::divides<ValueType>());
  }

  friend std::ostream& operator<<(std::ostream& stream, const Matrix2D& mat){
    auto num_width = std::to_string(*std::max_element(mat.begin(), mat.end())).size();
    stream << "[";
    size_t r = 0;
    auto mat_size = mat.width_*mat.height_;
    for(auto&& val : mat){
      r++;
      stream << " " << std::setw(num_width) << val;
      if(!(r % mat.width_) && r <= mat_size-1){
        stream << "\n ";
      }
    }
    stream << " ]";
    stream << std::resetiosflags(std::ios::showbase);
    return stream;
  }

private:
  auto binary_op_copy(const Matrix2D &other,
                 std::function<ValueType(ValueType, ValueType)> op)
      -> Matrix2D {
    assert(this->rows() == other.rows() && this->cols() == other.cols() &&
           "Matrix sizes do not match (binary operation requires matrices of "
           "same size)");
    Matrix2D result(rows(), cols(), ValueType{});
    std::transform(exec_policy, std::begin(*this), std::end(*this),
                   std::begin(other), std::begin(result),
                   [=](auto a, auto b) { return op(a, b); });
    return result;
  }
  
  auto binary_op_in_place(const Matrix2D &other,
                 std::function<ValueType(ValueType, ValueType)> op)
      -> Matrix2D& {
    assert(this->rows() == other.rows() && this->cols() == other.cols() &&
           "Matrix sizes do not match (binary operation requires matrices of "
           "same size)");
    std::transform(exec_policy, std::begin(*this), std::end(*this),
                   std::begin(other), std::begin(*this),
                   [=](auto a, auto b) { return op(a, b); });
    return *this;
  }
};

template <Matrix2DLike Matrix>
Matrix pad(const Matrix &mat,
           std::remove_const_t<decltype(mat.rows())> pad_size,
           std::remove_reference_t<decltype(mat(0, 0))> pad_value = 0) {
  Matrix padded(mat.rows() + 2 * pad_size, mat.cols() + 2 * pad_size,
                pad_value);
  for (decltype(mat.rows()) y = 0; y < mat.rows(); ++y) {
    for (decltype(mat.cols()) x = 0; x < mat.cols(); ++x) {
      padded(x + pad_size, y + pad_size) = mat(x, y);
    }
  }
  return padded;
}

auto main() -> int {
  {
  auto start = std::chrono::high_resolution_clock::now();
  int w, h;
  std::cout << "W: ";
  std::cin >> w;
  std::cout << "H: ";
  std::cin >> h;
  float start_value;
  std::cout << "Start Value: ";
  std::cin >> start_value;
  Matrix2D mat2(w, h, start_value);
  Matrix2D res(w, h, decltype(start_value){});
  for(int i = 0; i < 100; ++i){
    res += mat2;
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "\n" << res << "\n";
  std::cout << "Policy: " << typeid(exec_policy).name() << "Took: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                     start)
                   .count()
            << "ms\n";
  }
  std::cout << "Uncleaned: " << allocations << "\n";
  std::cout << "Allocations: " << allocations_total << "\n";
}

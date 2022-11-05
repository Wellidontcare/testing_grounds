#include <initializer_list>
#include <ios>
#include <iterator>
#include <iostream>
#include <utility>
#include <iomanip>
#include <vector>
#include <concepts>
#include <type_traits>
#include <unordered_map>
#include <algorithm>
#include <cassert>

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
concept Matrix2DLike = HasColumns<T> && HasRows<T> && HasRandomAccess<T>;

template <std::integral SizeType, Arithmetic ValueType> class Matrix2D {
  static std::unordered_map<void *, size_t> references_;
  SizeType width_;
  SizeType height_;

  ValueType *data_;

public:
  Matrix2D() : width_(0), height_(0), data_(nullptr){};
  Matrix2D(SizeType rows, SizeType cols, ValueType value)
      : width_(cols), height_(rows), data_(new ValueType[rows * cols]) {
    references_[data_]++;
    std::fill_n(data_, rows * cols, value);
  }

  Matrix2D(SizeType rows, SizeType cols,
           std::initializer_list<ValueType> values)
      : width_(cols), height_(rows), data_(new ValueType[rows * cols]) {
    assert(values.size() == rows * cols && "Matrix size does not match data");
    std::copy(std::begin(values), std::end(values), data_);
    references_[data_]++;
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
    if (references_[data_] == 1) {
      references_.erase(data_);
    }
  }

  Matrix2D &operator=(const Matrix2D &other) {
    if(this == &other){
      return *this;
    }
    width_ = other.width_;
    height_ = other.height_;
    if(data_ != other.data_ && references_[data_] == 1){
      references_.erase(references_.find(data_));
      delete[] data_;
      data_ = other.data_;
    }
    references_[data_]++;
    return *this;
  }

  Matrix2D& operator=(Matrix2D&& other){
    this->width_ = std::move(other.width_);
    this->height_ = std::move(other.height_);
    if(data_ != other.data_ && references_[data_] == 1){
      references_.erase(references_.find(data_));
      delete[] data_;
      this->data_ = std::move(other.data_);
    }
    this->references_[data_]++;
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

  auto operator*(const Matrix2D &other) -> Matrix2D {
    assert(this->rows() == other.cols() && "Matrix sizes do not match");
    Matrix2D result(rows(), other.cols(), ValueType{});
      for(SizeType col = 0; col < other.cols(); ++col){
        for(SizeType row = 0; row < rows(); ++row){
        for(SizeType k = 0; k < other.cols(); ++k){
          result(row, col) += (*this)(row, k)*other(k, col);
        }
      }
    }
    return result;
  }

  auto operator+(const Matrix2D& other) -> Matrix2D {
    assert(this->rows() == other.rows() && this->cols() == other.cols() &&
           "Matrix size missmatch on addition (matrices must be equal size)");
    Matrix2D result(rows(), cols(), 0);
    for(SizeType y = 0; y < rows(); ++y){
      for(SizeType x = 0; x < cols(); ++x){
        result(x, y) = (*this)(x, y) + other(x, y);
      }
    }
    return result;
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
};

template<std::integral SizeType, Arithmetic PixelType>
std::unordered_map<void*, size_t> Matrix2D<SizeType, PixelType>::references_ = std::unordered_map<void*, size_t>{};

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
  Matrix2D mat2(3, 3, {1, 2, 3,
                       4, 5, 6,
                       7, 8, 9});
  std::cout << pad(mat2, 1) + Matrix2D(5, 5, 1) << "\n";
}

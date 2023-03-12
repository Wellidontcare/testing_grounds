#include <cstddef>
#include <cstdint>

struct Image {
  uint16_t* data;
  size_t rows;
  size_t cols;
};

struct RoI {
  int x, y;
  int w, h;
};

extern "C" void rc_sum(Image image, RoI roi, uint16_t* row_sum_result, uint16_t* col_sum_result){
  auto roi_x = roi.x, roi_y = roi.y;
  auto roi_width = roi.w, roi_height = roi.h;
  auto image_ptr = image.data;
  auto roi_top = (roi_y);
  auto roi_bottom = (roi_y + roi_height);
  auto roi_left = (roi_x);
  auto roi_right = (roi_x + roi_width);
  for(int y = roi_top; y < roi_bottom; ++y){
      for(int x = roi_left; x < roi_right; ++x){
          row_sum_result[x - roi_left] += image_ptr[x + y*image.cols];
          col_sum_result[y - roi_top] += image_ptr[x + y*image.cols];
      }
  }
}

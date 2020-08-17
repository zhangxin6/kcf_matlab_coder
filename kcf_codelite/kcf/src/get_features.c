#include "p_def.h"
extern float a[box_p];

void get_features(const unsigned short im[box_p], const float cos_window[box_p], float x[box_p])
{
  float y;
  int k;
  int b_k;
  y = 0;
  for (k = 0; k < box_p; k++) {
    y += im[k];
  }
  y /= box_p;
  for (k = 0; k < box_p; k++) {
    a[k] = (im[k] - y) / 255.0 ;
  }
  for (k = 0; k < box_w; k++) {
    for (b_k = 0; b_k < box_h; b_k++) {
      x[b_k + box_h * k] = a[b_k + box_h * k] * cos_window[b_k + box_h * k];
    }
  }
}

#include "p_def.h"
#include <math.h>
void circshift(float a[box_p],float b[box_p],int shf[2]);
void ndgrid(const float varargin_1[box_h], const float varargin_2[box_w], float varargout_1[box_p], float varargout_2[box_p]);
void power(const float a[box_p], float y[box_p]);
void b_exp(float x[box_p]);

extern float b[box_p];
extern float rs[box_p];
extern float cs[box_p];

void gaussian_shaped_labels(float labels[box_p])
{
  int i0;
  int shf[2];
  float dv9[box_h];
  float dv10[box_w];
  float output_sigma;
  output_sigma = sqrt(gt2 * gt3) * output_sigma_factor / cell_size;
  for (i0 = 0; i0 < box_h; i0++) {
    dv9[i0] = -floor(box_h / 2.0) + i0 + 1;
  }
  for (i0 = 0; i0 < box_w; i0++) {
    dv10[i0] = -floor(box_w / 2.0) + i0 + 1;
  }
  ndgrid(dv9, dv10, rs, cs);
  power(rs, labels);
  power(cs, rs);
  for (i0 = 0; i0 < box_p; i0++) {
    labels[i0] = -0.5 /(output_sigma * output_sigma) * (labels[i0] + rs[i0]);
  }
  b_exp(labels);
  shf[0] = 1 - floor(box_h / 2);
  shf[1] = 1 - floor(box_w / 2);
  circshift(labels,b,shf);
}

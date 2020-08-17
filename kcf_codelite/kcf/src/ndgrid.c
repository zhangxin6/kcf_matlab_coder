#include "p_def.h"

void ndgrid(const float varargin_1[box_h], const float varargin_2[box_w], float varargout_1[box_p], float varargout_2[box_p])
{
  int k;
  int b_k;
  for (k = 0; k < box_w; k++) {
    for (b_k = 0; b_k < box_h; b_k++) {
      varargout_1[b_k + box_h * k] = varargin_1[b_k];
    }
  }

  for (k = 0; k < box_w; k++) {
    for (b_k = 0; b_k < box_h; b_k++) {
      varargout_2[b_k + box_h * k] = varargin_2[k];
    }
  }
}

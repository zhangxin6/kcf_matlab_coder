#include "p_def.h"
#include <math.h>

void get_subwindow(const unsigned short im[im_p], const int pos[2], unsigned short out[box_p])
{
  int i;
  int xs[box_w];
  int ys[box_h];
  int i1;
  for (i = 0; i < box_w; i++) {
    xs[i] = floor(pos[1]) + 1 + i - floor(box_w/2);
  }
  for (i = 0; i < box_h; i++) {
    ys[i] = floor(pos[0]) + 1 + i - floor(box_h/2);
  }
  for (i = 0; i < box_w; i++) {
    if (xs[i] < 1) {
      xs[i] = 1;
    }
    if (xs[i] > im_w) {
      xs[i] = im_w;
    }
  }
  for (i = 0; i < box_h; i++) {
    if (ys[i] < 1) {
      ys[i] = 1;
    }
    if (ys[i] > im_h) {
      ys[i] = im_h;
    }
  }
  for (i = 0; i < box_w; i++) {
    for (i1 = 0; i1 < box_h; i1++) {
      out[i1 + box_h * i] = im[(ys[i1] - 1) + im_h * (xs[i] - 1)];
    }
  }
}

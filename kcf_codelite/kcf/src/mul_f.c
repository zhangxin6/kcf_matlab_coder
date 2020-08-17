#include "p_def.h"

void mul_f(creal_T1 p1f[],creal_T1  p2f[], creal_T1 outf[])
{
  int ii,jj;

  for (jj = 0; jj < box_h; jj++) {
    for (ii = 0; ii < box_w; ii++) {
      outf[ii + box_w * jj].re = p1f[ii + box_w * jj].re * p2f[ii + box_w * jj].re -
        p1f[ii + box_w * jj].im * p2f[ii + box_w * jj].im;
      outf[ii + box_w * jj].im = p1f[ii + box_w * jj].re * p2f[ii + box_w * jj].im +
        p1f[ii + box_w * jj].im * p2f[ii + box_w * jj].re;
    }
  }
}

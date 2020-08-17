#include <math.h>
#include "p_def.h"

void b_exp(float x[box_p])
{
  int k;
  for (k = 0; k < box_p; k++) {
    x[k] = exp(x[k]);
  }
}


void c_exp(creal_T1 x[box_p])
{
  int k;
  float x_re;
  float r;
  for (k = 0; k < box_p; k++) {
    r = exp(x[k].re / 2.0);
    x_re = r * (r * cos(x[k].im));
    r *= r * sin(x[k].im);
    x[k].re = x_re;
    x[k].im = r;
  }
}

#include "p_def.h"

void div_f(creal_T1 p1f[],creal_T1  p2f[], creal_T1 outf[])
{
  int jj;
  float temp;
  creal_T1 outf1;
  for (jj = 0; jj < box_h * box_w; jj++)
  {
    temp = 1 / (p2f[jj].re * p2f[jj].re + p2f[jj].im * p2f[jj].im);
    outf1.re = temp *(p1f[jj].re * p2f[jj].re + p1f[jj].im * p2f[jj].im);
    outf1.im = temp *(p1f[jj].im * p2f[jj].re - p1f[jj].re * p2f[jj].im);
    outf[jj] = outf1;
  }
}

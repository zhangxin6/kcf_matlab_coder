#include "p_def.h"
void mul_f(creal_T1 p1f[],creal_T1  p2f[], creal_T1 outf[]);
void conj_f(creal_T1 inputf[],creal_T1 outf[]);
extern creal_T1 gf[box_p];

void linear_correlation(creal_T1 xf[box_p], creal_T1 yf[box_p], creal_T1 kf[box_p])
{
  static creal_T1 xyf[box_p];
  int k;
  conj_f(yf,gf);
  mul_f(xf,gf,xyf);
  for (k = 0; k < box_p; k++) {
    kf[k].re = xyf[k].re/box_p;
    kf[k].im = xyf[k].im/box_p; 
  }
}

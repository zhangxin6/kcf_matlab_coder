#include "p_def.h"
#include <math.h>

extern creal_T1 gf[box_p];

void fft2_d(float vector[],creal_T1 vector1[],int M,int N);
void ifft2(creal_T1 vector[],creal_T1 vector1[],int M,int N);
void ifft(creal_T1 vector[],int N);
void fft(creal_T1 vector[],int N);
void change(int N, creal_T1 vector[]);
void add(creal_T1 a, creal_T1 b, creal_T1* c);
void mul(creal_T1 a, creal_T1 b, creal_T1* c);
void sub(creal_T1 a, creal_T1 b, creal_T1 *c);
void divi(creal_T1 a, creal_T1 b, creal_T1* c);
void conj_f(creal_T1 inputf[],creal_T1 outf[]);
void mul_f(creal_T1 p1f[],creal_T1  p2f[], creal_T1 outf[]);
void polynomial_correlation(creal_T1 xf[box_p], creal_T1 yf[box_p], creal_T1 kf[box_p])
{
  static creal_T1 xyf[box_p];
  static creal_T1 xy[box_p];
  static float temp[box_p];
  int k;
  conj_f(yf,gf);
  mul_f(xf,gf,xyf);
  ifft2(xyf,xy,box_w,box_h);
  for (k = 0; k < box_p; k++) {
    temp[k] = (int) (0.5 + pow((xy[k].re / box_p + AA),BB) );
  }
  fft2_d(temp,kf,box_w,box_h);
}

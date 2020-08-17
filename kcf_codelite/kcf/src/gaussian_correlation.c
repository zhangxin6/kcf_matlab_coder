#include "p_def.h"
extern creal_T1 gf[box_p];

void conj_f(creal_T1 inputf[],creal_T1 outf[]);
void mul_f(creal_T1 p1f[],creal_T1  p2f[], creal_T1 outf[]);
void b_exp(float x[box_p]);
void fft2_d(float vector[],creal_T1 vector1[],int M,int N);
void ifft(creal_T1 vector[],int N);
void ifft2(creal_T1 vector[],creal_T1 vector1[],int M,int N);
void change(int N, creal_T1 vector[]);
void add(creal_T1 a, creal_T1 b, creal_T1* c);
void mul(creal_T1 a, creal_T1 b, creal_T1* c);
void sub(creal_T1 a, creal_T1 b, creal_T1 *c);
void divi(creal_T1 a, creal_T1 b, creal_T1* c);
void fft(creal_T1 x[],int N);

void gaussian_correlation(creal_T1 xf[box_p], creal_T1 yf[box_p], creal_T1 kf[box_p])
{
  float xx,yy;
  int k;
  static creal_T1 xyf[box_p];
  static creal_T1 xy[box_p];
  static float y[box_p];
  xx = 0;
  for (k = 0; k < box_p; k++) {
    xx += (xf[k].re * xf[k].re - -xf[k].im * xf[k].im)/box_p;
  }
  yy = 0;
  for (k = 0; k < box_p; k++) {
    yy += (yf[k].re * yf[k].re - -yf[k].im * yf[k].im)/box_p;
  }
  conj_f(yf,gf);
  mul_f(xf,gf,xyf);
  ifft2(xyf,xy,box_w,box_h);
  for (k = 0; k < box_p; k++) {
    y[k] = -(xx + yy - 2 * xy[k].re) / (box_p * (sigma * sigma));
  }
  b_exp(y);
  fft2_d(y,kf,box_w,box_h);
}

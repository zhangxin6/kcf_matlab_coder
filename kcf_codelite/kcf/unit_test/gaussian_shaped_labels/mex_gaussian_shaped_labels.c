#include "p_def.h"
#include <math.h>
#include "mex.h"

double b[box_p];

void power(const double a[box_p], double y[box_p])
{
  int k;
  for (k = 0; k < box_p; k++) {
    y[k] = a[k] * a[k];
  }
}
void ndgrid(const double varargin_1[box_h], const double varargin_2[box_w], double varargout_1[box_p], double varargout_2[box_p])
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
void b_exp(double x[box_p])
{
  int k;
  for (k = 0; k < box_p; k++) {
    x[k] = exp(x[k]);
  }
}
void circshift(double a[box_p],double b[box_p],int shf[2])
{
    int ii,jj,t1,t2;
    t1 = shf[1] % box_w;
    t2 = shf[0] % box_h;
    for(ii=0;ii<box_w;ii++) {
      for(jj=0;jj<box_h;jj++) {
        if( (ii < (box_w+t1)) && (jj < (box_h+t2)) ) {
          b[ii*box_h+jj] = a[(ii-t1)*box_h+(jj-t2)];
        }
        if( (ii >= (box_w+t1)) && (jj >= (box_h+t2)) ) {
            b[ii*box_h+jj] = a[(ii-t1-box_w)*box_h+jj-t2-box_h];
        }
        if( (ii < (box_w+t1)) && (jj >= (box_h+t2)) )  {
           b[ii*box_h+jj] = a[(ii-t1)*box_h+jj-t2-box_h];
        }
        if( (ii >= (box_w+t1)) && (jj < (box_h+t2)) ) {
            b[ii*box_h+jj] = a[(ii-t1-box_w)*box_h+(jj-t2)];
        }
      }
    }
    for(ii=0;ii<box_w;ii++) {
      for(jj=0;jj<box_h;jj++) {
        a[ii*box_h+jj] = b[ii*box_h+jj];
    }
  }
}

static void gaussian_shaped_labels(double labels[box_p])
{
  int i0;
  int shf[2];
  double dv9[box_h];
  double dv10[box_w];
  static double rs[box_p];
  static double cs[box_p];
  double output_sigma;
  output_sigma = sqrt(gt2*gt3) * output_sigma_factor / cell_size;
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

void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[]){
    double *input1;
    double *out;
    int RowA,ColA,i;
    if(nlhs != 1){
       mexErrMsgTxt("One output required.");
    }
    else if(nrhs != 1){
        mexErrMsgTxt("One input required.");
    }
    RowA = mxGetM(prhs[0]);
    ColA = mxGetN(prhs[0]);
    plhs[0] = mxCreateDoubleMatrix(RowA,ColA,mxREAL);

    input1 = mxGetPr(prhs[0]);
    out = mxGetPr(plhs[0]);
    gaussian_shaped_labels(input1);
    for(i=0;i<RowA*ColA;i++)
    {
      out[i] = input1[i];
    }
}

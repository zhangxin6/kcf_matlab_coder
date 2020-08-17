#include "p_def.h"
#include "mex.h"
creal_T1 gf[box_p];

void conj_f(creal_T1 inputf[],creal_T1 outf[])
{
  int jj;
  for (jj = 0; jj < box_p; jj++) {
    outf[jj].re = inputf[jj].re;
    outf[jj].im = -inputf[jj].im;
  }
}
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
void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[]){
    creal_T1 *input1;
    creal_T1 *input2;
    creal_T1 *out;
    double* input1_re;double* input1_im;
    double* input2_re;double* input2_im;
    double* out_re;   double* out_im;
    int RowA,ColA,RowB,ColB,i;

    if(nlhs != 1){
       mexErrMsgTxt("One output required.");
    }
    else if(nrhs != 2){
        mexErrMsgTxt("Two input required.");
    }
    RowA = mxGetM(prhs[0]);
    ColA = mxGetN(prhs[0]);
    RowB = mxGetM(prhs[1]);
    ColB=  mxGetN(prhs[1]);
    if(RowA != RowB || ColA != ColB){
        mexErrMsgTxt("Rows and Cols must be same.");
    }
    input1_re = mxGetPr(prhs[0]);
    input1_im = mxGetPi(prhs[0]);
    input1 = malloc(sizeof(creal_T1)*RowA*ColA);
    for(i=0;i<RowA*ColA;i++)
    {
      input1[i].re = input1_re[i];
      input1[i].im = input1_im[i];
    }
    input2_re = mxGetPr(prhs[1]);
    input2_im = mxGetPi(prhs[1]);
    input2 = malloc(sizeof(creal_T1)*RowB*ColB);
    for(i=0;i<RowB*ColB;i++)
    {
      input2[i].re = input2_re[i];
      input2[i].im = input2_im[i];
    }
    out = malloc(sizeof(creal_T1)*RowA*ColA);
    plhs[0] = mxCreateDoubleMatrix(RowA,ColA,mxCOMPLEX);
    out_re = mxGetPr(plhs[0]);
    out_im = mxGetPi(plhs[0]);

    linear_correlation(input1, input2, out);

    for(i=0;i<RowA*ColA;i++)
    {
      out_re[i] = out[i].re;
      out_im[i] = out[i].im;
    }
    free(input1);
    free(input2);
    free(out);
}

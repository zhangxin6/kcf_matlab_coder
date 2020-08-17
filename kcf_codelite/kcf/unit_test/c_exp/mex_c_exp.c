#include "mex.h"
#include "p_def.h"
#include <math.h>

void c_exp(creal_T1 x[box_p])
{
  int k;
  double x_re;
  double r;
  for (k = 0; k < box_p; k++) {
    r = exp(x[k].re / 2.0);
    x_re = r * (r * cos(x[k].im));
    r *= r * sin(x[k].im);
    x[k].re = x_re;
    x[k].im = r;
  }
}
void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[]){
    creal_T1 *input1;
    double* input1_re;double* input1_im;
    double* out_re;   double* out_im;
    int RowA,ColA,i;
    if(nlhs != 1){
       mexErrMsgTxt("One output required.");
    }
    else if(nrhs !=1){
        mexErrMsgTxt("One input required.");
    }
    RowA = mxGetM(prhs[0]);
    ColA = mxGetN(prhs[0]);
    input1_re = mxGetPr(prhs[0]);
    input1_im = mxGetPi(prhs[0]);
    input1 = malloc(sizeof(creal_T1)*RowA*ColA);
    for(i=0;i<RowA*ColA;i++)
    {
      input1[i].re = input1_re[i];
      input1[i].im = input1_im[i];
    }
    plhs[0] = mxCreateDoubleMatrix(RowA,ColA,mxCOMPLEX);
    out_re = mxGetPr(plhs[0]);
    out_im = mxGetPi(plhs[0]);
    c_exp(input1);
    for(i=0;i<RowA*ColA;i++)
    {
      out_re[i] = input1[i].re;
      out_im[i] = input1[i].im;
    }
    free(input1);
}

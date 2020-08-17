#include "mex.h"
#include "p_def.h"


void conj_f(creal_T1 inputf[],creal_T1 outf[])
{
  int jj;
  for (jj = 0; jj < box_p; jj++) {
    outf[jj].re = inputf[jj].re;
    outf[jj].im = -inputf[jj].im;
  }
}
void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[]){
    creal_T1 *input1;
    double* input1_re;double* input1_im;
    double* out_re;   double* out_im;  creal_T1 *out;
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
    out = malloc(sizeof(creal_T1)*RowA*ColA);
    plhs[0] = mxCreateDoubleMatrix(RowA,ColA,mxCOMPLEX);
    out_re = mxGetPr(plhs[0]);
    out_im = mxGetPi(plhs[0]);

    conj_f(input1,out);
    for(i=0;i<RowA*ColA;i++)
    {
      out_re[i] = out[i].re;
      out_im[i] = out[i].im;
    }
    free(input1);
    free(out);
}

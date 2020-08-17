#include "mex.h"
#include "p_def.h"

void power(const double a[box_p], double y[box_p])
{
  int k;
  for (k = 0; k < box_p; k++) {
    y[k] = a[k] * a[k];
  }
}

void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[]){
    double *input1;
    double *out;
    int RowA,ColA;
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
    power(input1,out);
}

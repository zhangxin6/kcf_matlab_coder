#include "mex.h"
#include "p_def.h"
#include <math.h>

void b_exp(double x[box_p])
{
  int k;
  for (k = 0; k < box_p; k++) {
    x[k] = exp(x[k]);
  }
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
    b_exp(input1);
    for(i=0;i<RowA*ColA;i++)
    {
      out[i] = input1[i];
    }
}

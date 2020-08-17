#include "mex.h"
#include "p_def.h"

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

void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[]){
    double *input1;
    double *output1;
    double *input2;
    double *output2;
    int RowA,ColA;
    if(nlhs != 2){
       mexErrMsgTxt("Two output required.");
    }
    else if(nrhs != 2){
        mexErrMsgTxt("Two input required.");
    }
    RowA = mxGetN(prhs[0]);
    ColA = mxGetN(prhs[1]);
    plhs[0] = mxCreateDoubleMatrix(RowA,ColA,mxREAL);
    plhs[1] = mxCreateDoubleMatrix(RowA,ColA,mxREAL);

    input1 = mxGetPr(prhs[0]);
    output1 = mxGetPr(plhs[0]);
    input2 = mxGetPr(prhs[1]);
    output2 = mxGetPr(plhs[1]);
    ndgrid(input1,input2,output1,output2);
}

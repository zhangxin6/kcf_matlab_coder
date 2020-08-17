#include "mex.h"
#include "p_def.h"

double a[box_p];

static void get_features(const double im[box_p], const double cos_window[box_p], double x[box_p])
{
  double y;
  int k;
  int b_k;
  y = 0;
  for (k = 0; k < box_p; k++) {
    y += im[k];
  }
  y /= box_p;
  for (k = 0; k < box_p; k++) {
    a[k] = (im[k] - y) / 255.0 ;
  }
  for (k = 0; k < box_w; k++) {
    for (b_k = 0; b_k < box_h; b_k++) {
      x[b_k + box_h * k] = a[b_k + box_h * k] * cos_window[b_k + box_h * k];
    }
  }
}
void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[]){
    double *input1;
    double *output1;
    double *input2;
    int RowA,ColA;
    if(nlhs != 1){
       mexErrMsgTxt("One output required.");
    }
    else if(nrhs != 2){
        mexErrMsgTxt("Two input required.");
    }
    RowA = mxGetM(prhs[0]);
    ColA = mxGetN(prhs[0]);
    plhs[0] = mxCreateDoubleMatrix(RowA,ColA,mxREAL);

    input1 = mxGetPr(prhs[0]);
    output1 = mxGetPr(plhs[0]);
    input2 = mxGetPr(prhs[1]);

    get_features(input1,input2,output1);
}

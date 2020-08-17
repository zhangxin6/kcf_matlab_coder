#include "mex.h"
#include "p_def.h"
#include <math.h>

static void get_subwindow(const double im[im_p], const int pos[2], double out[box_p])
{
  int i;
  int xs[box_w];
  int ys[box_h];
  int i1;
  for (i = 0; i < box_w; i++) {
    xs[i] = floor(pos[1]) + 1 + i - floor(box_w/2);
  }
  for (i = 0; i < box_h; i++) {
    ys[i] = floor(pos[0]) + 1 + i - floor(box_h/2);
  }
  for (i = 0; i < box_w; i++) {
    if (xs[i] < 1) {
      xs[i] = 1;
    }
    if (xs[i] > im_w) {
      xs[i] = im_w;
    }
  }
  for (i = 0; i < box_h; i++) {
    if (ys[i] < 1) {
      ys[i] = 1;
    }
    if (ys[i] > im_h) {
      ys[i] = im_h;
    }
  }
  for (i = 0; i < box_w; i++) {
    for (i1 = 0; i1 < box_h; i1++) {
      out[i1 + box_h * i] = im[(ys[i1] - 1) + im_h * (xs[i] - 1)];
    }
  }
}
void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[]){
    double *input1;
    int *input2;
    double * temp;
    double *output1;
    int RowA,ColA,i;
    if(nlhs != 1){
       mexErrMsgTxt("One output required.");
    }
    else if(nrhs != 2){
        mexErrMsgTxt("Two input required.");
    }
    input1 = mxGetPr(prhs[0]);
    temp  = mxGetPr(prhs[1]);
    input2 = malloc(sizeof(int)*2);
    input2[0]  = (int)(temp[0]);
    input2[1]  = (int)(temp[1]);
    plhs[0] = mxCreateDoubleMatrix(box_h,box_w,mxREAL);
    output1 = mxGetPr(plhs[0]);
    get_subwindow(input1,input2,output1);
}

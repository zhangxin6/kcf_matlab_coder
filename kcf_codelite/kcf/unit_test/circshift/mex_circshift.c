#include "mex.h"
#include "p_def.h"

void circshift(double a[box_p],double b[box_p],int shf[2])
{
    int ii,jj,t1,t2;
    t1 = shf[1] % box_w;
    t2 = shf[0] % box_h;
    t1 = shf[1];
    t2 = shf[0];

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

void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[]){
    double *input1;
    double *input2;
    double * temp;
    int input3[2];
    double *output1;
    int RowA,ColA,i;
    if(nlhs != 1){
       mexErrMsgTxt("One output required.");
    }
    else if(nrhs != 3){
        mexErrMsgTxt("Three input required.");
    }
    input1 = mxGetPr(prhs[0]);
    input2 = mxGetPr(prhs[1]);
    temp   = mxGetPr(prhs[2]);
    input3[0] = (int)(temp[0]);
    input3[1] = (int)(temp[1]);

    RowA = mxGetM(prhs[0]);
    ColA = mxGetN(prhs[0]);
    plhs[0] = mxCreateDoubleMatrix(RowA,ColA,mxREAL);

    output1 = mxGetPr(plhs[0]);
    circshift(input1,input2,input3);
    for(i=0;i<RowA*ColA;i++)
    {
      output1[i] = input1[i];
    }
}

#include "mex.h"
#include <stdio.h>
#include <stdlib.h>

void data_input(double buf[],const char name[])
{
  FILE *fp;
  if((fp = fopen(name,"r")) == NULL)
  {
     exit (1) ;
  };
  unsigned int i=0;
  while(fscanf(fp,"%lf,",&buf[i]) != EOF)
  {
      i++;
  }
}

void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[]){
    double *input1;
    char *input2; char* buf;
    double* out;
    double * temp;
    mwSize buflen;
    int status;
    int RowA,ColA,i;
    if(nlhs != 1){
       mexErrMsgTxt("One output required.");
    }
    else if(nrhs != 2){
        mexErrMsgTxt("Two input required.");
    }
    RowA = mxGetM(prhs[0]);
    ColA = mxGetN(prhs[0]);
    input1 = mxGetPr(prhs[0]);
    input2 = mxArrayToString(prhs[1]);

    plhs[0] = mxCreateDoubleMatrix(RowA,ColA,mxREAL);
    out = mxGetPr(plhs[0]);
    data_input(input1, input2);
    for(i=0;i<RowA*ColA;i++)
    {
      out[i] = input1[i];
    }
}

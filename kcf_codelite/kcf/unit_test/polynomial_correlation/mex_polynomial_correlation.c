#include "p_def.h"
#include "mex.h"
#include <math.h>
#include "my_fft.h"
creal_T1 gf[box_p];

void fft2_d(double vector[],creal_T1 vector1[],int M,int N)
{
   creal_T1 hang[N];
   creal_T1 lie[M];
   int i,j;

   for(j=1;j<=N;j++){
     for(i=1;i<=M;i++){
       lie[i-1].re = vector[ ((j-1)+ (i-1)*N) ];
       lie[i-1].im = 0;
     }
     fft(lie,M);
     for(i=1;i<=M;i++){
       vector1[ ((j-1)+ (i-1)*N) ].re = lie[i-1].re;
       vector1[ ((j-1)+ (i-1)*N) ].im = lie[i-1].im;
     }
   }
  for(i=1;i<=M;i++){
    for(j=1;j<=N;j++){
      hang[j-1].re =vector1[ (j-1)+ (i-1)*N ].re;
      hang[j-1].im =vector1[ (j-1)+ (i-1)*N ].im;
    }
    fft(hang,N);
    for(j=1;j<=N;j++){
      vector1[ (j-1)+ (i-1)*N ].re = hang[j-1].re;
      vector1[ (j-1)+ (i-1)*N ].im  = hang[j-1].im;
    }
  }
}
void ifft2(creal_T1 vector[],creal_T1 vector1[],int M,int N)
{
   creal_T1 hang[N];
   creal_T1 lie[M];
   int i,j;
   for(j=1;j<=N;j++){
     for(i=1;i<=M;i++){
       lie[i-1].re = vector[ ((j-1)+ (i-1)*N) ].re;
       lie[i-1].im = vector[ ((j-1)+ (i-1)*N) ].im;
     }
     ifft(lie,M);
     for(i=1;i<=M;i++){
       vector[ ((j-1)+ (i-1)*N) ].re = lie[i-1].re;
       vector[ ((j-1)+ (i-1)*N) ].im = lie[i-1].im;
     }
   }
  for(i=1;i<=M;i++){
    for(j=1;j<=N;j++){
      hang[j-1].re =vector[ (j-1)+ (i-1)*N ].re;
      hang[j-1].im =vector[ (j-1)+ (i-1)*N ].im;
    }
    ifft(hang,N);
    for(j=1;j<=N;j++){
      vector[ (j-1)+ (i-1)*N ].re = hang[j-1].re;
      vector[ (j-1)+ (i-1)*N ].im  = hang[j-1].im;
    }
  }
  for(i=1;i<=M;i++){
    for(j=1;j<=N;j++){
      vector1[ (j-1)+ (i-1)*N ].re = vector[ (j-1)+ (i-1)*N ].re;
      vector1[ (j-1)+ (i-1)*N ].im  = vector[ (j-1)+ (i-1)*N ].im;
    }
  }
}
void ifft(creal_T1 vector[],int N)
{
    int i;
    for(i=0;i<N;i++)
    {
      vector[i].im = -vector[i].im;
    }
    fft(vector,N);
    for(i=0;i<N;i++)
    {
      vector[i].re = vector[i].re / N;
      vector[i].im = -vector[i].im / N;
    }
}
void fft(creal_T1 vector[],int N)
{
  int dig,k,n,m,i,j1,dist,idx,idx1,r;
  creal_T1 coef,tmp,mul_res;

  change(N,vector);
  dig = 0;
  k = N;
  while(k > 1){
      dig = dig + 1;
      k = k / 2;
  }
  n = N / 2;
  for(m=1;m<=dig;m++)
  {
      dist = pow(2, (m - 1) );
      idx = 1;
      for(i = 1;i<=n;i++){
        idx1 = idx;
        for(j1 = 1; j1 <= (N / (2 * n)); j1++){
            r = (idx - 1) * pow(2, (dig - m));
            coef.re = cos(2 * M_PI * r / N);
            coef.im = -sin(2 * M_PI * r / N);

            tmp.re = vector[idx-1].re;
            tmp.im  = vector[idx-1].im;
            mul(vector[idx + dist-1], coef, &mul_res);
            add(tmp, mul_res, &vector[idx-1]);
            sub(tmp, mul_res, &vector[idx + dist-1]);
            idx = idx + 1;
        }
        idx = idx1 + 2 * dist;
    }
    n = n / 2;
  }
}
void change(int N, creal_T1 vector[]){
  int j1,i;
  double k;
  creal_T1 tmp;
  j1 = 0;
  for(i=1;i<=N;i++){
    if(i < j1+1){
      tmp.re = vector[j1].re;
      tmp.im = vector[j1].im;
      vector[j1].re = vector[i-1].re;
      vector[j1].im = vector[i-1].im;
      vector[i-1].re = tmp.re;
      vector[i-1].im = tmp.im;
    }
    k = N / 2;
    while(k<=j1){
      j1 = j1- k;
      k =k /2;
    }
    j1 = j1+k;
  }
}
void add(creal_T1 a, creal_T1 b, creal_T1* c){
  c->re = a.re + b.re;
  c->im = a.im + b.im;
}
void mul(creal_T1 a, creal_T1 b, creal_T1* c){
  c->re = a.re * b.re - a.im * b.im;
  c->im = a.re * b.im + a.im * b.re;
}
void sub(creal_T1 a, creal_T1 b, creal_T1 *c){
  c->re =a.re - b.re;
  c->im = a.im - b.im;
}
void divi(creal_T1 a, creal_T1 b, creal_T1* c){
  c->re = (a.re*b.re + a.im*b.im)/(b.re*b.re + b.im*b.im);
  c->im = (a.im*b.re - a.re*b.im)/(b.re*b.re + b.im*b.im);
}
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
void polynomial_correlation(creal_T1 xf[box_p], creal_T1 yf[box_p], creal_T1 kf[box_p])
{
  static creal_T1 xyf[box_p];
  static creal_T1 xy[box_p];
  static double temp[box_p];
  int k;
  conj_f(yf,gf);
  mul_f(xf,gf,xyf);
  ifft2(xyf,xy,box_w,box_h);
  for (k = 0; k < box_p; k++) {
    temp[k] = pow((xy[k].re / box_p + AA),BB);
  }
  fft2_d(temp,kf,box_w,box_h);
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

    polynomial_correlation(input1, input2, out);

    for(i=0;i<RowA*ColA;i++)
    {
      out_re[i] = out[i].re;
      out_im[i] = out[i].im;
    }
    free(input1);
    free(input2);
    free(out);
}

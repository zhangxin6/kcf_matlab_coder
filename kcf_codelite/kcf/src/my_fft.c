#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "p_def.h"
#include "my_fft.h"

extern float cos_1024[32];
extern float sin_1024[32];

void fft2_d(float vector[],creal_T1 vector1[],int M,int N)
{
   static creal_T1 hang[32];
   static creal_T1 lie[32];
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
void fft2(creal_T1 vector[],creal_T1 vector1[],int M,int N)
{
   creal_T1 hang[32];
   creal_T1 lie[32];
   int i,j;

   for(j=1;j<=N;j++){
     for(i=1;i<=M;i++){
       lie[i-1].re = vector[ ((j-1)+ (i-1)*N) ].re;
       lie[i-1].im = vector[ ((j-1)+ (i-1)*N) ].im;
     }
     fft(lie,M);
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
    fft(hang,N);
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
void ifft2(creal_T1 vector[],creal_T1 vector1[],int M,int N)
{
   creal_T1 hang[32];
   creal_T1 lie[32];
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
      dist = (int)(dist + 0.5);
      idx = 1;
      for(i = 1;i<=n;i++){
        idx1 = idx;
        for(j1 = 1; j1 <= (N / (2 * n)); j1++){
            r = (idx - 1) * (int)(0.5 + pow(2, (dig - m)));

            coef.re = cos_1024[(r % N)*32/N];
            coef.im = -sin_1024[(r % N)*32/N];

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
  float k;
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

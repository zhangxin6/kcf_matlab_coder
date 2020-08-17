#include <math.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "p_def.h"
#include "exp.h"
#include "circshift.h"
#include "power.h"
#include "ndgrid.h"
#include "data_input.h"
#include "my_fft.h"
#include "div_f.h"
#include "conj_f.h"
#include "mul_f.h"

#include "gaussian_correlation.h"
#include "polynomial_correlation.h"
#include "linear_correlation.h"
#include "gaussian_shaped_labels.h"
#include "get_features.h"
#include "get_subwindow.h"

float cos_1024[32];
char cos_1024n[30] = "../txt/cos_32.dat";
float sin_1024[32];
char sin_1024n[30] = "../txt/sin_32.dat";
float hann_1024[1024];
char hann_name[30] = "../txt/hann_32.dat";
float hann[box_p];

float gauss[box_p];
creal_T1 yf[box_p];
unsigned short patch[box_p];
float feature[box_p];
float b[box_p];
creal_T1 xf[box_p];
creal_T1 kf[box_p];
creal_T1 kf_ld[box_p];
creal_T1 alphaf[box_p];
creal_T1 model_alphaf[box_p];
creal_T1 model_xf[box_p];
creal_T1 zf[box_p];
creal_T1 gf[box_p];
creal_T1 kzf[box_p];
creal_T1 rf[box_p];
creal_T1 mf[box_p];
float response[box_p];
unsigned short im[im_p];
float a[box_p];
float rs[box_p];
float cs[box_p];

int main(int argc, char **argv)
{
  int pos[2];
  float max_temp;
  int index_m,vert_delta,horiz_delta;
  int i,j,jj,frame,frame_begin,frame_num,seq;
  FILE* fp;
  char im_name[60]={0};
  char part1[20] = "../color/";
  char part2[10];
  char part3[10] = "/";
  char part4[10];
  char part5[10] = ".txt";
  char out_name[40]={0};
  char out_name1[20] = "../output/res_";
  char out_name2[10];
  char out_name3[10] = ".txt";
  char feature_type[15]={0};

  data_input(cos_1024,cos_1024n,32);
  data_input(sin_1024,sin_1024n,32);
  data_input(hann_1024,hann_name,1024);
  for(i=0;i<box_h;i++){
    for(j=0;j<box_w;j++){
        hann[i+j*box_h] = hann_1024[i*32/box_h+j*32/box_w*32];
    }
  }
  //frame_begin=atoi(argv[1]);
  //frame_num=atoi(argv[2]);
  //seq=atoi(argv[3]);
  //strcat(feature_type,argv[4]);
  frame_begin =1;
  frame_num =80;
  seq=4;
  strcat(feature_type, "linear");
  pos[0] = gt1 + floor(gt3/2);
  pos[1] = gt0 + floor(gt2/2);
  gaussian_shaped_labels(gauss);
  fft2_d(gauss,yf,box_w,box_h);

  for (frame = frame_begin; frame < (frame_begin+frame_num); frame++) {
    sprintf(part2,"%d",seq);
    sprintf(part4,"%08d",frame);
    strcat(im_name,part1);strcat(im_name,part2);strcat(im_name,part3);strcat(im_name,part4);strcat(im_name,part5);
    data_input_short(im,im_name,im_p);
    //data_input_short(im,im_name);
    memset(im_name,0,60);
    if (frame == frame_begin) {
      get_subwindow(im, pos, patch);
      get_features(patch, hann, feature);
      fft2_d(feature, xf,box_w,box_h);
      if(strcmp(feature_type,"linear")==0){
        linear_correlation(xf, xf, kf);
      }
      else if(strcmp(feature_type,"polynomial")==0){
        polynomial_correlation(xf, xf, kf);
      }
      else if(strcmp(feature_type,"gaussian")==0){
        gaussian_correlation(xf, xf, kf);
      }
      for (jj = 0; jj < box_p; jj++) {
        kf_ld[jj].re = kf[jj].re + lambda;
        kf_ld[jj].im = kf[jj].im;
      }
      div_f(yf, kf_ld, alphaf);
      for (jj = 0; jj < box_p; jj++) {
        model_alphaf[jj] = alphaf[jj];
        model_xf[jj] = xf[jj];
      }
    }
    if (frame > frame_begin) {
      get_subwindow(im, pos, patch);
      get_features(patch, hann, feature);
      fft2_d(feature, zf,box_w,box_h);
      if(strcmp(feature_type,"linear")==0){
        linear_correlation(zf, model_xf, kzf);
      }
      else if(strcmp(feature_type,"polynomial")==0){
        polynomial_correlation(zf, model_xf, kzf);
      }
      else if(strcmp(feature_type,"gaussian")==0){
        gaussian_correlation(zf, model_xf, kzf);
      }
      mul_f(model_alphaf, kzf, mf);
      ifft2(mf,rf,box_w,box_h);
      for (jj = 0; jj < box_p; jj++) {
        response[jj] = rf[jj].re;
      }
      max_temp = response[0];
      index_m = 0;
      for (jj = 0; jj < box_p; jj++) {
          if(response[jj] > max_temp){
            max_temp = response[jj];
            index_m = jj;
          }
      }
      vert_delta  = (index_m % box_h) + 1;
      horiz_delta = (index_m / box_h) + 1;
      if(vert_delta > box_h/2){
        vert_delta = vert_delta - box_h;
      }
      if(horiz_delta > box_w/2){
        horiz_delta = horiz_delta - box_w;
      }
      pos[0] = pos[0] + cell_size * (vert_delta-1);
      pos[1] = pos[1] + cell_size * (horiz_delta-1);
      get_subwindow(im, pos, patch);
      get_features(patch, hann, feature);
      fft2_d(feature,xf,box_w,box_h);
      if(strcmp(feature_type,"linear")==0){
        linear_correlation(xf, xf, kf);
      }
      else if(strcmp(feature_type,"polynomial")==0){
        polynomial_correlation(xf, xf, kf);
      }
      else if(strcmp(feature_type,"gaussian")==0){
        gaussian_correlation(xf, xf, kf);
      }
      else{
        printf("uknown feature type.\n");
      }
      for (jj = 0; jj < box_p; jj++) {
        kf_ld[jj].re = kf[jj].re + lambda;
        kf_ld[jj].im = kf[jj].im;
      }
      div_f(yf,kf_ld,alphaf);
      for (jj = 0; jj < box_p; jj++) {
          model_alphaf[jj].re = (1 - ifr) * model_alphaf[jj].re + ifr * alphaf[jj].re;
          model_alphaf[jj].im = (1 - ifr) * model_alphaf[jj].im + ifr * alphaf[jj].im;
      }
      for (jj = 0; jj < box_p; jj++) {
          model_xf[jj].re = (1 - ifr) * model_xf[jj].re + ifr * xf[jj].re;
          model_xf[jj].im = (1 - ifr) * model_xf[jj].im + ifr * xf[jj].im;
      }
    }
    if(frame == frame_begin){
        sprintf(out_name2,"%d",seq);
        strcat(out_name,out_name1);strcat(out_name,out_name2);strcat(out_name,out_name3);
        if((fp = fopen(out_name,"w")) == NULL){
             exit (1);
        }
    }
    fprintf(fp,"%d,%d,%d,%d\n",pos[0],pos[1],gt2,gt3);
    printf("runnning,please wait,frame=%d\n",frame);
  }
  fclose(fp);
  return 1;
}

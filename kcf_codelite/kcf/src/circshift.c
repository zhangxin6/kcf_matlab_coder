#include "p_def.h"

void circshift(float a[box_p],float b[box_p],int shf[2])
{
    int ii,jj,t1,t2;
    t1 = shf[1] % box_w;
    t2 = shf[0] % box_h;
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

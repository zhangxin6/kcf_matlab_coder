#include "p_def.h"

void conj_f(creal_T1 inputf[],creal_T1 outf[])
{
  int jj;
  for (jj = 0; jj < box_p; jj++) {
    outf[jj].re = inputf[jj].re;
    outf[jj].im = -inputf[jj].re;
  }
}

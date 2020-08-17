/*
 * File: fft1.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Aug-2020 11:43:07
 */

#ifndef FFT1_H
#define FFT1_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "omp.h"
#include "kcf_single_types.h"

/* Function Declarations */
extern void b_r2br_r2dit_trig(const creal_T x[256], const double costab[9],
  const double sintab[9], creal_T y[256]);
extern void c_r2br_r2dit_trig(const creal_T x[256], const double costab[9],
  const double sintab[9], creal_T y[256]);
extern void r2br_r2dit_trig(const double costab[9], const double sintab[9],
  creal_T y[256]);

#endif

/*
 * File trailer for fft1.h
 *
 * [EOF]
 */

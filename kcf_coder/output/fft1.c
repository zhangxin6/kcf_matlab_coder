/*
 * File: fft1.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Aug-2020 11:43:07
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "kcf_single.h"
#include "fft1.h"

/* Function Declarations */
static void r2br_r2dit_trig_impl(const creal_T x[256], int xoffInit, const
  double costab[9], const double sintab[9], creal_T y[16]);

/* Function Definitions */

/*
 * Arguments    : const creal_T x[256]
 *                int xoffInit
 *                const double costab[9]
 *                const double sintab[9]
 *                creal_T y[16]
 * Return Type  : void
 */
static void r2br_r2dit_trig_impl(const creal_T x[256], int xoffInit, const
  double costab[9], const double sintab[9], creal_T y[16])
{
  int ix;
  int ju;
  int iy;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  int iheight;
  int istart;
  int j;
  double twid_re;
  double twid_im;
  int ihi;
  ix = xoffInit;
  ju = 0;
  iy = 0;
  for (i = 0; i < 15; i++) {
    y[iy] = x[ix];
    iy = 16;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y[iy] = x[ix];
  for (i = 0; i <= 15; i += 2) {
    temp_re = y[i + 1].re;
    temp_im = y[i + 1].im;
    y[i + 1].re = y[i].re - y[i + 1].re;
    y[i + 1].im = y[i].im - y[i + 1].im;
    y[i].re += temp_re;
    y[i].im += temp_im;
  }

  iy = 2;
  ix = 4;
  ju = 4;
  iheight = 13;
  while (ju > 0) {
    for (i = 0; i < iheight; i += ix) {
      temp_re = y[i + iy].re;
      temp_im = y[i + iy].im;
      y[i + iy].re = y[i].re - temp_re;
      y[i + iy].im = y[i].im - temp_im;
      y[i].re += temp_re;
      y[i].im += temp_im;
    }

    istart = 1;
    for (j = ju; j < 8; j += ju) {
      twid_re = costab[j];
      twid_im = sintab[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        temp_re = twid_re * y[i + iy].re - twid_im * y[i + iy].im;
        temp_im = twid_re * y[i + iy].im + twid_im * y[i + iy].re;
        y[i + iy].re = y[i].re - temp_re;
        y[i + iy].im = y[i].im - temp_im;
        y[i].re += temp_re;
        y[i].im += temp_im;
        i += ix;
      }

      istart++;
    }

    ju /= 2;
    iy = ix;
    ix += ix;
    iheight -= iy;
  }
}

/*
 * Arguments    : const creal_T x[256]
 *                const double costab[9]
 *                const double sintab[9]
 *                creal_T y[256]
 * Return Type  : void
 */
void b_r2br_r2dit_trig(const creal_T x[256], const double costab[9], const
  double sintab[9], creal_T y[256])
{
  int k;
  creal_T rwork[16];
  int xoff;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(rwork,xoff)

  for (k = 1; k < 17; k++) {
    xoff = (k - 1) << 4;
    r2br_r2dit_trig_impl(x, xoff, costab, sintab, rwork);
    memcpy(&y[(k << 4) + -16], &rwork[0], sizeof(creal_T) << 4);
  }
}

/*
 * Arguments    : const creal_T x[256]
 *                const double costab[9]
 *                const double sintab[9]
 *                creal_T y[256]
 * Return Type  : void
 */
void c_r2br_r2dit_trig(const creal_T x[256], const double costab[9], const
  double sintab[9], creal_T y[256])
{
  int k;
  int i0;
  creal_T rwork[16];
  int xoff;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(rwork,xoff)

  for (k = 1; k < 17; k++) {
    xoff = (k - 1) << 4;
    r2br_r2dit_trig_impl(x, xoff, costab, sintab, rwork);
    memcpy(&y[(k << 4) + -16], &rwork[0], sizeof(creal_T) << 4);
  }

  for (i0 = 0; i0 < 256; i0++) {
    y[i0].re *= 0.0625;
    y[i0].im *= 0.0625;
  }
}

/*
 * Arguments    : const double costab[9]
 *                const double sintab[9]
 *                creal_T y[256]
 * Return Type  : void
 */
void r2br_r2dit_trig(const double costab[9], const double sintab[9], creal_T y
                     [256])
{
  int k;
  creal_T rwork[16];
  int ju;
  int iy;
  int i;
  boolean_T tst;
  double temp_im;
  int b_k;
  int iheight;
  int istart;
  double temp_re;
  int j;
  double twid_re;
  double twid_im;
  int ihi;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(rwork,ju,iy,i,tst,temp_im,b_k,iheight,istart,temp_re,j,twid_re,twid_im,ihi)

  for (k = 1; k < 17; k++) {
    ju = 0;
    iy = 0;
    for (i = 0; i < 15; i++) {
      rwork[iy].re = 0.0;
      rwork[iy].im = 0.0;
      iy = 16;
      tst = true;
      while (tst) {
        iy >>= 1;
        ju ^= iy;
        tst = ((ju & iy) == 0);
      }

      iy = ju;
    }

    rwork[iy].re = 0.0;
    rwork[iy].im = 0.0;
    for (i = 0; i <= 15; i += 2) {
      temp_im = rwork[i + 1].im;
      rwork[i + 1].re = 0.0;
      rwork[i + 1].im = rwork[i].im - rwork[i + 1].im;
      rwork[i].re = 0.0;
      rwork[i].im += temp_im;
    }

    iy = 2;
    ju = 4;
    b_k = 4;
    iheight = 13;
    while (b_k > 0) {
      for (i = 0; i < iheight; i += ju) {
        temp_re = rwork[i + iy].re;
        temp_im = rwork[i + iy].im;
        rwork[i + iy].re = rwork[i].re - temp_re;
        rwork[i + iy].im = rwork[i].im - temp_im;
        rwork[i].re += temp_re;
        rwork[i].im += temp_im;
      }

      istart = 1;
      for (j = b_k; j < 8; j += b_k) {
        twid_re = costab[j];
        twid_im = sintab[j];
        i = istart;
        ihi = istart + iheight;
        while (i < ihi) {
          temp_re = twid_re * rwork[i + iy].re - twid_im * rwork[i + iy].im;
          temp_im = twid_re * rwork[i + iy].im + twid_im * rwork[i + iy].re;
          rwork[i + iy].re = rwork[i].re - temp_re;
          rwork[i + iy].im = rwork[i].im - temp_im;
          rwork[i].re += temp_re;
          rwork[i].im += temp_im;
          i += ju;
        }

        istart++;
      }

      b_k /= 2;
      iy = ju;
      ju += ju;
      iheight -= iy;
    }

    memcpy(&y[(k << 4) + -16], &rwork[0], sizeof(creal_T) << 4);
  }
}

/*
 * File trailer for fft1.c
 *
 * [EOF]
 */

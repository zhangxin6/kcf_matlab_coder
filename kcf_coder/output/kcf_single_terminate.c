/*
 * File: kcf_single_terminate.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Aug-2020 11:43:07
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "kcf_single.h"
#include "kcf_single_terminate.h"
#include "kcf_single_data.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void kcf_single_terminate(void)
{
  omp_destroy_nest_lock(&emlrtNestLockGlobal);
}

/*
 * File trailer for kcf_single_terminate.c
 *
 * [EOF]
 */

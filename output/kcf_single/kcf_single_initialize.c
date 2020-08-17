/*
 * File: kcf_single_initialize.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Aug-2020 11:43:07
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "kcf_single.h"
#include "kcf_single_initialize.h"
#include "fileManager.h"
#include "kcf_single_data.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void kcf_single_initialize(void)
{
  rt_InitInfAndNaN(8U);
  omp_init_nest_lock(&emlrtNestLockGlobal);
  eml_openfiles_not_empty_init();
}

/*
 * File trailer for kcf_single_initialize.c
 *
 * [EOF]
 */

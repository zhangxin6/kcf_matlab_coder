/*
 * File: ifWhileCond.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Aug-2020 11:43:07
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "kcf_single.h"
#include "ifWhileCond.h"

/* Function Definitions */

/*
 * Arguments    : const boolean_T x_data[]
 *                const int x_size[1]
 * Return Type  : boolean_T
 */
boolean_T ifWhileCond(const boolean_T x_data[], const int x_size[1])
{
  boolean_T y;
  int k;
  boolean_T exitg1;
  y = !(x_size[0] == 0);
  if (y) {
    k = 1;
    exitg1 = false;
    while ((!exitg1) && (k <= x_size[0])) {
      if (!x_data[0]) {
        y = false;
        exitg1 = true;
      } else {
        k = 2;
      }
    }
  }

  return y;
}

/*
 * File trailer for ifWhileCond.c
 *
 * [EOF]
 */

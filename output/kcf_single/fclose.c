/*
 * File: fclose.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Aug-2020 11:43:07
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "kcf_single.h"
#include "fclose.h"
#include "kcf_single_data.h"

/* Function Declarations */
static double rt_roundd_snf(double u);

/* Function Definitions */

/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * Arguments    : double fileID
 * Return Type  : void
 */
void b_fclose(double fileID)
{
  signed char fileid;
  signed char b_fileid;
  FILE * a;
  int i;
  boolean_T condition;
  fileid = (signed char)rt_roundd_snf(fileID);
  if ((fileid < 0) || (fileID != fileid)) {
    fileid = -1;
  }

  b_fileid = fileid;
  if (fileid < 0) {
    b_fileid = -1;
  }

  if (b_fileid >= 3) {
    if (!eml_openfiles_not_empty) {
      a = NULL;
      for (i = 0; i < 20; i++) {
        eml_autoflush[i] = false;
        eml_openfiles[i] = a;
      }

      eml_openfiles_not_empty = true;
    }

    a = eml_openfiles[b_fileid - 3];
  } else if (b_fileid == 0) {
    a = stdin;
  } else if (b_fileid == 1) {
    a = stdout;
  } else if (b_fileid == 2) {
    a = stderr;
  } else {
    a = NULL;
  }

  if ((a != NULL) && (fileid >= 3)) {
    condition = true;
  } else {
    condition = false;
  }

  if (condition) {
    i = fclose(a);
    if (i == 0) {
      if (!eml_openfiles_not_empty) {
        a = NULL;
        for (i = 0; i < 20; i++) {
          eml_autoflush[i] = false;
          eml_openfiles[i] = a;
        }

        eml_openfiles_not_empty = true;
      }

      eml_openfiles[fileid - 3] = NULL;
      eml_autoflush[fileid - 3] = true;
    }
  }
}

/*
 * File trailer for fclose.c
 *
 * [EOF]
 */

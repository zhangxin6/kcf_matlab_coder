/*
 * File: fileManager.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Aug-2020 11:43:07
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "kcf_single.h"
#include "fileManager.h"
#include "kcf_single_data.h"

/* Function Declarations */
static signed char filedata(void);

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : signed char
 */
static signed char filedata(void)
{
  signed char f;
  FILE * a;
  int i;
  signed char k;
  boolean_T exitg1;
  if (!eml_openfiles_not_empty) {
    a = NULL;
    for (i = 0; i < 20; i++) {
      eml_autoflush[i] = false;
      eml_openfiles[i] = a;
    }

    eml_openfiles_not_empty = true;
  }

  f = 0;
  k = 1;
  exitg1 = false;
  while ((!exitg1) && (k < 21)) {
    if (eml_openfiles[k - 1] == NULL) {
      f = k;
      exitg1 = true;
    } else {
      k++;
    }
  }

  return f;
}

/*
 * Arguments    : const char * cfilename
 *                const char * cpermission
 * Return Type  : signed char
 */
signed char cfopen(const char * cfilename, const char * cpermission)
{
  signed char fileid;
  signed char j;
  FILE * filestar;
  FILE * a;
  int i;
  fileid = -1;
  j = filedata();
  if (!(j < 1)) {
    filestar = fopen(cfilename, cpermission);
    if (filestar != NULL) {
      if (!eml_openfiles_not_empty) {
        a = NULL;
        for (i = 0; i < 20; i++) {
          eml_autoflush[i] = false;
          eml_openfiles[i] = a;
        }

        eml_openfiles_not_empty = true;
      }

      eml_openfiles[j - 1] = filestar;
      eml_autoflush[j - 1] = true;
      i = j + 2;
      if (i > 127) {
        i = 127;
      }

      fileid = (signed char)i;
    }
  }

  return fileid;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void eml_openfiles_not_empty_init(void)
{
  eml_openfiles_not_empty = false;
}

/*
 * File trailer for fileManager.c
 *
 * [EOF]
 */

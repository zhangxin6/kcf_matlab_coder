/*
 * File: fileManager.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 17-Aug-2020 11:43:07
 */

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

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
extern signed char cfopen(const char * cfilename, const char * cpermission);
extern void eml_openfiles_not_empty_init(void);

#endif

/*
 * File trailer for fileManager.h
 *
 * [EOF]
 */

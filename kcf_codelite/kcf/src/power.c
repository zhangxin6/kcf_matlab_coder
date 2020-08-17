#include "p_def.h"

void power(const float a[box_p], float y[box_p])
{
  int k;
  for (k = 0; k < box_p; k++) {
    y[k] = a[k] * a[k];
  }
}

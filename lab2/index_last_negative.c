#include "index_last_negative.h"

int index_last_negative(int const a[], int size) {
  int ret = 0;

  for (int i = 0; i != size; ++i) {
    if (a[i] < 0) { ret = i; }
  }

  return ret;
}

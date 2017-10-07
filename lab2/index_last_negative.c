#include "index_last_negative.h"

int index_last_negative(int const a[], int size) {
  for (int i = size - 1; i != -1; --i) {
    if (a[i] < 0) { return i; }
  }
  
  return -1;
}

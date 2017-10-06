//0
#include "index_first_negative.h"

int index_first_negative(int const a[], int size) { 
  for (int i = 0; i != size; ++i) {
    if (a[i] < 0) { return i; }
  }
}

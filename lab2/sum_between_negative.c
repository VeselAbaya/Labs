#include "sum_between_negative.h"

int sum_between_negative(int const a[], int size) {
  int sum = 0;
  int even = 0;
  int odd = 0;
  
  int i = 0;
  while (a[i] % 2 == 1) { ++i; }
  even = i;

  for (i = 0; i != size; ++i) {
    if (a[i] % 2 == 1) { odd = i; } 
  }

  for (i = even; i != odd + 1; ++i) {
    sum += abs(a[i]);
  }

  return sum;
}

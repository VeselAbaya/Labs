#include "sum_before_and_after_negative.h"

int sum_before_and_after_negative(int const a[], int size) {
  int flag_even_in = 0;
  int flag_odd_in = 0;
 
  int sum = 0;
  int even = 0;
  int odd = 0;

  for (int i = 0; i != size; ++i) {
    if (a[i] % 2 == 0) { 
      even = i;
      flag_even_in = 1;
      break;
    }
  }

  for (int i = 0; i != size; ++i) {
    if (a[i] % 2 == 1) { 
      odd = i;
      flag_odd_in = 1; 
    }
  }

  if (flag_even_in) {
    for (int i = 0; i != even + 1; ++i) { sum += abs(a[i]); }
  }
  if (flag_odd_in) {
    for (int i = odd; i != size; ++i) { sum += abs(a[i]); }
  }

  return sum;
}

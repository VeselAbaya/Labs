#include "sum_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int sum_before_and_after_negative(int const a[], int size) {
  int flag_even_in = 0;
  int flag_odd_in = 0;

  int sum = 0;
  
  for (int i = 0; i != index_first_negative(a, size) + 1; ++i) {
    sum += abs(a[i]);
  }
  for (int i = index_last_negative(a, size); i != size; ++i) {
    sum += abs(a[i]);
  }

  return sum;
}

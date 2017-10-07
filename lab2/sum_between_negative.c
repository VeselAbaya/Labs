#include "sum_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int sum_between_negative(int const a[], int size) {
  int sum = 0;
  
  for (int i = index_first_negative(a, size); i != index_last_negative(a, size); ++i) {
    sum += abs(a[i]);
  }

  return sum;
}

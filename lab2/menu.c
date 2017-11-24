#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"

int main() {
  int a[100];
  int command;
  scanf("%d ", &command);
  
  int size;
  for (size = 0; getchar() != '\n' && size != 100; ++size) {
    scanf("%d", &a[size]);
  }

  if (size == 0) { 
  	printf("Данные некорректны\n");
  	return 0;
  }

  switch(command) {
    case(0):
      printf("%d\n", index_first_negative(a, size));
      break;
    case(1):
      printf("%d\n", index_last_negative(a, size));
      break;
    case(2):
      printf("%d\n", sum_between_negative(a, size));
      break;
    case(3):
      printf("%d\n", sum_before_and_after_negative(a, size));
      break;
    default:
      printf("Данные некорректны\n");
      break;
  }

  return 0;
}

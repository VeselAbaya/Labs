#include "get_name.h"
#include "print_str.h"
#include <string.h>

int main() {
  char* name = get_name();
  char hello[107] = "Hello, ";
  strncat(hello, name, 100);
  print_str(hello);
  return 0;
}

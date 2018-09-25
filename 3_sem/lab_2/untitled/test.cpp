#include "h_list.h"
#include <iostream>
using namespace h_list;

int main() {
  lisp s1;
  read_lisp(s1);
  write_lisp(s1);
  std::cout << std::endl;
  lisp s2 = flatten(s1);
  write_lisp(s2);

  return 0;
}

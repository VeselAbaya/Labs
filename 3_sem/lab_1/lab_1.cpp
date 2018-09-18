#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

#define FIRST_CALL true

using namespace std;

bool check_expr_impl(istringstream& istr, bool call = false) {
  bool res;
  char c;
  istr >> c;

  if (isalpha(c))
    return true;
  else if (c == '(')
    res = check_expr_impl(istr);
  else
    return false;

  istr >> c;
  if (res && (c == '+' || c == '*' || c == '-'))
    res = check_expr_impl(istr);
  else
    return false;

  istr >> c;
  if (res && c == ')') {
    // scratch
    if (call == FIRST_CALL) {
      istr.peek();
      if (istr.eof())
        return true;
      else
        return false;
    }
    // scratch

    return true;
  } else
    return false;
}

bool check_expr(string const& expr) {
  if (expr.size() == 1 && isalpha(expr.at(0)))
    return true;
  if (expr.empty() || expr.at(0) != '(')
    return false;

  istringstream str{expr};
  return check_expr_impl(str, FIRST_CALL);
}


int main(int argc, char* argv[]) {
  ifstream i_file(argv[1]);
  ofstream o_file("lab1_output.txt");
  std::vector<string> exprs;

  // for setw() to find spacing
  size_t spacing = 0;
  string expr;
  while(getline(i_file, expr).good()) {
    spacing = max(spacing, expr.size());
    exprs.push_back(expr);
  }

  o_file << boolalpha;
  for (auto& expr: exprs)
    o_file << setw(spacing) << left << expr <<" : " << check_expr(expr) << endl;

  i_file.close();
  o_file.close();
  return 0;
}

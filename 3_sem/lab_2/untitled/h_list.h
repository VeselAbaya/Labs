#pragma once
#include <iostream>
#include <string>

namespace h_list {
  typedef std::string base;
  struct s_expr;
  struct two_ptr {
    s_expr * hd = nullptr;
    s_expr * tl = nullptr;
  };
  struct s_expr {
    bool tag; // true: atom, false: pair
    struct {
      base atom;
      two_ptr pair;
    } node; //end union node
  }; //end s_expr

  typedef s_expr* lisp;

  void print_s_expr(lisp s);
  lisp head(const lisp & s);
  lisp tail(const lisp & s);
  lisp cons(const lisp & h, const lisp & t);
  lisp make_atom(const base x);
  bool isAtom(const lisp & s);
  void destroy(const lisp & s);
  base getAtom(const lisp & s);
  lisp concat(const lisp & y, const lisp & z);
  lisp flatten(const lisp s);

  void read_lisp(lisp & y, std::istream& in);
  void read_s_expr(char prev, lisp & y, std::istream& in);
  void read_seq(lisp & y, std::istream& in);

  void write_lisp(const lisp x, std::ostream& out);
  void write_seq(const lisp x, std::ostream& out);

  lisp copy_lisp(const lisp x);
  // end of namespace h_list
}

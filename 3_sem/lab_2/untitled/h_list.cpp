#include <iostream>
#include <cstdlib>
#include <iostream>
#include <exception>
#include <QDebug>
#include "h_list.h"

using namespace std;
namespace h_list {
  lisp head(const lisp & s) {
    // PreCondition: not null (s)
    if (s != nullptr) {
      if (!isAtom(s))
        return s->node.pair.hd;
      else {
        cerr << "Error: Head(atom) \n";
        exit(1);
      }
    } else {
      cerr << "Error: Head(nil) \n";
      exit(1);
    }
  }

  bool isAtom(const lisp & s) {
    if (s == nullptr)
      return false;
    else
      return (s->tag);
  }

  lisp tail(const lisp & s) {
    // PreCondition: not null (s)
    if (s != nullptr) {
      if (!isAtom(s))
        return s->node.pair.tl;
      else {
        cerr << "Error: Tail(atom) \n";
        exit(1);
      }
    } else {
      cerr << "Error: Tail(nil) \n";
      exit(1);
    }
  }

  lisp cons(const lisp & h, const lisp & t) {
    // PreCondition: not isAtom (t)
    lisp p;
    if (isAtom(t)) {
      cerr << "Error: Cons(*, atom)\n";
      exit(1);
    } else {
      p = new s_expr;
      if (p == nullptr) {
        cerr << "Memory not enough\n";
        exit(1);
      } else {
        p->tag = false;
        p->node.pair.hd = h;
        p->node.pair.tl = t;
        return p;
      }
    }
  }

  lisp make_atom(const base x) {
    lisp s;
    s = new s_expr;
    s->tag = true;
    s->node.atom = x;
    return s;
  }

  void destroy(const lisp & s) {
    if (s != nullptr) {
      if (!isAtom(s)) {
        destroy(head(s));
        destroy(tail(s));
      }
      delete s;
    }
  }

  base getAtom(const lisp & s) {
    if (!isAtom(s)) {
      cerr << "Error: getAtom(s) for !isAtom(s) \n";
      exit(1);
    } else
      return (s->node.atom);
  }

  lisp concat(const lisp & y, const lisp & z) {
    if (!y) return copy_lisp(z);
    else return cons(copy_lisp(head(y)), concat(tail(y), z));
  } // end concat

  lisp flatten(const lisp s) {
    if (!s) return nullptr;
    else if (isAtom(s))
      return cons(make_atom(getAtom(s)), nullptr);
    else {
      if (isAtom(head(s)))
        return cons(make_atom(getAtom(head(s))), flatten(tail(s)));
      else
        return concat(flatten(head(s)), flatten(tail(s)));
    }
  } //end flatten

  void read_lisp(lisp & y, std::istream& in) {
    char x;
    do {
      in >> x;
    } while (x == ' ');
    read_s_expr(x, y, in);
  } //end read_lisp

  void read_s_expr(char prev, lisp & y, std::istream& in) {
    if (prev == ')') {
      cerr << " ! List.Error 1 " << endl;
      exit(1);
    } else if (prev != '(') {
      base value = std::string{prev};
      while (in.peek() != ' ' && in.peek() != '(' && in.peek() != ')')
          value += in.get();
      y = make_atom(value);
    } else
      read_seq(y, in);
  } //end read_s_expr

  void read_seq(lisp & y, std::istream& in) {
    char x;
    lisp p1, p2;

    if (!(in >> x)) {
      cerr << " ! List.Error 2 " << endl;
      exit(1);
    } else {
      while (x == ' ')
        in >> x;
      if (x == ')')
        y = nullptr;
      else {
        read_s_expr(x, p1, in);
        read_seq(p2, in);
        y = cons(p1, p2);
      }
    }
  } //end read_seq

  void write_lisp(const lisp x, std::ostream& out) {
    if (!x)
      out << " ()";
    else if (isAtom(x))
      out << ' ' << x->node.atom;
    else {
      out << " (";
      write_seq(x, out);
      out << " )";
    }
  } // end write_lisp

  void write_seq(const lisp x, std::ostream& out) {
    if (x) {
      write_lisp(head(x), out);
      write_seq(tail(x), out);
    }
  }

  lisp copy_lisp(const lisp x) {
    if (!x)
      return nullptr;
    else if (isAtom(x))
      return make_atom(x->node.atom);
    else
      return cons(copy_lisp(head(x)), copy_lisp(tail(x)));
  } //end copy-lisp
} // end of namespace h_list

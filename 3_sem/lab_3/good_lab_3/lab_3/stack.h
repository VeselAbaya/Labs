#ifndef STACK_H
#define STACK_H

#include <vector>
#include <iostream>
#include <string>

template <typename T>
class Stack {
public:
    void push(T i) {
    _data.push_back(i);
  }

    void pop() {
    if (!_data.empty())
        _data.pop_back();
  }

  T top() {
    return _data.back();
  }

  bool empty() {
    return _data.empty();
  }

private:
    std::vector<T> _data;
};


#endif // STACK_H

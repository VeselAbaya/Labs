#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <exception>

template <typename T>
class Tree {
    class Node {
    public:
        T value;
        Node* left = nullptr;
        Node* right = nullptr;

        ~Node() {
            if (left)
                delete left;
            if (right)
                delete right;
        }

        void output(std::ostream& out) {
            if (this) {
                out << value;
                if (left) {
                    out << '(';
                    left->output(out);
                    out << ')';
                }

                if (right) {
                    out << '(';
                    right->output(out);
                    out << ')';
                }
            }
        }

        void read(std::istream& in) {
            char c = 0;
            if (this) {
                in >> value;

                /* left node */
                c = in.get();
                if (c == '(') {
                    if (in.peek() != ')') {
                        left = new Node();
                        left->read(in);
                    } else {
                        c = in.get();
                        left = nullptr;
                    }
                } else if (c == ')')
                    return;
                else
                    throw std::logic_error("Incorrect input format");


                /* right node */
                c = in.get();
                if (c == '(') {
                    if (in.peek() != ')') {
                        right = new Node();
                        right->read(in);
                    } else {
                        c = in.get();
                        right = nullptr;
                    }
                } else if (c == ')')
                    return;
                else
                    throw std::logic_error("Incorrect input format");

                /* this node */
                c = in.get();
                if (c != ')')
                    throw std::logic_error("Incorrect input format");
            } else
                throw std::logic_error("Incorrect input format");
        }

        void print_leaves(std::ostream& out) {
            if (this) {
                if (!left && !right)
                    out << value << ' ';
                if (left)
                    left->print_leaves(out);
                if (right)
                    right->print_leaves(out);
            }
        }
    };

public:
    Tree(): _root(new Node) {}

    ~Tree() {
        _root->~Node();
    }

    void print_leaves(std::ostream& out) {
        _root->print_leaves(out);
    }

    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, Tree<U> const& tree);

    template<typename U>
    friend std::istream& operator>>(std::istream& in, Tree<U>& tree);    
private:
    Node* _root;
};

template<typename U>
std::istream& operator>>(std::istream& in, Tree<U>& tree) {
    if (tree._root)
        tree.~Tree<U>();

    if (in.get() == '(' && in.peek() != ')') {
        tree._root = new typename Tree<U>::Node();
        tree._root->read(in);
    } else
        tree._root = nullptr;

    return in;
}


template<typename U>
std::ostream& operator<<(std::ostream& out, Tree<U> const& tree) {
    if (tree._root) {
        out << '(';
        tree._root->output(out);
        out << ')';
    }

    return out;
}



#endif // TREE_H

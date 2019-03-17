#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <iomanip>
#include <exception>

#include "node.h"
#include "edge.h"

class AVLtree {
    friend GraphWidget;
    friend Edge;

private:
    Node* _root = nullptr;

public:
    AVLtree() {}

    ~AVLtree() {
        Delete(_root);
    }

    bool add(int const& item, GraphWidget* gw) {
        return add(item, _root, gw);
    }

    bool remove(int const& item) {
        if (_root)
            return remove(item, _root);
        else
            throw std::logic_error("Tree is empty");
    }

    int max() {
        if (_root)
            return max(_root);
        else
            throw std::logic_error("Tree is empty");
    }

    int min() {
        if(_root)
            return min(_root);
        else
            throw std::logic_error("Tree is empty");
    }

private:
    void Delete(Node*& node) {
        if (node) {
            Delete(node->left);
            Delete(node->right);

            delete node;
            node = nullptr;
        }
    }

    void rotate_right(Node*& node) {
        Node* x = node;
        Node* y = node->left;

        x->left = y->right;
        y->right = x;
        node = y;

        x->balance += 1;
        if (y->balance < 0) x->balance += -y->balance;

        y->balance += 1;
        if (x->balance > 0) y->balance += x->balance;
    }

    void rotate_left(Node*& node) {
        Node* x = node;
        Node* y = node->right;

        x->right = y->left;
        y->left  = x;
        node = y;

        x->balance -= 1;
        if (y->balance > 0) x->balance -= y->balance;

        y->balance -= 1;
        if (x->balance < 0) y->balance -= -x->balance;
    }

    bool incr_balance(Node*& node) {
        ++node->balance;

        if (node->balance == 0)
            return false;

        if (node->balance == 1)
            return true;

        if (node->balance == 2) {
            if (node->right->balance == -1)
                rotate_right(node->right);

            rotate_left(node);

            return false;
        }

        // ERROR: initially non-balanced node
        return true;
    }

    bool decr_balance(Node*& node) {
        node->balance--;

        if (node->balance == 0)
            return false;

        if (node->balance == -1)
            return true;

        if (node->balance == -2) {
            if (node->left->balance == 1)
                rotate_left(node->left);

            rotate_right(node);

            return false;
        }

        // ERROR: initially non-balanced node
        return true;
    }

    bool add(int const& item, Node*& node, GraphWidget* gw) {
        if (node == nullptr) {
            node = new Node(item, gw);
            gw->_scene->addItem(node);
            return true;
        }
        else if (item > node->value)
            return add(item, node->right, gw) && incr_balance(node);
        else if(item < node->value)
            return add(item, node->left, gw) && decr_balance(node);

        return false; // no need to add already existing node
    }

    bool remove(int const& item, Node*& node) {
        if (node == nullptr)
            return false;
        else if (node->value > item)
            return remove(item, node->left) && incr_balance(node);
        else if (node->value < item)
            return remove(item, node->right) && decr_balance(node);
        else {
            if (node->left == nullptr && node->right == nullptr)
                Delete(node);
            else if (node->left && node->right) {
                Node* current_node = node;
                int min_node_value = min(node->right);

                bool isHeightChanged = remove(min_node_value, node);
                current_node->value = min_node_value;

                return isHeightChanged;
            }
            else {
                Node* node_to_remove = node;

                if (node->left == nullptr) {
                    node = node_to_remove->right;
                    node_to_remove->right = nullptr;
                }
                else {
                    node = node_to_remove->left;
                    node_to_remove->left = nullptr;
                }

                Delete(node_to_remove);
            }

            return true;
        }
    }

    int max(const Node* const& node) {
        if (node)
            return node->right ? max(node->right) : node->value;
    }

    int min(const Node* const& node) {
        if (node)
            return node->left ? min(node->left) : node->value;
    }
};

#endif

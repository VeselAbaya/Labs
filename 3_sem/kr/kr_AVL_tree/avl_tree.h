#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <algorithm>

template<typename T>
class AVL_tree {
    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;
        T data;
        int height = 0;

        ~Node() {
            delete left;
            delete right;
        }
    };

    Node* _root;

    Node* insert(int x, Node* t) {
        if(!t) {
            t = new Node;
            t->data = x;
        }
        else if(x < t->data) {
            t->left = insert(x, t->left);
            if(height(t->left) - height(t->right) == 2) {
                if(x < t->left->data)
                    t = single_right_rotate(t);
                else
                    t = double_right_rotate(t);
            }
        }
        else if(x > t->data) {
            t->right = insert(x, t->right);
            if(height(t->right) - height(t->left) == 2) {
                if(x > t->right->data)
                    t = single_left_rotate(t);
                else
                    t = double_left_rotate(t);
            }
        }

        t->height = std::max(height(t->left), height(t->right))+1;
        return t;
    }

    Node* single_right_rotate(Node* &t) {
        Node* u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = std::max(height(t->left), height(t->right))+1;
        u->height = std::max(height(u->left), t->height)+1;
        return u;
    }

    Node* single_left_rotate(Node* &t) {
        Node* u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = std::max(height(t->left), height(t->right))+1;
        u->height = std::max(height(t->right), t->height)+1 ;
        return u;
    }

    Node* double_left_rotate(Node* &t) {
        t->right = single_right_rotate(t->right);
        return single_left_rotate(t);
    }

    Node* double_right_rotate(Node* &t) {
        t->left = single_left_rotate(t->left);
        return single_right_rotate(t);
    }

    Node* min(Node* t) {
        if(!t)
            return nullptr;
        else if(t->left == nullptr)
            return t;
        else
            return min(t->left);
    }

    Node* max(Node* t) {
        if(!t)
            return nullptr;
        else if(t->right == nullptr)
            return t;
        else
            return max(t->right);
    }

    Node* remove(T x, Node* t) {
        Node* temp;

        // Element not found
        if(!t)
            return nullptr;

        // Searching for element
        else if(x < t->data)
            t->left = remove(x, t->left);
        else if(x > t->data)
            t->right = remove(x, t->right);

        // Element found
        // With 2 children
        else if(t->left && t->right) {
            temp = min(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        // With one or zero child
        else {
            temp = t;
            if(t->left == nullptr)
                t = t->right;
            else if(t->right == nullptr)
                t = t->left;
            delete temp;
        }
        if(!t)
            return t;

        t->height = std::max(height(t->left), height(t->right))+1;

        // If node is unbalanced
        // If left node is deleted, right case
        if(height(t->left) - height(t->right) == 2) {
            // right right case
            if(height(t->left->left) - height(t->left->right) == 1)
                return single_left_rotate(t);
            // right left case
            else
                return double_left_rotate(t);
        }
        // If right node is deleted, left case
        else if(height(t->right) - height(t->left) == 2) {
            // left left case
            if(height(t->right->right) - height(t->right->left) == 1)
                return single_right_rotate(t);
            // left right case
            else
                return double_right_rotate(t);
        }
        return t;
    }

    int height(Node* t) {
        return (!t ? -1 : t->height);
    }

    void in_order(Node* t, std::ostream& out) {
        if(!t)
            return;
        in_order(t->left, out);
        out << t->data << " ";
        in_order(t->right, out);
    }

public:
    AVL_tree() {
        _root = nullptr;
    }

    ~AVL_tree() {
        delete _root;
    }

    void insert(T x) {
        _root = insert(x, _root);
    }

    void remove(T x) {
        _root = remove(x, _root);
    }

    void output(std::ostream& out) {
        in_order(_root, out);
    }
};

#endif // AVL_TREE_H

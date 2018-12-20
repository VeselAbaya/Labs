#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>

#include "node.h"
#include "edge.h"

//! [0]
class GraphWidget : public QGraphicsView {
    friend void Node::display_tree(Node* parent_node, double offset);
    friend void Node::removeEdge(Edge *edge);
    class AVLTree {
        friend GraphWidget;
        GraphWidget* gw;
    public:
        AVLTree(GraphWidget* gw): gw(gw) {}

        ~AVLTree() {
            destroy(root);
        }

//        My Node class for storing data, note how I add height
        void insert(int val) {
            insert(val, root);
            updateAllHeights(root);
            root->removeAllEdges();
            root->display_tree(nullptr, 300);
        }

        void remove(int val) {
            remove(val, root);
            updateAllHeights(root);
            if (root) {
                root->removeAllEdges();
                root->display_tree(nullptr, 300);
            }
        }

//        Rotate a Node branch to the left, in order to balance things
        Node* rotateLeft(Node *&node){
            Node* temp = node->right;
            node->right = temp->left;
            temp->left = node;

//            update the Nodes new height
//            node->right->updateHeight();
            node->updateHeight();
            temp->updateHeight();

            return temp;
        }

//        Rotate a Node branch to the right, in order to balance things
        Node* rotateRight(Node *&node){
            Node* temp = node->left;
            node->left = temp->right;
            temp->right = node;

//            update the Nodes new height
//            node->left->updateHeight();
            node->updateHeight();
            temp->updateHeight();

            return temp;
        }

//        Rotate a Node branch to the right then the left, in order to balance things
        Node* rotateRightLeft(Node *&node){
            Node* temp = node->right;
            node->right = rotateRight(temp);
            return rotateLeft(node);
        }

//        Rotate a Node branch to the left then the right, in order to balance things
        Node* rotateLeftRight(Node *&node){
            Node* temp = node->left;
            node->left = rotateLeft(temp);
            return rotateRight(node);
        }

//        Function that checks each Node's left and right branches to determine if they are unbalanced
//        If they are, we rotate the branches
        void rebalance(Node *&node){
            int hDiff = getDiff(node);
            if (hDiff > 1){
                if (getDiff(node->left) > 0) {
                    node = rotateRight(node);
                } else {
                    node = rotateLeftRight(node);
                }
            } else if(hDiff < -1) {
                if (getDiff(node->right) < 0) {
                    node = rotateLeft(node);
                } else {
                    node = rotateRightLeft(node);
                }
            }
        }

    private:
        Node *root = nullptr;
//        Insert a Node (very similar to BST, except we need to update Node height and then check for rebalance)
        void insert(int d, Node *&node){
            if (node == nullptr){
                node = new Node(d, gw);
                gw->_scene->addItem(node);
                node->updateHeight();
            }
            else {
                if (d < node->value){
                    insert(d, node->left);
                    node->updateHeight();
                    rebalance(node);
                }
                else if (d > node->value){
                    insert(d, node->right);
                    node->updateHeight();
                    rebalance(node);
                }
            }
        }

        void remove(int val, Node*& node) {
            if (node) {
                if (val < node->value) {
                    remove(val, node->left);
                    node->updateHeight();
                    rebalance(node);
                }
                else if (val > node->value) {
                    remove(val, node->right);
                    node->updateHeight();
                    rebalance(node);
                }
                else {
                    if (node->left && node->right) {
                        Node* current_node = node;
                        int min_node_value = min(node->right);

                        remove(min_node_value, node);
                        current_node->value = min_node_value;

                        current_node->updateHeight();
                        rebalance(current_node);
                    }
                    else if (node->left || node->right) {
                        Node* node_to_remove = node;
                        if (node->left) {
                            node = node_to_remove->left;
                            node_to_remove->left = nullptr;
                        }
                        else if (node->right) {
                            node = node_to_remove->right;
                            node_to_remove->right = nullptr;
                        }

                        node->updateHeight();
                        rebalance(node);
                        destroy(node_to_remove);
                    }
                    else {
                        destroy(node);
                    }
                }
            }
        }



        int min(Node*& node) {
            if (node)
                return node->left ? min(node->left) : node->value;
        }

//        Same as BST
        void destroy(Node *&node){
            if (node != nullptr){
                destroy(node->left);
                destroy(node->right);

                gw->_scene->removeItem(node);
                delete node;
                node = nullptr;
            }
        }

//        Get the difference between Node right and left branch heights, if it returns positive
//        We know the left side is greater, if negative, we know the right side is greater
        int getDiff(Node *node){
            int lHeight = 0;
            int rHeight = 0;
            if (node->left != nullptr) {
                lHeight =  node->left->height;
            }
            if (node->right != nullptr) {
                rHeight = node->right->height;
            }
            return lHeight - rHeight;
        }

        void updateAllHeights(Node*& node) {
            if (node) {
                updateAllHeights(node->left);
                updateAllHeights(node->right);
                node->updateHeight();
                rebalance(node);
            }
        }
    };

    Q_OBJECT

    friend AVLTree;

public:
    GraphWidget(QWidget *parent = nullptr);

public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();
    void nodeMenu(Node* node);
    void insertNode(int);

protected:
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void scaleView(qreal scaleFactor);

private:
    AVLTree tree = AVLTree(this);
    int timerId;
    QGraphicsScene* _scene;
};
//! [0]

#endif // GRAPHWIDGET_H

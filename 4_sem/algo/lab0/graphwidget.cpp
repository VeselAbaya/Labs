#include "graphwidget.h"
#include "edge.h"
#include "node.h"

#include <math.h>

#include <QKeyEvent>
#include <QRandomGenerator>

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent), timerId(0)
{
    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-350, -350, 600, 600);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(1.4), qreal(1.4));
    setMinimumSize(600, 600);
    setWindowTitle(tr("Elastic Nodes"));

//    Node *node1 = new Node(this, QString::number(1));
//    Node *node2 = new Node(this, QString::number(2));
//    Node *node3 = new Node(this, QString::number(3));
//    Node *node4 = new Node(this, QString::number(4));
//    centerNode = new Node(this, QString::number(5));
//    Node *node6 = new Node(this, QString::number(6));
//    Node *node7 = new Node(this, QString::number(7));
//    Node *node8 = new Node(this, QString::number(8));
//    Node *node9 = new Node(this, QString::number(9));
//    scene->addItem(node1);
//    scene->addItem(node2);
//    scene->addItem(node3);
//    scene->addItem(node4);
//    scene->addItem(centerNode);
//    scene->addItem(node6);
//    scene->addItem(node7);
//    scene->addItem(node8);
//    scene->addItem(node9);
//    scene->addItem(new Edge(node1, node2));
//    scene->addItem(new Edge(node2, node3));
//    scene->addItem(new Edge(node2, centerNode));
//    scene->addItem(new Edge(node3, node6));
//    scene->addItem(new Edge(node4, node1));
//    scene->addItem(new Edge(node4, centerNode));
//    scene->addItem(new Edge(centerNode, node6));
//    scene->addItem(new Edge(centerNode, node8));
//    scene->addItem(new Edge(node6, node9));
//    scene->addItem(new Edge(node7, node4));
//    scene->addItem(new Edge(node8, node7));
//    scene->addItem(new Edge(node9, node8));

//    node1->setPos(-50, -50);
//    node2->setPos(0, -50);
//    node3->setPos(50, -50);
//    node4->setPos(-50, 0);
//    centerNode->setPos(0, 0);
//    node6->setPos(50, 0);
//    node7->setPos(-50, 50);
//    node8->setPos(0, 50);
//    node9->setPos(50, 50);
}

void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}

void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<Node *> nodes;
    foreach (QGraphicsItem *item, scene()->items()) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }

    foreach (Node *node, nodes)
        node->calculateForces();

    bool itemsMoved = false;
    foreach (Node *node, nodes) {
        if (node->advancePosition())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}

#if QT_CONFIG(wheelevent)
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
#endif

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::shuffle()
{
    foreach (QGraphicsItem *item, scene()->items()) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + QRandomGenerator::global()->bounded(300), -150 + QRandomGenerator::global()->bounded(300));
    }
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void GraphWidget::file_opened(QString file_path) {
    scene()->clear();
    nodes.clear();

    std::ifstream file{file_path.toStdString()};
    Node* mainNode;
    std::string row;
    while (std::getline(file, row)) {
        if (row.empty())
            break;

        auto input = std::stringstream(row);
        std::string value;
        input >> value;

        auto nodeIt = std::find_if(nodes.begin(), nodes.end(), [&value](Node* node) {
            return QString(value.c_str()) == node->value;
        });

        if (nodeIt == nodes.end()) {
            mainNode = new Node(this, QString(value.c_str()));
            scene()->addItem(mainNode);
            mainNode->setPos(qrand() % 250 - 250, qrand() % 250 - 250);

            nodes.push_back(mainNode);
        }
        else {
            mainNode = *nodeIt;
        }

        while (input.good()) {
            input >> value;
            nodeIt = std::find_if(nodes.begin(), nodes.end(), [&value](Node* node) {
                return QString(value.c_str()) == node->value;
            });

            if (nodeIt == nodes.end()) {
                Node* node = new Node(this, QString(value.c_str()));
                nodes.push_back(node);
                scene()->addItem(node);
                scene()->addItem(new Edge(mainNode, node));

                node->setPos(qrand() % 500 - 330, qrand() % 500 - 330);
            }
            else {
                scene()->addItem(new Edge(mainNode, *nodeIt));
            }
        }
    }
}

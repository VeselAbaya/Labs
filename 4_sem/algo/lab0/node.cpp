#include "edge.h"
#include "node.h"
#include "graphwidget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

Node::Node(GraphWidget *graphWidget, QString value): graph(graphWidget), value(value) {
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<Edge *> Node::edges() const
{
    return edgeList;
}

void Node::calculateForces()
{
//    if (!scene() || scene()->mouseGrabberItem() == this) {
//        newPos = pos();
//        return;
//    }

//    // Sum up all forces pushing this item away
//    qreal xvel = 0;
//    qreal yvel = 0;
//    foreach (QGraphicsItem *item, scene()->items()) {
//        Node *node = qgraphicsitem_cast<Node *>(item);
//        if (!node)
//            continue;

//        QPointF vec = mapToItem(node, 0, 0);
//        qreal dx = vec.x();
//        qreal dy = vec.y();
//        double l = 2.0 * (dx * dx + dy * dy);
//        if (l > 0) {
//            xvel += (dx * 150.0) / l;
//            yvel += (dy * 150.0) / l;
//        }
//    }

//    // Now subtract all forces pulling items together
//    double weight = (edgeList.size() + 1) * 10;
//    foreach (Edge *edge, edgeList) {
//        QPointF vec;
//        if (edge->sourceNode() == this)
//            vec = mapToItem(edge->destNode(), 0, 0);
//        else
//            vec = mapToItem(edge->sourceNode(), 0, 0);
//        xvel -= vec.x() / weight;
//        yvel -= vec.y() / weight;
//    }

//    if (qAbs(xvel) < 0.1 && qAbs(yvel) < 0.1)
//        xvel = yvel = 0;

//    QRectF sceneRect = scene()->sceneRect();
//    newPos = pos() + QPointF(xvel, yvel);
//    newPos.setX(qMin(qMax(newPos.x(), sceneRect.left() + 10), sceneRect.right() - 10));
//    newPos.setY(qMin(qMax(newPos.y(), sceneRect.top() + 10), sceneRect.bottom() - 10));
}

bool Node::advancePosition()
{
//    if (newPos == pos())
//        return false;

//    setPos(newPos);
//    return true;
}

QRectF Node::boundingRect() const
{
    qreal adjust = 1;
    return QRectF( -DIAMETR/2 - adjust, -DIAMETR/2 - adjust, DIAMETR + adjust, DIAMETR + adjust);
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-DIAMETR/2, -DIAMETR/2, DIAMETR, DIAMETR);
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setPen(QPen(Qt::black, 0));
    QString str = value;
    if (str.length() == 1)
        painter->drawText(-5, 5, str);
    else
        painter->drawText(-5 - str.length()*str.length(), 5, str);
    painter->drawEllipse(-DIAMETR/2, -DIAMETR/2, DIAMETR, DIAMETR);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (Edge *edge, edgeList)
            edge->adjust();
        graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

bool Node::operator==(Node const& node) const {
    return value == node.value;
}

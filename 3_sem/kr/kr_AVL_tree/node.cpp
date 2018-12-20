/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "edge.h"
#include "node.h"
#include "graphwidget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

Node::Node(int data, GraphWidget *graphWidget, QObject* parent) : QObject(parent), value(data), graph(graphWidget)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);

    QObject::connect(this, SIGNAL(rightClicked(Node*)), graphWidget, SLOT(nodeMenu(Node*)));
}
//! [0]

void Node::updateHeight(){
    int lHeight = 0;
    int rHeight = 0;
    if (left != nullptr) {
        lHeight = left->height;
    }
    if (right != nullptr) {
        rHeight = right->height;
    }
    int max = (lHeight > rHeight) ? lHeight : rHeight;
    height = max + 1;
}

//! [1]
void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

void Node::removeEdge(Edge *edge) {
    if (edge) {
        graph->_scene->removeItem(edge);
        edgeList.removeOne(edge);
    }
}

void Node::removeAllEdges() {
    for (Edge* edge : edgeList)
        removeEdge(edge);
    if (left)
        left->removeAllEdges();
    if (right)
        right->removeAllEdges();
}

Edge* Node::findEdge(Node *dest) {
    for (Edge* edge : edgeList) {
        if (edge->destNode() == dest || edge->sourceNode() == dest ||
                edge->destNode() == this || edge->sourceNode() == this)
            return edge;
    }

    return nullptr;
}

QList<Edge *> Node::edges() const
{
    return edgeList;
}
//! [1]

//! [8]
QRectF Node::boundingRect() const
{
    qreal adjust = 3;
    return QRectF( -DIAMETR/2 - adjust, -DIAMETR/2 - adjust, DIAMETR + adjust, DIAMETR + adjust);
}
//! [8]

//! [9]
QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-DIAMETR/2, -DIAMETR/2, DIAMETR, DIAMETR);
    return path;
}
//! [9]

//! [10]
void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setPen(QPen(Qt::black, 0));
    QString str = QString::number(value);
    if (str.length() == 1)
        painter->drawText(-5, 5, str);
    else
        painter->drawText(-5 - str.length()*str.length(), 5, str);
    painter->drawEllipse(-DIAMETR/2, -DIAMETR/2, DIAMETR, DIAMETR);
}
//! [10]

//! [11]
QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (Edge *edge, edgeList)
            edge->adjust();
//        graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}
//! [11]

void Node::display_tree(Node* parent, double offset) {
    if (parent) {
        QPointF parent_pos = parent->pos();
        if (value < parent->value)
            setPos(parent_pos.x() - offset, parent_pos.y() + DIAMETR*3);
        else
            setPos(parent_pos.x() + offset, parent_pos.y() + DIAMETR*3);
    }
    else
        setPos(300, DIAMETR + DIAMETR/3);

    update();

    if (left) {
        graph->_scene->addItem(new Edge(this, left));
        left->display_tree(this, offset/2);
    }
    if (right) {
        graph->_scene->addItem(new Edge(this, right));
        right->display_tree(this, offset/2);
    }
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if(event->button() == Qt::RightButton) {
        emit rightClicked(this);
    }
}

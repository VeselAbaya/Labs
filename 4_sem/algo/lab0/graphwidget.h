#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <QGraphicsView>
#include <QList>
#include <QVector>
#include <QDebug>

class Node;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

    void itemMoved();

    std::vector<Node*> nodes;
public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();
    void file_opened(QString file_path);

protected:
    void timerEvent(QTimerEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void scaleView(qreal scaleFactor);

private:
    int timerId;
};

#endif // GRAPHWIDGET_H

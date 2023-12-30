#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>
#include "user.h"

class Edge;
class GraphWidget;

//! [0]
class Node : public QGraphicsItem
{
public:
    Node(GraphWidget *graphWidget, const QString& inputName="", int id=0);

    void addEdge(Edge *edge);
    QList<Edge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    void calculateForces();
    bool advancePosition();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    int getUniqueID() const;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QList<Edge *> edgeList;
    QPointF newPos;
    GraphWidget *graph;
    QString name;
    int uniqueID;
};


#endif // NODE_H

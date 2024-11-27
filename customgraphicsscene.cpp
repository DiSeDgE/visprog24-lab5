#include "customgraphicsscene.h"
#include <QGraphicsItem>

CustomGraphicsScene::CustomGraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
{
}

QGraphicsItem* CustomGraphicsScene::itemAt(const QPointF &point, const QTransform &transform) const
{
    return QGraphicsScene::itemAt(point, transform);
}

void CustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit mousePressed(event);
    QGraphicsScene::mousePressEvent(event);
}

void CustomGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit mouseMoved(event);
    QGraphicsScene::mouseMoveEvent(event);
}

void CustomGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit mouseReleased(event);
    QGraphicsScene::mouseReleaseEvent(event);
}

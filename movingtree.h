#ifndef MOVINGTREE_H
#define MOVINGTREE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QObject>
#include <QPainter>

class MovingTree : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT

public:
    MovingTree(QGraphicsScene* scene);
    QRectF boundingRect() const override;
    void handleCollisions(const QRectF &treeRect);

public slots:
    void move();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QGraphicsScene* scene;
    QTimer* timer;
    int speedX;
    int speedY;
};

#endif // MOVINGTREE_H

#ifndef MOVINGHUMAN_H
#define MOVINGHUMAN_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QObject>
#include <QPainter>

class MovingHuman : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT

public:
    MovingHuman(QGraphicsScene* scene);
    QRectF boundingRect() const override;
    void handleCollisions(const QRectF &humanRect);

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

#endif // MOVINGHUMAN_H

#ifndef MOVINGPHONE_H
#define MOVINGPHONE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QObject>
#include <QPainter>

class MovingPhone : public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:

    MovingPhone(QGraphicsScene* scene);

public slots:

    void move();
    void handleCollisions(const QRectF &birdRect);

protected:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QGraphicsScene* scene;
    QTimer* timer;
    int speedX;
    int speedY;
};

#endif // MOVINGPHONE_H

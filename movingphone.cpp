#include "movingphone.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>

MovingPhone::MovingPhone(QGraphicsScene* scene) : QGraphicsRectItem(0, 0, 40, 70) {
    this->scene = scene;
    setBrush(Qt::yellow);
    setPos(100, 100);
    setFlag(QGraphicsItem::ItemIsMovable);
    speedX = 5;
    speedY = 5;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MovingPhone::move);
    timer->start(20);
}

void MovingPhone::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Основная форма телефона
    painter->setBrush(Qt::darkGray);
    painter->drawRoundedRect(boundingRect(), 10, 10);

    // Экран телефона
    QRectF screenRect(5, 5, 30, 50);
    painter->setBrush(Qt::black);
    painter->drawRect(screenRect);

    // Динамик (вверху)
    QRectF speakerRect(15, 8, 10, 3);
    painter->setBrush(Qt::gray);
    painter->drawRoundedRect(speakerRect, 1, 1);

    // Кнопка Home (внизу)
    QRectF homeButton(15, 60, 10, 5);
    painter->setBrush(Qt::gray);
    painter->drawEllipse(homeButton);
}


void MovingPhone::move() {
    setPos(x() + speedX, y() + speedY);
    QRectF birdRect = sceneBoundingRect();
    handleCollisions(birdRect);
}

void MovingPhone::handleCollisions(const QRectF &birdRect) {
    QList<QGraphicsItem*> itemsOnScene = scene->items();
    bool invertX = false;
    bool invertY = false;

    for (QGraphicsItem* item : itemsOnScene) {
        if (item == this) continue;

        if (item->data(0).toString() == "brushItem") {
            continue;
        }

        QRectF itemRect = item->sceneBoundingRect();
        if (!birdRect.intersects(itemRect)) continue;

        QGraphicsPixmapItem* wall = dynamic_cast<QGraphicsPixmapItem*>(item);

        bool collisionLeft = birdRect.right() > itemRect.left() && birdRect.left() < itemRect.left();
        bool collisionRight = birdRect.left() < itemRect.right() && birdRect.right() > itemRect.right();
        bool collisionTop = birdRect.bottom() > itemRect.top() && birdRect.top() < itemRect.top();
        bool collisionBottom = birdRect.top() < itemRect.bottom() && birdRect.bottom() > itemRect.bottom();

        if (wall) {
            if (collisionLeft || collisionRight) invertX = true;
            if (collisionTop || collisionBottom) invertY = true;
        } else {
            if (collisionLeft || collisionRight) invertX = true;
            if (collisionTop || collisionBottom) invertY = true;
        }
    }

    if (invertX) speedX = -speedX;
    if (invertY) speedY = -speedY;
}

#include "movinghuman.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>

MovingHuman::MovingHuman(QGraphicsScene* scene) : QGraphicsEllipseItem(0, 0, 40, 40) {
    this->scene = scene;
    setBrush(Qt::lightGray);
    setPos(0, 0);
    setFlag(QGraphicsItem::ItemIsMovable);
    speedX = 3;
    speedY = 3;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MovingHuman::move);
    timer->start(20);
}

void MovingHuman::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPointF position = this->pos();

    // Голова
    painter->setBrush(QColor(255, 224, 189)); // Светло-бежевый цвет для кожи
    painter->drawEllipse(position.x() - 20, position.y(), 40, 40);

    // Глаза
    painter->setBrush(Qt::white);
    painter->drawEllipse(position.x() - 10, position.y() + 10, 10, 10);
    painter->drawEllipse(position.x() + 5, position.y() + 10, 10, 10);

    painter->setBrush(Qt::black);
    painter->drawEllipse(position.x() - 6, position.y() + 14, 4, 4);
    painter->drawEllipse(position.x() + 9, position.y() + 14, 4, 4);

    // Рот
    painter->setPen(QPen(Qt::red, 2));
    painter->drawArc(position.x() - 10, position.y() + 25, 20, 10, 0 * 16, -180 * 16);

    // Тело
    painter->setBrush(Qt::blue);
    painter->drawRect(position.x() - 15, position.y() + 40, 30, 60);

    // Руки
    painter->setPen(QPen(Qt::black, 2));
    painter->drawLine(position.x() - 15, position.y() + 50, position.x() - 30, position.y() + 80);
    painter->drawLine(position.x() + 15, position.y() + 50, position.x() + 30, position.y() + 80);

    // Ноги
    painter->setPen(QPen(Qt::black, 3));
    painter->drawLine(position.x() - 10, position.y() + 100, position.x() - 10, position.y() + 140);
    painter->drawLine(position.x() + 10, position.y() + 100, position.x() + 10, position.y() + 140);
}

QRectF MovingHuman::boundingRect() const {
    return QRectF(pos().x() - 30, pos().y(), 60, 150);
}

void MovingHuman::move() {
    setPos(x() + speedX, y() + speedY);

    QRectF humanRect = sceneBoundingRect();
    handleCollisions(humanRect);
}

void MovingHuman::handleCollisions(const QRectF &humanRect) {
    QList<QGraphicsItem*> itemsOnScene = scene->items();
    bool invertX = false;
    bool invertY = false;

    for (QGraphicsItem* item : itemsOnScene) {
        if (item == this) continue;

        if (item->data(0).toString() == "brushItem") {
            continue;
        }

        QRectF itemRect = item->sceneBoundingRect();
        if (!humanRect.intersects(itemRect)) continue;

        QGraphicsPixmapItem* wall = dynamic_cast<QGraphicsPixmapItem*>(item);
        bool collisionLeft = humanRect.right() > itemRect.left() && humanRect.left() < itemRect.left();
        bool collisionRight = humanRect.left() < itemRect.right() && humanRect.right() > itemRect.right();
        bool collisionTop = humanRect.bottom() > itemRect.top() && humanRect.top() < itemRect.top();
        bool collisionBottom = humanRect.top() < itemRect.bottom() && humanRect.bottom() > itemRect.bottom();

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

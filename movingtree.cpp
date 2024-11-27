#include "movingtree.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>

MovingTree::MovingTree(QGraphicsScene* scene) : QGraphicsEllipseItem(0, 0, 40, 40) {
    this->scene = scene;
    setBrush(Qt::green);
    setPos(150, 40);
    setFlag(QGraphicsItem::ItemIsMovable);
    speedX = 3;
    speedY = 3;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MovingTree::move);
    timer->start(20);
}

void MovingTree::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPointF position = this->pos();

    // Ствол дерева
    painter->setBrush(QColor(139, 69, 19)); // Коричневый цвет
    painter->drawRect(position.x() + 50, position.y() + 80, 20, 70);

    // Листва дерева (три зелёных круга)
    painter->setBrush(Qt::green);
    painter->drawEllipse(position.x() + 30, position.y() + 40, 60, 60);
    painter->drawEllipse(position.x() + 20, position.y() + 20, 80, 60);
    painter->drawEllipse(position.x() + 40, position.y() + 10, 50, 50);
}

QRectF MovingTree::boundingRect() const {
    return QRectF(pos().x(), pos().y(), 120, 150);
}

void MovingTree::move() {
    setPos(x() + speedX, y() + speedY);
    QRectF treeRect = sceneBoundingRect();
    handleCollisions(treeRect);
}

void MovingTree::handleCollisions(const QRectF &treeRect) {
    QList<QGraphicsItem*> itemsOnScene = scene->items();
    bool invertX = false;
    bool invertY = false;

    for (QGraphicsItem* item : itemsOnScene) {
        if (item == this) continue;

        if (item->data(0).toString() == "brushItem") {
            continue;
        }

        QRectF itemRect = item->sceneBoundingRect();
        if (!treeRect.intersects(itemRect)) continue;

        QGraphicsPixmapItem* wall = dynamic_cast<QGraphicsPixmapItem*>(item);
        bool collisionLeft = treeRect.right() > itemRect.left() && treeRect.left() < itemRect.left();
        bool collisionRight = treeRect.left() < itemRect.right() && treeRect.right() > itemRect.right();
        bool collisionTop = treeRect.bottom() > itemRect.top() && treeRect.top() < itemRect.top();
        bool collisionBottom = treeRect.top() < itemRect.bottom() && treeRect.bottom() > itemRect.bottom();

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

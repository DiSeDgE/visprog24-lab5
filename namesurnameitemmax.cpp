#include "NameSurnameItemMax.h"

NameSurnameItemMax::NameSurnameItemMax(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setFlag(ItemIsMovable);
}

QRectF NameSurnameItemMax::boundingRect() const
{
    return QRectF(0, 0, 300, 90); // Ширина и высота под "MAXIM KARIMOV"
}

void NameSurnameItemMax::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *option,
                               QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(QPen(Qt::black));
    painter->setBrush(QBrush(Qt::black));

    // Рисуем "MAXIM"
    drawLetterM(painter, 0, 0);
    drawLetterA(painter, 40, 0);
    drawLetterX(painter, 80, 0);
    drawLetterI(painter, 120, 0);
    drawLetterM(painter, 160, 0);

    // Рисуем "KARIMOV"
    drawLetterK(painter, 0, 40);
    drawLetterA(painter, 40, 40);
    drawLetterR(painter, 80, 40);
    drawLetterI(painter, 120, 40);
    drawLetterM(painter, 160, 40);
    drawLetterO(painter, 200, 40);
    drawLetterV(painter, 240, 40);
}

void NameSurnameItemMax::drawLetterM(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x, y + 30);
    painter->drawLine(x, y, x + 10, y + 15);
    painter->drawLine(x + 10, y + 15, x + 20, y);
    painter->drawLine(x + 20, y, x + 20, y + 30);
}

void NameSurnameItemMax::drawLetterA(QPainter *painter, int x, int y)
{
    painter->drawLine(x + 10, y, x, y + 30);
    painter->drawLine(x + 10, y, x + 20, y + 30);
    painter->drawLine(x + 5, y + 15, x + 15, y + 15);
}

void NameSurnameItemMax::drawLetterX(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x + 20, y + 30);
    painter->drawLine(x + 20, y, x, y + 30);
}

void NameSurnameItemMax::drawLetterI(QPainter *painter, int x, int y)
{
    painter->drawLine(x + 10, y, x + 10, y + 30);
}

void NameSurnameItemMax::drawLetterK(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x, y + 30);
    painter->drawLine(x, y + 15, x + 20, y);
    painter->drawLine(x, y + 15, x + 20, y + 30);
}

void NameSurnameItemMax::drawLetterR(QPainter *painter, int x, int y)
{
    painter->drawRect(x, y, 5, 30);
    painter->drawEllipse(x + 5, y, 15, 15);
    painter->drawLine(x + 10, y + 15, x + 20, y + 30);
}

void NameSurnameItemMax::drawLetterO(QPainter *painter, int x, int y)
{
    painter->drawEllipse(x, y, 20, 30);
}

void NameSurnameItemMax::drawLetterV(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x + 10, y + 30);
    painter->drawLine(x + 20, y, x + 10, y + 30);
}

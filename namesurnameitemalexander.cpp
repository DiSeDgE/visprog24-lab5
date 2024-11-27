#include "namesurnameitemalexander.h"
#include <QPainter>

NameSurnameItemAlexander::NameSurnameItemAlexander(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setFlag(ItemIsMovable);
}

QRectF NameSurnameItemAlexander::boundingRect() const
{
    return QRectF(0, -5, 200, 70); // Размер области рисования
}

void NameSurnameItemAlexander::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black));
    painter->setBrush(QBrush(Qt::black));

    drawLetterI(painter);
    drawLetterL(painter);
    drawLetterY(painter);
    drawLetterA(painter);

    drawLetterF(painter);
    drawLetterI1(painter);
    drawLetterS(painter);
    drawLetterK(painter);
    drawLetterO(painter);
    drawLetterV(painter);
}

void NameSurnameItemAlexander::drawLetterI(QPainter *painter)
{
    painter->drawRect(5, 0, 5, 25); // Прямая линия для "И"
    painter->drawRect(15, 0, 5, 25);
    painter->drawLine(5, 25, 20, 0);
}

void NameSurnameItemAlexander::drawLetterL(QPainter *painter)
{
    // Вертикальная линия
    painter->drawLine(25, 0, 25, 25); // Вертикальная линия для "Л"

    // Диагональная линия
    painter->drawLine(25, 25, 35, 25); // Диагональная линия для "Л"

}



void NameSurnameItemAlexander::drawLetterY(QPainter *painter)
{
    painter->drawLine(40, 0, 45, 12); // "Й"
    painter->drawLine(50, 0, 45, 12);
    painter->drawLine(45, 12, 45, 25);
    painter->drawEllipse(40, -5, 10, 5);
}

void NameSurnameItemAlexander::drawLetterA(QPainter *painter)
{
    painter->drawLine(60, 25, 65, 0); // "А"
    painter->drawLine(65, 0, 70, 25);
    painter->drawLine(62, 12, 68, 12);
}

void NameSurnameItemAlexander::drawLetterF(QPainter *painter)
{
    painter->drawRect(80, 0, 5, 25); // "Ф"
    painter->drawEllipse(75, 5, 15, 15);
}

void NameSurnameItemAlexander::drawLetterI1(QPainter *painter)
{
    painter->drawRect(100, 0, 5, 25); // "И"
    painter->drawRect(110, 0, 5, 25);
    painter->drawLine(100, 25, 115, 0);
}

void NameSurnameItemAlexander::drawLetterS(QPainter *painter)
{
    painter->drawRect(120, 0, 10, 5); // "С"
    painter->drawRect(120, 20, 10, 5);
    painter->drawRect(120, 5, 5, 15);
}

void NameSurnameItemAlexander::drawLetterK(QPainter *painter)
{
    painter->drawLine(135, 0, 135, 25); // "К"
    painter->drawLine(135, 12, 145, 0);
    painter->drawLine(135, 12, 145, 25);
}

void NameSurnameItemAlexander::drawLetterO(QPainter *painter)
{
    painter->drawEllipse(150, 0, 15, 25); // "О"
}

void NameSurnameItemAlexander::drawLetterV(QPainter *painter)
{
    painter->drawLine(170, 0, 175, 25); // "В"
    painter->drawLine(175, 25, 180, 0);
}

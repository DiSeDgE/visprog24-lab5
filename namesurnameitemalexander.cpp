#include "NameSurnameItemAlexander.h"
#include <QPainter>

NameSurnameItemAlexander::NameSurnameItemAlexander(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setFlag(ItemIsMovable);
}

QRectF NameSurnameItemAlexander::boundingRect() const
{
    return QRectF(0, 0, 300, 60); // Размер области рисования
}

void NameSurnameItemAlexander::paint(QPainter *painter,
                                     const QStyleOptionGraphicsItem *option,
                                     QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(QPen(Qt::black));
    painter->setBrush(QBrush(Qt::black));

    // Имя "Alexander"
    drawLetterA(painter, 0, 0);
    drawLetterL(painter, 30, 0);
    drawLetterE(painter, 60, 0);
    drawLetterX(painter, 90, 0);
    drawLetterA(painter, 120, 0);
    drawLetterN(painter, 150, 0);
    drawLetterD(painter, 180, 0);
    drawLetterE(painter, 210, 0);
    drawLetterR(painter, 240, 0);

    // Фамилия "Sorokin"
    drawLetterS(painter, 0, 30);
    drawLetterO(painter, 30, 30);
    drawLetterR(painter, 60, 30);
    drawLetterO(painter, 90, 30);
    drawLetterK(painter, 120, 30);
    drawLetterI(painter, 150, 30);
    drawLetterN(painter, 180, 30);
}

void NameSurnameItemAlexander::drawLetterA(QPainter *painter, int x, int y)
{
    painter->drawLine(x + 10, y, x, y + 30);      // Левая диагональ
    painter->drawLine(x + 10, y, x + 20, y + 30); // Правая диагональ
    painter->drawLine(x + 5, y + 15, x + 15, y + 15); // Горизонтальная перекладина
}

void NameSurnameItemAlexander::drawLetterL(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x, y + 30);           // Вертикальная линия
    painter->drawLine(x, y + 30, x + 20, y + 30); // Горизонтальная линия
}

void NameSurnameItemAlexander::drawLetterE(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x, y + 30);           // Вертикальная линия
    painter->drawLine(x, y, x + 20, y);           // Верхняя горизонтальная
    painter->drawLine(x, y + 15, x + 15, y + 15); // Средняя горизонтальная
    painter->drawLine(x, y + 30, x + 20, y + 30); // Нижняя горизонтальная
}

void NameSurnameItemAlexander::drawLetterX(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x + 20, y + 30); // Левая диагональ
    painter->drawLine(x + 20, y, x, y + 30); // Правая диагональ
}

void NameSurnameItemAlexander::drawLetterN(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x, y + 30);           // Левая вертикальная
    painter->drawLine(x, y, x + 20, y + 30);      // Диагональная
    painter->drawLine(x + 20, y, x + 20, y + 30); // Правая вертикальная
}

void NameSurnameItemAlexander::drawLetterD(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x, y + 30);                 // Левая вертикальная
    painter->drawArc(x, y, 30, 30, 90 * 16, -180 * 16); // Полукруг
}

void NameSurnameItemAlexander::drawLetterR(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x, y + 30);                 // Левая вертикальная
    painter->drawArc(x, y, 20, 20, 90 * 16, -180 * 16); // Верхний полукруг
    painter->drawLine(x + 10, y + 15, x + 20, y + 30);  // Наклонная
}

void NameSurnameItemAlexander::drawLetterS(QPainter *painter, int x, int y)
{
    painter->drawArc(x, y, 20, 15, 0, 180 * 16);             // Верхняя дуга
    painter->drawArc(x, y + 15, 20, 15, 180 * 16, 180 * 16); // Нижняя дуга
}

void NameSurnameItemAlexander::drawLetterO(QPainter *painter, int x, int y)
{
    painter->drawEllipse(x, y, 20, 30); // Овал
}

void NameSurnameItemAlexander::drawLetterK(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x, y + 30);           // Вертикальная линия
    painter->drawLine(x, y + 15, x + 20, y);      // Верхняя диагональ
    painter->drawLine(x, y + 15, x + 20, y + 30); // Нижняя диагональ
}

void NameSurnameItemAlexander::drawLetterI(QPainter *painter, int x, int y)
{
    painter->drawLine(x + 10, y, x + 10, y + 30); // Вертикальная линия
}

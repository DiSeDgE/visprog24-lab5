#include "namesurnameitemmax.h"
#include <QPainter>

NameSurnameItemMax::NameSurnameItemMax(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setFlag(ItemIsMovable);
}

QRectF NameSurnameItemMax::boundingRect() const
{
    // Увеличиваем ширину для всех букв "Roman Predko"
    return QRectF(0, 0, 360, 40);
}

void NameSurnameItemMax::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(QPen(Qt::black));
    painter->setBrush(QBrush(Qt::black));

    // Рисуем "Roman"
    drawLetterR(painter, 0, 0);
    drawLetterO(painter, 30, 0);
    drawLetterM(painter, 60, 0);
    drawLetterA(painter, 90, 0);
    drawLetterN(painter, 120, 0);

    // Рисуем "Predko"
    drawLetterP(painter, 160, 0);
    drawLetterR(painter, 190, 0);
    drawLetterE(painter, 220, 0);
    drawLetterD(painter, 250, 0);
    drawLetterK(painter, 280, 0);
    drawLetterO(painter, 310, 0);
}

void NameSurnameItemMax::drawLetterR(QPainter *painter, int x, int y)
{
    painter->drawRect(x, y, 5, 30); // Вертикальная часть
    painter->drawEllipse(x + 5, y, 15, 15); // Верхний круг
    painter->drawLine(x + 10, y + 15, x + 20, y + 30); // Наклонная часть
}

void NameSurnameItemMax::drawLetterO(QPainter *painter, int x, int y)
{
    painter->drawEllipse(x, y, 20, 30); // Буква O
}

void NameSurnameItemMax::drawLetterM(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x, y + 30); // Левая вертикальная
    painter->drawLine(x, y, x + 10, y + 15); // Левая диагональ
    painter->drawLine(x + 10, y + 15, x + 20, y); // Правая диагональ
    painter->drawLine(x + 20, y, x + 20, y + 30); // Правая вертикальная
}

void NameSurnameItemMax::drawLetterA(QPainter *painter, int x, int y)
{
    painter->drawLine(x + 10, y, x, y + 30); // Левая диагональ
    painter->drawLine(x + 10, y, x + 20, y + 30); // Правая диагональ
    painter->drawLine(x + 5, y + 15, x + 15, y + 15); // Горизонтальная
}

void NameSurnameItemMax::drawLetterN(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x, y + 30); // Левая вертикальная
    painter->drawLine(x, y, x + 20, y + 30); // Диагональ
    painter->drawLine(x + 20, y, x + 20, y + 30); // Правая вертикальная
}

void NameSurnameItemMax::drawLetterP(QPainter *painter, int x, int y)
{
    painter->drawRect(x, y, 5, 30); // Вертикальная часть
    painter->drawEllipse(x + 5, y, 15, 15); // Верхний круг
}

void NameSurnameItemMax::drawLetterE(QPainter *painter, int x, int y)
{
    painter->drawRect(x, y, 5, 30); // Вертикальная часть
    painter->drawRect(x + 5, y, 15, 5); // Верхний горизонтальный
    painter->drawRect(x + 5, y + 12, 15, 5); // Средний горизонтальный
    painter->drawRect(x + 5, y + 25, 15, 5); // Нижний горизонтальный
}

void NameSurnameItemMax::drawLetterD(QPainter *painter, int x, int y)
{
    painter->drawRect(x, y, 5, 30); // Вертикальная часть
    painter->drawEllipse(x + 5, y, 20, 30); // Правая часть
}

void NameSurnameItemMax::drawLetterK(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x, y + 30); // Вертикальная часть
    painter->drawLine(x, y + 15, x + 20, y); // Верхняя диагональ
    painter->drawLine(x, y + 15, x + 20, y + 30); // Нижняя диагональ
}

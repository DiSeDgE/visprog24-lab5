#include "namesurnameitemdementiy.h"
#include <QPainter>

NameSurnameItemDementiy::NameSurnameItemDementiy(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setFlag(ItemIsMovable);
}

QRectF NameSurnameItemDementiy::boundingRect() const
{
    return QRectF(0, 0, 400, 60); // Увеличенный размер для "Kostya Sukhorukov"
}

void NameSurnameItemDementiy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(QPen(Qt::black));
    painter->setBrush(QBrush(Qt::black));

    // Рисуем "Kostya"
    drawLetterK(painter, 0, 0);
    drawLetterO(painter, 30, 0);
    drawLetterS(painter, 60, 0);
    drawLetterT(painter, 90, 0);
    drawLetterY(painter, 120, 0);
    drawLetterA(painter, 150, 0);

    // Рисуем "Sukhorukov"
    drawLetterS(painter, 0, 30);
    drawLetterU(painter, 30, 30);
    drawLetterK(painter, 60, 30);
    drawLetterH(painter, 90, 30);
    drawLetterO(painter, 120, 30);
    drawLetterR(painter, 150, 30);
    drawLetterU(painter, 180, 30);
    drawLetterK(painter, 210, 30);
    drawLetterO(painter, 240, 30);
    drawLetterV(painter, 270, 30);
}

void NameSurnameItemDementiy::drawLetterK(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x, y + 30); // Вертикальная часть
    painter->drawLine(x, y + 15, x + 20, y); // Верхняя диагональ
    painter->drawLine(x, y + 15, x + 20, y + 30); // Нижняя диагональ
}

void NameSurnameItemDementiy::drawLetterO(QPainter *painter, int x, int y)
{
    painter->drawEllipse(x, y, 20, 30); // Круг для буквы O
}

void NameSurnameItemDementiy::drawLetterS(QPainter *painter, int x, int y)
{
    painter->drawArc(x, y, 20, 15, 0, 180 * 16); // Верхняя дуга
    painter->drawArc(x, y + 15, 20, 15, 180 * 16, 180 * 16); // Нижняя дуга
}

void NameSurnameItemDementiy::drawLetterT(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x + 20, y); // Горизонтальная часть
    painter->drawLine(x + 10, y, x + 10, y + 30); // Вертикальная часть
}

void NameSurnameItemDementiy::drawLetterY(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x + 10, y + 15); // Левая диагональ
    painter->drawLine(x + 20, y, x + 10, y + 15); // Правая диагональ
    painter->drawLine(x + 10, y + 15, x + 10, y + 30); // Вертикальная часть
}

void NameSurnameItemDementiy::drawLetterA(QPainter *painter, int x, int y)
{
    painter->drawLine(x + 10, y, x, y + 30); // Левая диагональ
    painter->drawLine(x + 10, y, x + 20, y + 30); // Правая диагональ
    painter->drawLine(x + 5, y + 15, x + 15, y + 15); // Горизонтальная
}

void NameSurnameItemDementiy::drawLetterU(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x, y + 30); // Левая вертикальная
    painter->drawLine(x + 20, y, x + 20, y + 30); // Правая вертикальная
    painter->drawArc(x, y + 10, 20, 20, 0, -180 * 16); // Нижняя дуга
}

void NameSurnameItemDementiy::drawLetterH(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x, y + 30); // Левая вертикальная
    painter->drawLine(x + 20, y, x + 20, y + 30); // Правая вертикальная
    painter->drawLine(x, y + 15, x + 20, y + 15); // Горизонтальная
}

void NameSurnameItemDementiy::drawLetterR(QPainter *painter, int x, int y)
{
    painter->drawRect(x, y, 5, 30); // Вертикальная часть
    painter->drawEllipse(x + 5, y, 15, 15); // Верхний круг
    painter->drawLine(x + 10, y + 15, x + 20, y + 30); // Наклонная часть
}

void NameSurnameItemDementiy::drawLetterV(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x + 10, y + 30); // Левая диагональ
    painter->drawLine(x + 20, y, x + 10, y + 30); // Правая диагональ
}

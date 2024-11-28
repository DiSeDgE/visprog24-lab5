#include "namesurnameitemdementiy.h"
#include <QPainter>

NameSurnameItemDementiy::NameSurnameItemDementiy(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setFlag(ItemIsMovable);
}

QRectF NameSurnameItemDementiy::boundingRect() const
{
    return QRectF(0, 0, 300, 120); // Увеличенный размер для длинного текста
}

void NameSurnameItemDementiy::paint(QPainter *painter,
                                    const QStyleOptionGraphicsItem *option,
                                    QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(QPen(Qt::black));
    painter->setBrush(QBrush(Qt::black));

    // Рисуем "Dementiy"
    drawLetterD(painter, 0, 0);
    drawLetterE(painter, 30, 0);
    drawLetterM(painter, 60, 0);
    drawLetterE(painter, 90, 0);
    drawLetterN(painter, 120, 0);
    drawLetterT(painter, 150, 0);
    drawLetterI(painter, 180, 0);
    drawLetterY(painter, 210, 0);

    // Рисуем "Shipilov"
    drawLetterS(painter, 0, 40);
    drawLetterH(painter, 30, 40);
    drawLetterI(painter, 60, 40);
    drawLetterP(painter, 90, 40);
    drawLetterI(painter, 120, 40);
    drawLetterL(painter, 150, 40);
    drawLetterO(painter, 180, 40);
    drawLetterV(painter, 210, 40);
}

void NameSurnameItemDementiy::drawLetterD(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x, y + 30);                 // Левая вертикальная
    painter->drawArc(x, y, 30, 30, 90 * 16, -180 * 16); // Правая дуга
}

void NameSurnameItemDementiy::drawLetterE(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x, y + 30);           // Левая вертикальная
    painter->drawLine(x, y, x + 20, y);           // Верхняя горизонтальная
    painter->drawLine(x, y + 15, x + 15, y + 15); // Средняя горизонтальная
    painter->drawLine(x, y + 30, x + 20, y + 30); // Нижняя горизонтальная
}

void NameSurnameItemDementiy::drawLetterM(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x, y + 30);           // Левая вертикальная
    painter->drawLine(x, y, x + 10, y + 15);      // Левая диагональ
    painter->drawLine(x + 10, y + 15, x + 20, y); // Правая диагональ
    painter->drawLine(x + 20, y, x + 20, y + 30); // Правая вертикальная
}

void NameSurnameItemDementiy::drawLetterN(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x, y + 30);           // Левая вертикальная
    painter->drawLine(x, y, x + 20, y + 30);      // Диагональ
    painter->drawLine(x + 20, y, x + 20, y + 30); // Правая вертикальная
}

void NameSurnameItemDementiy::drawLetterT(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x + 20, y);           // Верхняя горизонтальная
    painter->drawLine(x + 10, y, x + 10, y + 30); // Вертикальная
}

void NameSurnameItemDementiy::drawLetterI(QPainter *painter, int x, int y)
{
    painter->drawLine(x + 10, y, x + 10, y + 30); // Вертикальная линия
}

void NameSurnameItemDementiy::drawLetterY(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x + 10, y + 15);           // Левая диагональ
    painter->drawLine(x + 20, y, x + 10, y + 15);      // Правая диагональ
    painter->drawLine(x + 10, y + 15, x + 10, y + 30); // Вертикальная
}

void NameSurnameItemDementiy::drawLetterS(QPainter *painter, int x, int y)
{
    painter->drawArc(x, y, 20, 15, 0, 180 * 16);             // Верхняя дуга
    painter->drawArc(x, y + 15, 20, 15, 180 * 16, 180 * 16); // Нижняя дуга
}

void NameSurnameItemDementiy::drawLetterH(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x, y + 30);           // Левая вертикальная
    painter->drawLine(x + 20, y, x + 20, y + 30); // Правая вертикальная
    painter->drawLine(x, y + 15, x + 20, y + 15); // Горизонтальная
}

void NameSurnameItemDementiy::drawLetterP(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x, y + 30);                 // Левая вертикальная
    painter->drawArc(x, y, 20, 15, 90 * 16, -180 * 16); // Верхняя дуга
}

void NameSurnameItemDementiy::drawLetterL(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x, y + 30);           // Вертикальная линия
    painter->drawLine(x, y + 30, x + 20, y + 30); // Горизонтальная линия
}

void NameSurnameItemDementiy::drawLetterO(QPainter *painter, int x, int y)
{
    painter->drawEllipse(x, y, 20, 30); // Эллипс
}

void NameSurnameItemDementiy::drawLetterV(QPainter *painter, int x, int y)
{
    painter->drawLine(x, y, x + 10, y + 30);      // Левая диагональ
    painter->drawLine(x + 20, y, x + 10, y + 30); // Правая диагональ
}

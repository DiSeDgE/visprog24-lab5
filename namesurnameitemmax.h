#ifndef NAMESURNAMEITEMMAX_H
#define NAMESURNAMEITEMMAX_H

#include <QGraphicsItem>
#include <QPainter>

class NameSurnameItemMax : public QGraphicsItem
{
public:
    explicit NameSurnameItemMax(QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    void drawLetterM(QPainter *painter, int x, int y);
    void drawLetterA(QPainter *painter, int x, int y);
    void drawLetterX(QPainter *painter, int x, int y);
    void drawLetterI(QPainter *painter, int x, int y);
    void drawLetterK(QPainter *painter, int x, int y);
    void drawLetterR(QPainter *painter, int x, int y);
    void drawLetterO(QPainter *painter, int x, int y);
    void drawLetterV(QPainter *painter, int x, int y);
};

#endif // NAMESURNAMEITEMMAX_H

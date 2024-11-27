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
    void drawLetterR(QPainter *painter, int x, int y);
    void drawLetterO(QPainter *painter, int x, int y);
    void drawLetterM(QPainter *painter, int x, int y);
    void drawLetterA(QPainter *painter, int x, int y);
    void drawLetterN(QPainter *painter, int x, int y);
    void drawLetterP(QPainter *painter, int x, int y);
    void drawLetterE(QPainter *painter, int x, int y);
    void drawLetterD(QPainter *painter, int x, int y);
    void drawLetterK(QPainter *painter, int x, int y);
};

#endif // NAMESURNAMEITEMMAX_H

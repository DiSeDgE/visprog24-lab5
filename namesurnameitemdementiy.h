#ifndef NAMESURNAMEITEMDEMENTIY_H
#define NAMESURNAMEITEMDEMENTIY_H

#include <QGraphicsItem>
#include <QPainter>

class NameSurnameItemDementiy : public QGraphicsItem
{
public:
    explicit NameSurnameItemDementiy(QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    void drawLetterK(QPainter *painter, int x, int y);
    void drawLetterO(QPainter *painter, int x, int y);
    void drawLetterS(QPainter *painter, int x, int y);
    void drawLetterT(QPainter *painter, int x, int y);
    void drawLetterY(QPainter *painter, int x, int y);
    void drawLetterA(QPainter *painter, int x, int y);

    void drawLetterU(QPainter *painter, int x, int y);
    void drawLetterH(QPainter *painter, int x, int y);
    void drawLetterR(QPainter *painter, int x, int y);
    void drawLetterV(QPainter *painter, int x, int y);
};

#endif // NAMESURNAMEITEMDEMENTIY_H

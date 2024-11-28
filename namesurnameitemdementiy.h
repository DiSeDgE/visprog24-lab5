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
    void drawLetterD(QPainter *painter, int x, int y);
    void drawLetterE(QPainter *painter, int x, int y);
    void drawLetterM(QPainter *painter, int x, int y);
    void drawLetterN(QPainter *painter, int x, int y);
    void drawLetterT(QPainter *painter, int x, int y);
    void drawLetterI(QPainter *painter, int x, int y);
    void drawLetterY(QPainter *painter, int x, int y);
    void drawLetterS(QPainter *painter, int x, int y);
    void drawLetterH(QPainter *painter, int x, int y);
    void drawLetterP(QPainter *painter, int x, int y);
    void drawLetterL(QPainter *painter, int x, int y);
    void drawLetterO(QPainter *painter, int x, int y);
    void drawLetterV(QPainter *painter, int x, int y);
};

#endif // NAMESURNAMEITEMDEMENTIY_H

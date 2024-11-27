#ifndef NAMESURNAMEITEMALEXANDER_H
#define NAMESURNAMEITEMALEXANDER_H

#include <QGraphicsItem>
#include <QGraphicsScene>

class NameSurnameItemAlexander : public QGraphicsItem
{
public:
    explicit NameSurnameItemAlexander(QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    void drawLetterI(QPainter *painter);
    void drawLetterL(QPainter *painter);
    void drawLetterY(QPainter *painter);
    void drawLetterA(QPainter *painter);
    void drawLetterF(QPainter *painter);
    void drawLetterI1(QPainter *painter);
    void drawLetterS(QPainter *painter);
    void drawLetterK(QPainter *painter);
    void drawLetterO(QPainter *painter);
    void drawLetterV(QPainter *painter);
};

#endif // NAMESURNAMEITEMALEXANDER_H

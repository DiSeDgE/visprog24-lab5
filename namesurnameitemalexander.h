#ifndef NAMESURNAMEITEMALEXANDER_H
#define NAMESURNAMEITEMALEXANDER_H

#include <QGraphicsItem>
#include <QPainter>

class NameSurnameItemAlexander : public QGraphicsItem
{
public:
    explicit NameSurnameItemAlexander(QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    void drawLetterA(QPainter *painter, int x, int y);
    void drawLetterL(QPainter *painter, int x, int y);
    void drawLetterE(QPainter *painter, int x, int y);
    void drawLetterX(QPainter *painter, int x, int y);
    void drawLetterN(QPainter *painter, int x, int y);
    void drawLetterD(QPainter *painter, int x, int y);
    void drawLetterR(QPainter *painter, int x, int y);
    void drawLetterS(QPainter *painter, int x, int y);
    void drawLetterO(QPainter *painter, int x, int y);
    void drawLetterK(QPainter *painter, int x, int y);
    void drawLetterI(QPainter *painter, int x, int y);
};

#endif // NAMESURNAMEITEMALEXANDER_H

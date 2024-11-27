#ifndef GRAPHICEDITOR_H
#define GRAPHICEDITOR_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPen>
#include "customgraphicsscene.h"
#include "shapedialog.h"


namespace Ui {
class GraphicEditor;
}

class GraphicEditor : public QDialog
{
    Q_OBJECT

public:
    explicit GraphicEditor(QWidget *parent = nullptr);
    ~GraphicEditor();

    void updateEraserColor(const QColor &backgroundColor);



private slots:
    void on_btnAddShape_clicked();
    void on_btnBrush_clicked();
    void on_btnEraser_clicked();

    void on_colorPicker_clicked();

    void handleSceneMousePress(QGraphicsSceneMouseEvent *event);
    void handleSceneMouseMove(QGraphicsSceneMouseEvent *event);
    void handleSceneMouseRelease(QGraphicsSceneMouseEvent *event);

    void on_btnBackground_clicked();
    void on_btnDeleteShape_clicked();

    void drawNameAndSurname();
    void drawNameAndSurname1();
    void drawNameAndSurname2();
    void onShapeCreated(const QString &shapeType, const QSize &shapeSize, const QColor &fillColor, const QColor &outlineColor, bool filled, const QList<int> &triangleSides);
protected:
    bool eventFilter(QObject *object, QEvent *event) override;


private:
    Ui::GraphicEditor *ui;
    CustomGraphicsScene *scene;
    bool drawing;
    bool erasing;
    bool movingItem;
    QPen brushPen;
    QPen eraserPen;
    QPointF lastPoint;
    QPointF eraseStart;
    ShapeDialog *shapeDialog;
    QPointF lastClickPos;
};

#endif // GRAPHICEDITOR_H

// shapedialog.h
#ifndef SHAPEDIALOG_H
#define SHAPEDIALOG_H

#include <QDialog>
#include <QColor>
#include <QSize>
#include <QList>


namespace Ui {
class ShapeDialog;
}

class ShapeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShapeDialog(QWidget *parent = nullptr);
    ~ShapeDialog();

    QString getShapeType() const;
    QSize getShapeSize() const;
    QColor getFillColor() const;
    QColor getOutlineColor() const;
    bool isFilled() const;
    QList<int> getTriangleSides() const;
    void setSignalEmitted(bool value);

signals:
    void shapeCreated(const QString &shapeType, const QSize &shapeSize, const QColor &fillColor,
                      const QColor &outlineColor, bool filled, const QList<int> &triangleSides);

private slots:
    void on_buttonBox_accepted();
    void on_fillColorButton_clicked();
    void on_outlineColorButton_clicked();
    void onShapeChanged(int index);

private:
    Ui::ShapeDialog *ui;
    QColor fillColor;
    QColor outlineColor;
    bool isSignalEmitted = false;
};

#endif // SHAPEDIALOG_H

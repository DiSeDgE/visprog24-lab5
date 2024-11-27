#include "shapedialog.h"
#include "ui_shapedialog.h"
#include <QColorDialog>

ShapeDialog::ShapeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShapeDialog),
    fillColor(Qt::white),
    outlineColor(Qt::black),
    isSignalEmitted(false)
{
    ui->setupUi(this);
    connect(ui->shapeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onShapeChanged(int)));
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ShapeDialog::on_buttonBox_accepted);
}

ShapeDialog::~ShapeDialog()
{
    delete ui;
}

QString ShapeDialog::getShapeType() const {
    return ui->shapeComboBox->currentText();
}

QSize ShapeDialog::getShapeSize() const {
    if (getShapeType() == "Прямоугольник") {
        int width = ui->rectWidthSpinBox->value();
        int height = ui->rectHeightSpinBox->value();
        return QSize(width, height);
    } else if (getShapeType() == "Круг") {
        int radius = ui->circleRadiusSpinBox->value();
        return QSize(radius, radius);
    } else if (getShapeType() == "Треугольник") {
        return QSize();
    }
    return QSize();
}

QColor ShapeDialog::getFillColor() const {
    return fillColor;
}

QColor ShapeDialog::getOutlineColor() const {
    return outlineColor;
}

bool ShapeDialog::isFilled() const {
    return ui->fillCheckBox->isChecked();
}

void ShapeDialog::on_fillColorButton_clicked()
{
    QColor color = QColorDialog::getColor(fillColor, this, "Выберите цвет заливки");
    if (color.isValid()) {
        fillColor = color;
    }
}

void ShapeDialog::on_outlineColorButton_clicked()
{
    QColor color = QColorDialog::getColor(outlineColor, this, "Выберите цвет обводки");
    if (color.isValid()) {
        outlineColor = color;
    }
}

void ShapeDialog::onShapeChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

QList<int> ShapeDialog::getTriangleSides() const {
    return {ui->triangleSideASpinBox->value(),
            ui->triangleSideBSpinBox->value(),
            ui->triangleSideCSpinBox->value()};
}

void ShapeDialog::on_buttonBox_accepted()
{
    if (isSignalEmitted) {
        return;
    }

    QString shapeType = getShapeType();
    QSize shapeSize = getShapeSize();
    QColor fillColor = getFillColor();
    QColor outlineColor = getOutlineColor();
    bool filled = isFilled();
    QList<int> triangleSides = getTriangleSides();

    emit shapeCreated(shapeType, shapeSize, fillColor, outlineColor, filled, triangleSides);
    isSignalEmitted = true;
    QDialog::accept();
}

void ShapeDialog::setSignalEmitted(bool value)
{
    isSignalEmitted = value;
}

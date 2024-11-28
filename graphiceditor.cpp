#include "graphiceditor.h"
#include <QColorDialog>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsRectItem>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QPolygonF>
#include <QTransform>
#include "build/Desktop_Qt_6_8_0_llvm_mingw_64_bit-Debug/ui_graphiceditor.h"
#include "movinghuman.h"
#include "movingphone.h"
#include "movingtree.h"
#include "namesurnameitemalexander.h"
#include "namesurnameitemdementiy.h"
#include "namesurnameitemmax.h"
#include "shapedialog.h"
#include "ui_graphiceditor.h"

GraphicEditor::GraphicEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphicEditor),
    drawing(false),
    erasing(false)
{
    ui->setupUi(this);


    scene = new CustomGraphicsScene(this);
    ui->graphicsView->setScene(scene);


    ui->graphicsView->installEventFilter(this);


    ui->brushStyleComboBox->addItem("Solid", static_cast<int>(Qt::SolidLine));
    ui->brushStyleComboBox->addItem("Dash", static_cast<int>(Qt::DashLine));
    ui->brushStyleComboBox->addItem("Dot", static_cast<int>(Qt::DotLine));
    ui->brushStyleComboBox->addItem("Dash Dot", static_cast<int>(Qt::DashDotLine));
    ui->brushStyleComboBox->addItem("Dash Dot Dot", static_cast<int>(Qt::DashDotDotLine));

    shapeDialog = new ShapeDialog(this);
    connect(shapeDialog, &ShapeDialog::shapeCreated, this, &GraphicEditor::onShapeCreated);
    connect(ui->btnDeleteShape, &QPushButton::clicked, this, &GraphicEditor::on_btnDeleteShape_clicked);


    connect(scene, &CustomGraphicsScene::mousePressed, this, &GraphicEditor::handleSceneMousePress);
    connect(scene, &CustomGraphicsScene::mouseMoved, this, &GraphicEditor::handleSceneMouseMove);
    connect(scene, &CustomGraphicsScene::mouseReleased, this, &GraphicEditor::handleSceneMouseRelease);

    scene->setSceneRect(scene->itemsBoundingRect());
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setRenderHint(QPainter::TextAntialiasing);
    ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    connect(ui->btnDrawName, &QPushButton::clicked, this, &GraphicEditor::drawNameAndSurname);
    connect(ui->btnDrawName, &QPushButton::clicked, this, &GraphicEditor::drawNameAndSurname1);
    connect(ui->btnDrawName, &QPushButton::clicked, this, &GraphicEditor::drawNameAndSurname2);

    QGraphicsPixmapItem *topWall = new QGraphicsPixmapItem(QPixmap(":/assets/wall.png"));
    topWall->setPos(-205, -50);
    QTransform transform;
    transform.scale(2.4, 1);
    topWall->setTransform(transform);
    scene->addItem(topWall);

    QGraphicsPixmapItem *bottomWall = new QGraphicsPixmapItem(QPixmap(":/assets/wall.png"));
    bottomWall->setPos(-205,360);
    transform.scale(1, 1);
    bottomWall->setTransform(transform);
    scene->addItem(bottomWall);

    QGraphicsPixmapItem *leftWall = new QGraphicsPixmapItem(QPixmap(":/assets/wall.png"));
    leftWall->setPos(-185, -35);
    leftWall->setRotation(90);
    transform.scale(0.5, 1.1);
    leftWall->setTransform(transform);
    scene->addItem(leftWall);

    QGraphicsPixmapItem *RightWall = new QGraphicsPixmapItem(QPixmap(":/assets/wall.png"));
    RightWall->setPos(660,-35);
    RightWall->setRotation(90);
    transform.scale(1.1, 1);
    RightWall->setTransform(transform);
    scene->addItem(RightWall);

    MovingPhone* bird = new MovingPhone(scene);
    scene->addItem(bird);

    MovingHuman* human = new MovingHuman(scene);
    scene->addItem(human);

    MovingTree *train = new MovingTree(scene);
    scene->addItem(train);


}



GraphicEditor::~GraphicEditor()
{
    delete ui;
}

void GraphicEditor::on_colorPicker_clicked()
{
    QColor selectedColor = QColorDialog::getColor(brushPen.color(), this, "Выберите цвет кисти");

    if (selectedColor.isValid()) {
        brushPen.setColor(selectedColor);
    }
}





void GraphicEditor::on_btnAddShape_clicked()
{
    shapeDialog->setSignalEmitted(false);
    shapeDialog->exec();
}

void GraphicEditor::on_btnDeleteShape_clicked() {
    QPointF scenePos = lastClickPos;

    QRectF searchArea(scenePos.x() - 5, scenePos.y() - 5, 10, 10);
    QList<QGraphicsItem *> items = scene->items(searchArea);

    if (!items.isEmpty()) {
        QGraphicsItem *item = items.first();
        scene->removeItem(item);
        delete item;
    }



}


void GraphicEditor::onShapeCreated(const QString &shapeType, const QSize &shapeSize,
                                   const QColor &fillColor, const QColor &outlineColor,
                                   bool filled, const QList<int> &triangleSides)
{


    QGraphicsItem *item = nullptr;


    if (shapeType == "Прямоугольник") {
        item = new QGraphicsRectItem(0, 0, shapeSize.width(), shapeSize.height());
        QGraphicsRectItem *rectItem = qgraphicsitem_cast<QGraphicsRectItem *>(item);
        rectItem->setPen(QPen(outlineColor));
        if (filled) rectItem->setBrush(QBrush(fillColor));
    } else if (shapeType == "Круг") {
        item = new QGraphicsEllipseItem(0, 0, shapeSize.width(), shapeSize.height());
        QGraphicsEllipseItem *ellipseItem = qgraphicsitem_cast<QGraphicsEllipseItem *>(item);
        ellipseItem->setPen(QPen(outlineColor));
        if (filled) ellipseItem->setBrush(QBrush(fillColor));
    } else if (shapeType == "Треугольник") {
        if (triangleSides.size() == 3) {

            int a = triangleSides[0];
            int b = triangleSides[1];
            int c = triangleSides[2];

            if (a + b > c && a + c > b && b + c > a) {
                double angle = acos((b*b + c*c - a*a) / (2.0 * b * c));
                QPolygonF triangle;
                triangle << QPointF(0, 0) << QPointF(b, 0)
                         << QPointF(c * cos(angle), c * sin(angle));

                item = new QGraphicsPolygonItem(triangle);
                QGraphicsPolygonItem *polygonItem = qgraphicsitem_cast<QGraphicsPolygonItem *>(item);
                polygonItem->setPen(QPen(outlineColor));
                if (filled) polygonItem->setBrush(QBrush(fillColor));
            } else {
            }
        }
    }

    if (item) {
        item->setFlag(QGraphicsItem::ItemIsMovable);
        scene->addItem(item);
    }
}



void GraphicEditor::on_btnBrush_clicked()
{

    int size = ui->brushSizeSpinBox->value();
    Qt::PenStyle style = static_cast<Qt::PenStyle>(ui->brushStyleComboBox->currentData().toInt());


    brushPen.setWidth(size);
    brushPen.setStyle(style);




    erasing = false;
}

void GraphicEditor::on_btnEraser_clicked()
{
    int size = ui->eraserSizeSpinBox->value();
    eraserPen = QPen(Qt::SolidLine);
    eraserPen.setWidth(size);
    eraserPen.setColor(Qt::transparent);

    erasing = true;
}

bool GraphicEditor::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->graphicsView) {
        if (event->type() == QEvent::MouseButtonPress) {
            mousePressEvent(static_cast<QMouseEvent *>(event));
            return true;
        } else if (event->type() == QEvent::MouseMove) {
            mouseMoveEvent(static_cast<QMouseEvent *>(event));
            return true;
        } else if (event->type() == QEvent::MouseButtonRelease) {
            mouseReleaseEvent(static_cast<QMouseEvent *>(event));
            return true;
        }
    }
    return QDialog::eventFilter(object, event);
}


void GraphicEditor::handleSceneMousePress(QGraphicsSceneMouseEvent *event)
{
    QPointF scenePos = event->scenePos();
    lastClickPos = scenePos;

    QGraphicsItem *item = scene->itemAt(scenePos, QTransform());

    if (item && item->flags() & QGraphicsItem::ItemIsMovable) {
        movingItem = true;
    } else {
        movingItem = false;
        if (event->button() == Qt::LeftButton) {
            if (erasing) {
                eraseStart = scenePos;
            } else {
                drawing = true;
                lastPoint = scenePos;
            }
        }
    }
}

void GraphicEditor::handleSceneMouseMove(QGraphicsSceneMouseEvent *event)
{
    if (!movingItem) {
        if (drawing && !erasing) {
            QGraphicsLineItem *line = new QGraphicsLineItem(QLineF(lastPoint, event->scenePos()));
            line->setPen(brushPen);
            scene->addItem(line);

            // Устанавливаем метку для объектов, нарисованных кистью
            line->setData(0, "brushItem");

            lastPoint = event->scenePos();
        } else if (erasing) {
            QRectF eraserArea(event->scenePos().x() - eraserPen.width() / 2,
                              event->scenePos().y() - eraserPen.width() / 2,
                              eraserPen.width(),
                              eraserPen.width());

            QList<QGraphicsItem *> items = scene->items(eraserArea);

            for (QGraphicsItem *item : items) {
                if (item->data(0).toString() == "brushItem") {
                    scene->removeItem(item);
                    delete item;
                }
            }
        }
    }
}

void GraphicEditor::handleSceneMouseRelease(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        drawing = false;
        movingItem = false;
    }
}



void GraphicEditor::on_btnBackground_clicked()
{

    QColor selectedColor = QColorDialog::getColor(scene->backgroundBrush().color(), this, "Выберите цвет фона");

    if (selectedColor.isValid()) {
        scene->setBackgroundBrush(QBrush(selectedColor));


        updateEraserColor(selectedColor);
    }
}


void GraphicEditor::updateEraserColor(const QColor &backgroundColor)
{

    QColor eraserColor = backgroundColor;


    eraserPen.setColor(eraserColor);
}

void GraphicEditor::drawNameAndSurname()
{
    NameSurnameItemAlexander *nameSurnameItemAlexander = new NameSurnameItemAlexander();

    scene->addItem(nameSurnameItemAlexander);
}
void GraphicEditor::drawNameAndSurname1()
{
    NameSurnameItemDementiy *nameSurnameItemDementiy = new NameSurnameItemDementiy();

    scene->addItem(nameSurnameItemDementiy);
}

void GraphicEditor::drawNameAndSurname2()
{
    NameSurnameItemMax *nameSurnameItemMax = new NameSurnameItemMax();

    scene->addItem(nameSurnameItemMax);
}

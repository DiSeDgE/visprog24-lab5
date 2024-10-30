#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>
#include <QCloseEvent>
#include <QColorDialog>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadSettings();

    // Привязываем действия из меню к слотам
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onNewFile);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onOpenFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onSaveFile);
    connect(ui->actionClear, &QAction::triggered, this, &MainWindow::onClearText);
    connect(ui->actionReturn, &QAction::triggered, this, &MainWindow::onRestoreText);
    connect(ui->actionAuthors, &QAction::triggered, this, &MainWindow::showAuthors);
    connect(ui->actionHelp, &QAction::triggered, this, &MainWindow::showHelp);
    connect(ui->actionFind, &QAction::triggered, this, &MainWindow::findText);
    connect(ui->actionReplace, &QAction::triggered, this, &MainWindow::replaceText);
    connect(ui->actionCopy, &QAction::triggered, this, &MainWindow::copyText);
    connect(ui->actionPaste, &QAction::triggered, this, &MainWindow::pasteText);
    connect(ui->actionSaveTable, &QAction::triggered, this, &MainWindow::onSaveTable);
    connect(ui->actionOpenTable, &QAction::triggered, this, &MainWindow::onOpenTable);
    connect(ui->actionDefault, &QAction::triggered, this, &MainWindow::onDefaultSettings);
}

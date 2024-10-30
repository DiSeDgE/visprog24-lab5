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

MainWindow::~MainWindow()
{
    delete ui;
}

// Функция для создания нового файла
void MainWindow::onNewFile()
{
    ui->textEdit->clear();
}

// Функция для сохранения файла
void MainWindow::onSaveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), "", tr("HTML файлы (*.html);;Все файлы (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::WriteOnly | QFile::Text)) {
            QTextStream out(&file);
            out << ui->textEdit->toHtml(); // Сохраняем как HTML
            file.close();
        }
    }
}


// Функция для открытия файла
void MainWindow::onOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "", tr("HTML файлы (*.html);;Все файлы (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream in(&file);
            ui->textEdit->setHtml(in.readAll()); // Открываем как HTML
            file.close();
        }
    }
}

// Функция для сохранения таблицы
void MainWindow::onSaveTable()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить таблицу"), "", tr("HTML файлы (*.html);;Все файлы (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::WriteOnly | QFile::Text)) {
            QTextStream out(&file);

            // Начало HTML таблицы
            out << "<html><body><table border=\"1\">";

            int rowCount = ui->tableWidget->rowCount();
            int columnCount = ui->tableWidget->columnCount();

            // Сохранение каждой строки и колонки таблицы
            for (int row = 0; row < rowCount; ++row) {
                out << "<tr>";  // Начало строки
                for (int column = 0; column < columnCount; ++column) {
                    QTableWidgetItem *item = ui->tableWidget->item(row, column);
                    QString cellText = item ? item->text() : "";

                    // Извлечение стилей ячейки
                    QString fontStyle;
                    if (item) {
                        QFont font = item->font();
                        QColor textColor = item->foreground().color();

                        fontStyle = "style='";

                        // Устанавливаем жирный шрифт
                        if (font.bold()) fontStyle += "font-weight:bold;";
                        // Курсив
                        if (font.italic()) fontStyle += "font-style:italic;";
                        // Зачеркивание
                        if (font.strikeOut()) fontStyle += "text-decoration:line-through;";
                        // Цвет текста
                        fontStyle += "color:" + textColor.name() + ";";
                        // Сохранение шрифта
                        fontStyle += "font-family:" + font.family() + ";";
                        // Сохранение размера шрифта
                        fontStyle += "font-size:" + QString::number(font.pointSize()) + "pt;";
                        fontStyle += "'";
                    }

                    // Сохранение ячейки с форматированием
                    out << "<td " << fontStyle << ">" << cellText << "</td>";
                }
                out << "</tr>";  // Конец строки
            }

            out << "</table></body></html>";
            file.close();
        }
    }
}


// Функция для открытия  таблицы
void MainWindow::onOpenTable()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть таблицу"), "", tr("HTML файлы (*.html);;Все файлы (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream in(&file);
            QString htmlContent = in.readAll();

            // Парсинг HTML для заполнения таблицы
            QRegularExpression rowRegex("<tr>(.+?)</tr>");
            QRegularExpression cellRegex("<td.*?>(.*?)</td>");
            QRegularExpression styleRegex("style='(.*?)'");

            ui->tableWidget->setRowCount(0);
            QRegularExpressionMatchIterator rowMatchIterator = rowRegex.globalMatch(htmlContent);

            while (rowMatchIterator.hasNext()) {
                QRegularExpressionMatch rowMatch = rowMatchIterator.next();
                QString rowData = rowMatch.captured(1);
                QRegularExpressionMatchIterator cellMatchIterator = cellRegex.globalMatch(rowData);
                int currentRowCount = ui->tableWidget->rowCount();
                ui->tableWidget->insertRow(currentRowCount);
                int column = 0;

                while (cellMatchIterator.hasNext()) {
                    QRegularExpressionMatch cellMatch = cellMatchIterator.next();
                    QString cellText = cellMatch.captured(1);

                    // Извлечение стилей ячейки
                    QRegularExpressionMatch styleMatch = styleRegex.match(cellMatch.captured(0));
                    QTableWidgetItem *newItem = new QTableWidgetItem(cellText);

                    if (styleMatch.hasMatch()) {
                        QString styleData = styleMatch.captured(1);

                        // Применение стилей (жирный, курсив, зачеркивание, цвет)
                        if (styleData.contains("font-weight:bold")) newItem->setFont(QFont("", -1, QFont::Bold));
                        if (styleData.contains("font-style:italic")) newItem->setFont(QFont("", -1, QFont::Normal, true));
                        if (styleData.contains("text-decoration:line-through")) {
                            QFont font = newItem->font();
                            font.setStrikeOut(true);
                            newItem->setFont(font);
                        }
                        if (styleData.contains("font-size:")) {
                            QFont font = newItem->font();
                            font.setStrikeOut(true);
                            newItem->setFont(font);
                        }
                        QFont font;
                        // Извлечение размера шрифта
                        QRegularExpression fontSizeRegex("font-size:(\\d+)pt");
                        QRegularExpressionMatch fontSizeMatch = fontSizeRegex.match(styleData);
                        if (fontSizeMatch.hasMatch()) {
                            int fontSize = fontSizeMatch.captured(1).toInt();
                            font.setPointSize(fontSize);
                        }

                        // Извлечение шрифта
                        QRegularExpression fontFamilyRegex("font-family:([^;]+);");
                        QRegularExpressionMatch fontFamilyMatch = fontFamilyRegex.match(styleData);
                        if (fontFamilyMatch.hasMatch()) {
                            QString fontFamily = fontFamilyMatch.captured(1);
                            font.setFamily(fontFamily);
                        }

                        newItem->setFont(font);
                        QRegularExpression colorRegex("color:(#[0-9a-fA-F]{6})");
                        QRegularExpressionMatch colorMatch = colorRegex.match(styleData);
                        if (colorMatch.hasMatch()) {
                            QColor textColor(colorMatch.captured(1));
                            newItem->setForeground(textColor);
                        }
                    }

                    ui->tableWidget->setItem(currentRowCount, column, newItem);
                    column++;
                }
            }
            file.close();
        }
    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tabledialog.h"
#include "findreplacedialog.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadSettings();

    QToolBar *toolbar = addToolBar("Text and Table Controls");

    toolbar->addWidget(new QLabel("Text:"));

    QFontComboBox *fontComboBox = new QFontComboBox(this);
    toolbar->addWidget(fontComboBox);
    connect(fontComboBox, &QFontComboBox::currentFontChanged, this, &MainWindow::onFontChanged);

    QSpinBox *fontSizeSpinBox = new QSpinBox(this);
    fontSizeSpinBox->setRange(8, 72);
    toolbar->addWidget(fontSizeSpinBox);
    connect(fontSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onFontSizeChanged);
    QAction *textColorAction = toolbar->addAction("Text Color");
    connect(textColorAction, &QAction::triggered, this, &MainWindow::onTextColorChanged);

    toolbar->addSeparator();


    toolbar->addWidget(new QLabel("Table:"));

    QSpinBox *paddingSpinBox = new QSpinBox(this);
    paddingSpinBox->setRange(0, 50);
    paddingSpinBox->setValue(10);
    toolbar->addWidget(paddingSpinBox);
    connect(paddingSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onPaddingChanged);


    QAction *cellColorAction = toolbar->addAction("Cell Color");
    connect(cellColorAction, &QAction::triggered, this, &MainWindow::onCellColorChanged);


    findReplaceDialog = new FindReplaceDialog(this);

    connect(findReplaceDialog, &FindReplaceDialog::findNext, this, &MainWindow::findNext);
    connect(findReplaceDialog, &FindReplaceDialog::replace, this, &MainWindow::replace);
    connect(findReplaceDialog, &FindReplaceDialog::replaceAll, this, &MainWindow::replaceAll);

    connect(ui->actionRestore, &QAction::triggered, this, &MainWindow::on_actionRestore_triggered);

    tempFile.setFileTemplate(QDir::temp().filePath("tempFile_X.txt"));
    tempFile.open();
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{



    ui->textEdit->clear();

    currentFile.clear();

}

void MainWindow::on_actionOpen_triggered()
{

    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);


    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    currentFile = fileName;
    QTextStream in(&file);


    QString content = in.readAll();
    ui->textEdit->setHtml(content);

    file.close();
}

void MainWindow::saveToTempFile()
{

    if (!tempFile.isOpen()) {
        if (!tempFile.open()) {
            QMessageBox::warning(this, "Ошибка", "Не удалось открыть временный файл для записи.");
            return;
        }
    }

    QTextStream out(&tempFile);
    out << ui->textEdit->toHtml();
    tempFile.flush();
    tempFile.close();
}

void MainWindow::restoreFromTempFile()
{

    if (tempFile.isOpen()) {
        tempFile.close();
    }


    if (!tempFile.open()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть временный файл для чтения.");
        return;
    }

    QTextStream in(&tempFile);
    QString content = in.readAll();
    ui->textEdit->setHtml(content);
    tempFile.close();
}


void MainWindow::on_actionSave_triggered()
{

    if (currentFile.isEmpty()) {
        QString fileName = QFileDialog::getSaveFileName(this, "Save the file");
        if (fileName.isEmpty()) {
            return;
        }
        currentFile = fileName;
    }

    QFile file(currentFile);

    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    QTextStream out(&file);
    QString content = ui->textEdit->toHtml();
    out << content;
    file.close();
}





void MainWindow::on_actionClear_triggered()
{

    saveToTempFile();
    ui->textEdit->clear();


}

void MainWindow::on_actionRestore_triggered()
{
    restoreFromTempFile();
}



void MainWindow::on_addTableButton_clicked()
{

    TableDialog *dialog = new TableDialog(this);
    connect(dialog, &TableDialog::accepted, this, &MainWindow::on_tableDialogAccepted);

    dialog->exec();
}

void MainWindow::on_tableDialogAccepted()
{
    TableDialog *dialog = qobject_cast<TableDialog *>(sender());
    if (dialog) {
        int rows = dialog->getRowCount();
        int columns = dialog->getColumnCount();


        QString tableHtml = "<table border='1'>";
        for (int i = 0; i < rows; ++i) {
            tableHtml += "<tr>";
            for (int j = 0; j < columns; ++j) {
                tableHtml += "<td style='padding: 20px;'> </td>";
            }
            tableHtml += "</tr>";
        }
        tableHtml += "</table>";

        ui->textEdit->insertHtml(tableHtml);
    }
}



void MainWindow::onFontChanged(const QFont &font)
{
    QTextCharFormat format;
    format.setFont(font);
    mergeFormatOnWordOrSelection(format);
    saveSettings();
}

void MainWindow::onFontSizeChanged(int size)
{
    QTextCharFormat format;
    format.setFontPointSize(size);
    mergeFormatOnWordOrSelection(format);
    saveSettings();
}

void MainWindow::onTextColorChanged()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Select Text Color");
    if (color.isValid()) {
        QTextCharFormat format;
        format.setForeground(color);
        mergeFormatOnWordOrSelection(format);
    }
}

void MainWindow::onPaddingChanged(int padding)
{
    QString paddingStyle = QString("padding: %1px;").arg(padding);

    QTextCursor cursor = ui->textEdit->textCursor();
    QTextTable *table = cursor.currentTable();

    if (table) {
        int rows = table->rows();
        int columns = table->columns();
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < columns; ++col) {
                QTextTableCell cell = table->cellAt(row, col);
                QTextCursor cellCursor = cell.firstCursorPosition();

                QTextBlockFormat cellFormat = cellCursor.blockFormat();

                cellFormat.setLeftMargin(padding);
                cellFormat.setRightMargin(padding);
                cellFormat.setTopMargin(padding);
                cellFormat.setBottomMargin(padding);

                cellCursor.setBlockFormat(cellFormat);
            }
        }
    }

}



void MainWindow::onCellColorChanged()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Выберите цвет ячейки");

    if (color.isValid()) {
        currentCellColor = color;

        QTextCursor cursor = ui->textEdit->textCursor();

        QTextTable *table = cursor.currentTable();
        if (table) {
            QTextTableCell currentCell = table->cellAt(cursor);

            if (currentCell.isValid()) {
                QTextTableCellFormat cellFormat;
                cellFormat.setBackground(currentCellColor);
                currentCell.setFormat(cellFormat);
            } else {
                QMessageBox::warning(this, "Предупреждение", "Нет валидной ячейки под курсором.");
            }
        }
    }
}

void MainWindow::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if (!cursor.hasSelection()) {
        cursor.select(QTextCursor::WordUnderCursor);
    }
    cursor.mergeCharFormat(format);
    ui->textEdit->mergeCurrentCharFormat(format);
}

void MainWindow::on_actionFind_triggered()
{

    findReplaceDialog->show();
}


void MainWindow::findNext()
{
    QString searchText = findReplaceDialog->getSearchText();
    bool caseSensitive = findReplaceDialog->isCaseSensitive();

    QTextDocument::FindFlags flags;
    if (caseSensitive) {
        flags |= QTextDocument::FindCaseSensitively;
    }


    bool found = ui->textEdit->find(searchText, flags);

    if (!found) {
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.setPosition(0);
        ui->textEdit->setTextCursor(cursor);


        found = ui->textEdit->find(searchText, flags);
    }

    if (!found) {
        QMessageBox::information(this, "Поиск", "Текст не найден.");
    }
}


void MainWindow::replace()
{
    QString searchText = findReplaceDialog->getSearchText();
    QString replaceText = findReplaceDialog->getReplaceText();
    bool caseSensitive = findReplaceDialog->isCaseSensitive();

    QTextDocument::FindFlags flags;
    if (caseSensitive) {
        flags |= QTextDocument::FindCaseSensitively;
    }

    QTextCursor cursor = ui->textEdit->textCursor();

    cursor.movePosition(QTextCursor::Start);
    ui->textEdit->setTextCursor(cursor);

    if (ui->textEdit->find(searchText, flags)) {
        cursor = ui->textEdit->textCursor();


        if (cursor.selectedText() == searchText) {
            cursor.insertText(replaceText);


            cursor.movePosition(QTextCursor::NextCharacter);
            ui->textEdit->setTextCursor(cursor);
        }
    } else {
        QMessageBox::information(this, "Замена", "Текст не найден.");
    }
}






void MainWindow::replaceAll()
{
    QString searchText = findReplaceDialog->getSearchText();
    QString replaceText = findReplaceDialog->getReplaceText();
    bool caseSensitive = findReplaceDialog->isCaseSensitive();

    QTextDocument::FindFlags flags;
    if (caseSensitive) {
        flags |= QTextDocument::FindCaseSensitively;
    }

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::Start);
    ui->textEdit->setTextCursor(cursor);

    int replacements = 0;
    while (ui->textEdit->find(searchText, flags)) {
        QTextCursor replaceCursor = ui->textEdit->textCursor();
        replaceCursor.insertText(replaceText);
        ++replacements;
    }

    if (replacements == 0) {
        QMessageBox::information(this, "Замена", "Текст не найден.");
    } else {
        QMessageBox::information(this, "Замена", QString("Заменено %1 вхождений.").arg(replacements));
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{

    if (ui->textEdit->document()->isModified()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Сохранить изменения?", "У вас есть несохранённые изменения. Хотите сохранить их?",
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (reply == QMessageBox::Yes) {
            if (currentFile.isEmpty()) {
                on_actionSave_triggered();
            } else {
                saveToTempFile();
            }
        } else if (reply == QMessageBox::Cancel) {
            event->ignore();
            return;
        }
    }

    event->accept();
}



void MainWindow::saveSettings()
{
    QSettings settings("MyCompany", "MyApp");

    settings.setValue("font", ui->textEdit->currentFont());
    settings.setValue("fontSize", ui->textEdit->fontPointSize());

    QFontComboBox *fontComboBox = findChild<QFontComboBox*>();
    if (fontComboBox) {
        settings.setValue("fontComboBox", fontComboBox->currentFont().family());
    }
    QSpinBox *fontSizeSpinBox = findChild<QSpinBox*>();
    if (fontSizeSpinBox) {
        settings.setValue("fontSizeSpinBox", fontSizeSpinBox->value());
    }

    QSpinBox *paddingSpinBox = findChild<QSpinBox*>();
    if (paddingSpinBox) {
        settings.setValue("padding", paddingSpinBox->value());
    }


    QComboBox *comboBox = findChild<QComboBox*>();
    if (comboBox) {
        settings.setValue("comboBoxIndex", comboBox->currentIndex());
        settings.setValue("comboBoxText", comboBox->currentText());
    }
    if (fontSizeSpinBox) {
        settings.setValue("fontSizeSpinBox", fontSizeSpinBox->value());
    }
}


void MainWindow::loadSettings()
{
    QSettings settings("MyCompany", "MyApp");


    QFont font = settings.value("font", QFont()).value<QFont>();
    if (!font.family().isEmpty()) {
        ui->textEdit->setCurrentFont(font);
    }

    int fontSize = settings.value("fontSize", 12).toInt();
    ui->textEdit->setFontPointSize(fontSize);


    QString fontFamily = settings.value("fontComboBox", "").toString();
    if (!fontFamily.isEmpty()) {
        QFontComboBox *fontComboBox = findChild<QFontComboBox*>();
        if (fontComboBox) {
            fontComboBox->setCurrentFont(QFont(fontFamily));
        }
    }


    int savedFontSize = settings.value("fontSizeSpinBox", 12).toInt();
    QSpinBox *fontSizeSpinBox = findChild<QSpinBox*>();
    if (fontSizeSpinBox) {
        fontSizeSpinBox->setValue(savedFontSize);
    }

    int savedPadding = settings.value("padding", 10).toInt();
    QSpinBox *paddingSpinBox = findChild<QSpinBox*>();
    if (paddingSpinBox) {
        paddingSpinBox->setValue(savedPadding);
    }


    int comboBoxIndex = settings.value("comboBoxIndex", -1).toInt();
    QString comboBoxText = settings.value("comboBoxText", "").toString();
    QComboBox *comboBox = findChild<QComboBox*>();
    if (comboBox) {
        if (comboBoxIndex != -1) {
            comboBox->setCurrentIndex(comboBoxIndex);
        } else if (!comboBoxText.isEmpty()) {
            int index = comboBox->findText(comboBoxText);
            if (index != -1) {
                comboBox->setCurrentIndex(index);
            }
        }
    }
}



void MainWindow::onComboBoxChanged(int index)
{
    QSettings settings("MyCompany", "MyApp");
    settings.setValue("comboBoxIndex", index);
    saveSettings();
}

void MainWindow::onSpinBoxChanged(int value)
{
    QSettings settings("MyCompany", "MyApp");
    settings.setValue("spinBoxValue", value);
    saveSettings();
}



#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QTextStream>
#include <QMainWindow>
#include <QTextEdit>
#include <QTableWidget>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTemporaryFile>
#include <QFontDialog>
#include <QColorDialog>
#include <QComboBox>
#include <QFontDatabase>
#include <QSpinBox>
#include <QTextTable>
#include <QTextTableCell>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QLabel>
#include <QPushButton>
#include <QInputDialog>
#include <QSettings>
#include <QFontComboBox>
#include <QToolBar>

#include "findreplacedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionClear_triggered();
    void on_addTableButton_clicked();
    void on_tableDialogAccepted();

    void onFontChanged(const QFont &font);
    void onFontSizeChanged(int size);
    void onTextColorChanged();
    void onPaddingChanged(int padding);
    void onCellColorChanged();

    void on_actionFind_triggered();
    void findNext();
    void replace();
    void replaceAll();

    void saveToTempFile();
    void restoreFromTempFile();
    void on_actionRestore_triggered();

    void closeEvent(QCloseEvent *event);

    void saveSettings();
    void loadSettings();
    void onComboBoxChanged(int index);
    void onSpinBoxChanged(int value);

    void openGraphicEditor();

private:
    Ui::MainWindow *ui;
    QString currentFile;
    QTemporaryFile tempFile;
    int currentPadding = 10;
    QColor currentCellColor;
    FindReplaceDialog *findReplaceDialog;
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
};

#endif // MAINWINDOW_H


#include "mainwindow.h"
#include <QIcon>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QIcon icon(":assets/app.icns");
    a.setWindowIcon(icon);
    MainWindow w;
    w.show();
    return a.exec();
}

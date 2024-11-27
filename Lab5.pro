QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Вы можете сделать так, чтобы ваш код не компилировался, если он использует устаревшие API.
# Для этого раскомментируйте следующую строку.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000  # отключает все API, устаревшие до Qt 6.0.0

SOURCES += \
    customgraphicsscene.cpp \
    findreplacedialog.cpp \
    graphiceditor.cpp \
    main.cpp \
    mainwindow.cpp \
    movinghuman.cpp \
    movingphone.cpp \
    movingtree.cpp \
    namesurnameitemalexander.cpp \
    namesurnameitemdementiy.cpp \
    namesurnameitemmax.cpp \
    shapedialog.cpp \
    tabledialog.cpp

HEADERS += \
    customgraphicsscene.h \
    findreplacedialog.h \
    graphiceditor.h \
    mainwindow.h \
    movinghuman.h \
    movingphone.h \
    movingtree.h \
    namesurnameitemalexander.h \
    namesurnameitemdementiy.h \
    namesurnameitemmax.h \
    shapedialog.h \
    tabledialog.h

FORMS += \
    findreplacedialog.ui \
    graphiceditor.ui \
    mainwindow.ui \
    shapedialog.ui \
    tabledialog.ui

# Добавьте файл ресурсов
RESOURCES += resources.qrc


# Правила развертывания по умолчанию
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

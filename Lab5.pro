QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Вы можете сделать так, чтобы ваш код не компилировался, если он использует устаревшие API.
# Для этого раскомментируйте следующую строку.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000  # отключает все API, устаревшие до Qt 6.0.0

SOURCES += \
    findreplacedialog.cpp \
    main.cpp \
    mainwindow.cpp \
    tabledialog.cpp

HEADERS += \
    findreplacedialog.h \
    mainwindow.h \
    tabledialog.h

FORMS += \
    findreplacedialog.ui \
    mainwindow.ui \
    tabledialog.ui

# Добавьте файл ресурсов
RESOURCES += resources.qrc


# Правила развертывания по умолчанию
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

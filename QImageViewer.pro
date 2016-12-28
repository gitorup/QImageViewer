# QT for image viewer
# author    hancq
# date      2016-10-18
QT += widgets
TARGET = QImageViewer

SOURCES += \
    main.cpp

RESOURCES += \
    images.qrc

INCLUDEPATH += mainwindow

include(mainwindow/mainwindow.pri)
include(imageviewer/imageviewer.pri)

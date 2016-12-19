# QT for image viewer
# author    hancq
# date      2016-10-18
QT += widgets
TARGET = QImageViewer

SOURCES += \
    main.cpp

RESOURCES += \
    images.qrc

INCLUDEPATH += src

include(src/src.pri)

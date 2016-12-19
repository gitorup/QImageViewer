#include <QApplication>

#include "qimageviewer.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QImageViewer imageViewer;
    imageViewer.resize(640,480);
    imageViewer.setWindowIcon(QIcon(":/images/logo.png"));
    imageViewer.show();

    return app.exec();
}

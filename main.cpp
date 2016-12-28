#include <QApplication>

#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.resize(640, 480);
    mainWindow.setWindowIcon(QIcon(":/images/logo.png"));
    mainWindow.show();

    return app.exec();
}

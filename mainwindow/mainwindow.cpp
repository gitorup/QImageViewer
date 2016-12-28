#include "mainwindow.h"
#include "qimageviewer.h"

#include <QWidget>
#include <QImage>
#include <QFileDialog>
#include <QPixmap>
#include <QAction>
#include <QMessageBox>
#include <QDebug>
#include <QScrollArea>
#include <QGridLayout>
#include <QImageReader>
#include <QErrorMessage>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    /* init main window */
    initMainWindow();

    /* init ui */
    initUiComponent();

    /* init resource */
    initImageResource();

    //qDebug() << QImageReader::supportedImageFormats();
}

void MainWindow::initImageResource(void)
{
    index = -1;
    filename.clear();

    imageLabel->clear();
    imageLabel->resize(QSize(200, 100));
    setWindowTitle(tr("QImageViewer"));
}

void MainWindow::loadImageResource(QString &filename)
{
    QImage image;
    QPixmap pixmap;

    if (!image.load(filename)) {
        QMessageBox::information(this,
                                 tr("Error"),
                                 tr("Open file error"));
        return ;
    }

    pixmap = QPixmap::fromImage(image);
    imageSize = pixmap.size();
    imageLabel->setPixmap(pixmap);
    imageLabel->resize(imageSize);
    setWindowTitle(QFileInfo(filename).fileName() + tr(" - QImageViewer"));
}

void MainWindow::openActionTriggered(void)
{
    filename = QFileDialog::getOpenFileName(this, tr("Select image:"),
        "D:\\Documents\\Pictures", tr("Images (*.jpg *.jpeg *.png *.bmp *.gif)"));
    if (filename.isEmpty()) {
        return ;
    }

    /* get file list */
    path = QFileInfo(filename).absolutePath();
    initImgInfoList(imgInfoList);

    /* load image */
    loadImageResource(filename);
}

void MainWindow::closeActionTriggered(void)
{
    initImageResource();
}

void MainWindow::lastActionTriggered(void)
{
    if (index < 0) {
        QMessageBox::information(this,
                                 tr("Error"),
                                 tr("Open a image, please!"));
        return ;
    }

    while (1) {
        index = index - 1;
        int count = imgInfoList.count();
        //qDebug() << "left count: " << count << "index: " << index;
        if (index < 0) {
            QMessageBox::information(this, tr("Tip"), tr("This is the first image."));
            index = count - 1;
        }

        filename.clear();
        filename.append(path);
        filename += "/";
        filename += imgInfoList.at(index).fileName();
        //qDebug() << "filname: " << filename;

        if (!QFile(filename).exists()) {
            imgInfoList.removeAt(index);
            continue;
        } else {
            break;
        }
    }

    loadImageResource(filename);
}

void MainWindow::nextActionTriggered(void)
{
    if (index < 0) {
        QMessageBox::information(this,
                                 tr("Error"),
                                 tr("Open a image, please!"));
        return ;
    }

    while (1) {
        index = index + 1;
        int count = imgInfoList.count();
        //qDebug() << "right count: " << count << "index: " << index;
        if (index == count) {
            QMessageBox::information(this, tr("Tip"), tr("This is the last image."));
            index = 0;
        }

        filename.clear();
        filename.append(path);
        filename += "/";
        filename += imgInfoList.at(index).fileName();
        //qDebug() << "filname: " << filename;

        if (!QFile(filename).exists()) {
            imgInfoList.removeAt(index);
            continue;
        } else {
            break;
        }
    }

    loadImageResource(filename);
}

void MainWindow::toLeftActionTriggered(void)
{
    if (filename.isEmpty()) {
        QMessageBox::information(this,
                                 tr("Error"),
                                 tr("Open a image, please!"));
        return ;
    }

    QImage imgRotate;
    QMatrix matrix;
    QPixmap pixmap;
    QImage image;

    imageAngle += 3;
    imageAngle = imageAngle % 4;
    qDebug() << "angle:%d" << imageAngle;
    matrix.rotate(imageAngle * 90);

    image.load(filename);
    imgRotate = image.transformed(matrix);
    pixmap = QPixmap::fromImage(imgRotate);
    imageSize = pixmap.size();

    imageLabel->resize(imgRotate.size());
    imageLabel->setPixmap(pixmap);
}

void MainWindow::toRightActionTriggered(void)
{
    if (filename.isEmpty()) {
        QMessageBox::information(this,
                                 tr("Error"),
                                 tr("Open a image, please!"));
        return ;
    }

    QImage imgRotate;
    QMatrix matrix;
    QPixmap pixmap;
    QImage image;

    imageAngle += 1;
    imageAngle = imageAngle % 4;
    //qDebug() << "angle:%d" << imageAngle;
    matrix.rotate(imageAngle * 90);

    image.load(filename);
    imgRotate = image.transformed(matrix);
    pixmap = QPixmap::fromImage(imgRotate);
    imageSize = pixmap.size();

    imageLabel->resize(imgRotate.size());
    imageLabel->setPixmap(pixmap);
}

void MainWindow::toEnlargeActionTriggered(void)
{
    if (filename.isEmpty()) {
        QMessageBox::information(this,
                                 tr("Error"),
                                 tr("Open a image, please!"));
        return ;
    }

    QImage imgScaled;
    QPixmap pixmap;
    QImage image;
    QImage imgRotate;
    QMatrix matrix;

    image.load(filename);
    matrix.rotate(imageAngle * 90);
    imgRotate = image.transformed(matrix);

    imgScaled = imgRotate.scaled(imageSize.width() * 1.2,
                             imageSize.height() * 1.2,
                             Qt::KeepAspectRatio);

    pixmap = QPixmap::fromImage(imgScaled);
    imageSize = pixmap.size();
    //qDebug() << "width:%d, height:%d" << imageSize.width() << imageSize.height();

    imageLabel->setPixmap(pixmap);
    imageLabel->resize(imageSize);
}

void MainWindow::toLessenActionTriggered(void)
{
    if (filename.isEmpty()) {
        QMessageBox::information(this,
                                 tr("Error"),
                                 tr("Open a image, please!"));
        return ;
    }

    QImage imgScaled;
    QPixmap pixmap;
    QImage image;
    QImage imgRotate;
    QMatrix matrix;

    image.load(filename);
    matrix.rotate(imageAngle * 90);
    imgRotate = image.transformed(matrix);

    imgScaled = imgRotate.scaled(imageSize.width() * 0.8,
                             imageSize.height() * 0.8,
                             Qt::KeepAspectRatio);

    pixmap = QPixmap::fromImage(imgScaled);
    imageSize = pixmap.size();
    //qDebug() << "width:%d, height:%d" << imageSize.width() << imageSize.height();

    imageLabel->setPixmap(pixmap);
    imageLabel->resize(imageSize);
}

void MainWindow::deleteActionTriggered(void)
{
    if (filename.isEmpty()) {
        QMessageBox::information(this,
                                 tr("Error"),
                                 tr("Open a image, please!"));
        return ;
    }

    QMessageBox message(QMessageBox::Warning,
                        tr("Warning"),
                        tr("Do you want to delete this image?"),
                        QMessageBox::Yes|QMessageBox::No,
                        NULL);
    if (message.exec() == QMessageBox::No) {
        return ;
    }

    if (QFile::remove(filename)) {
        qDebug() << "remove success: " << filename;
    } else {
        qDebug() << "remove failed: " << filename;
    }

    imageLabel->clear();
    imageLabel->resize(QSize(200, 100));
    setWindowTitle(tr("QImageViewer"));
}

void MainWindow::initImgInfoList(QFileInfoList &imgInfoList)
{
    QDir dir = QFileInfo(filename).absolutePath();
    QFileInfoList infoList = dir.entryInfoList(QDir::Files);
    qDebug() << "GET:" << infoList.count() << dir;

    QFileInfo info;
    for (int i = 0; i < infoList.count(); i++) {
        info = infoList.at(i);
        //qDebug() << i << info.absolutePath();
        QString suffix = info.suffix();

        if (suffix == "jpg" || suffix == "bmp" || suffix == "png"
            || suffix == "gif" || suffix == "jpeg") {
            imgInfoList.append(info);
            //qDebug() << "getImgInfoList:" << i << info.absolutePath() << info.suffix();
        }
    }

    QFileInfo curImageInfo = QFileInfo(filename);
    for (int j = 0; j < imgInfoList.count(); j++) {
        info = imgInfoList.at(j);
        if (info.fileName() == curImageInfo.fileName()) {
            index = j;
            qDebug() << "curImage index: " << index;
        }
    }
}

void MainWindow::setQImageViewerWidget(void)
{
    /* label show image */
    imageLabel = new QLabel();
    imageAngle = 0;

    QScrollArea *imageScrollArea = new QScrollArea();
    imageScrollArea->setAlignment(Qt::AlignCenter);
    imageScrollArea->setFrameShape(QFrame::NoFrame);
    imageScrollArea->setWidget(imageLabel);

    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(imageScrollArea, 0, 0);
    centralWidget->setLayout(mainLayout);
}

void MainWindow::setWindowComponet(void)
{
    openAction = new QAction(tr("Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open a image."));
    openAction->setIcon(QIcon(":/images/open.png"));

    closeAction = new QAction(tr("Close"), this);
    closeAction->setShortcut(QKeySequence::Close);
    closeAction->setStatusTip(tr("Close a image."));
    closeAction->setIcon(QIcon(":/images/close.png"));

    lastAction = new QAction(tr("Last"), this);
    lastAction->setStatusTip(tr("Last image."));
    lastAction->setIcon(QIcon(":/images/left.png"));

    nextAction = new QAction(tr("Next"), this);
    nextAction->setStatusTip(tr("Next image"));
    nextAction->setIcon(QIcon(":/images/right.png"));

    toLeftAction = new QAction(tr("LeftSpin"), this);
    toLeftAction->setStatusTip(tr("To Left."));
    toLeftAction->setIcon(QIcon(":/images/toLeft.png"));

    toRightAction = new QAction(tr("RightSpin"), this);
    toRightAction->setStatusTip(tr("To Right."));
    toRightAction->setIcon(QIcon(":/images/toRight.png"));

    toEnlargeAction = new QAction(tr("Enlarge"), this);
    toEnlargeAction->setStatusTip(tr("To Enlarge."));
    toEnlargeAction->setIcon(QIcon(":/images/large.png"));

    toLessenAction = new QAction(tr("Lessen"), this);
    toLessenAction->setStatusTip(tr("To Lessen."));
    toLessenAction->setIcon(QIcon(":/images/small.png"));

    deleteAction = new QAction(tr("Delete"), this);
    deleteAction->setStatusTip(tr("Delete a image"));
    deleteAction->setIcon(QIcon(":/images/clear.png"));
    deleteAction->setShortcut(QKeySequence::Delete);

    QAction *exitAction = new QAction(tr("Exit"), this);
    exitAction->setStatusTip(tr("Exit"));
    exitAction->setIcon(QIcon(":/images/quit.png"));
    exitAction->setShortcut(QKeySequence::Quit);

    QAction *aboutQt = new QAction(tr("About Qt"), this);
    aboutQt->setStatusTip(tr("About Qt"));
    aboutQt->setIcon(QIcon(":/images/Qt.png"));

    QAction *about = new QAction(tr("About QImageViewer"), this);
    about->setStatusTip(tr("About QImageViewer"));
    about->setIcon(QIcon(":/images/help.png"));

    QMenu *fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(closeAction);
    fileMenu->addSeparator();
    fileMenu->addAction(deleteAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    QMenu *operationMenu = menuBar->addMenu(tr("Operate"));
    operationMenu->addAction(lastAction);
    operationMenu->addAction(nextAction);
    operationMenu->addSeparator();
    operationMenu->addAction(toLeftAction);
    operationMenu->addAction(toRightAction);
    operationMenu->addSeparator();
    operationMenu->addAction(toEnlargeAction);
    operationMenu->addAction(toLessenAction);

    QMenu *helpMenu = menuBar->addMenu(tr("Help"));
    helpMenu->addAction(aboutQt);
    helpMenu->addAction(about);

    toolBar->addAction(openAction);
    toolBar->addAction(closeAction);
    toolBar->addAction(lastAction);
    toolBar->addAction(nextAction);
    toolBar->addAction(toLeftAction);
    toolBar->addAction(toRightAction);
    toolBar->addAction(toEnlargeAction);
    toolBar->addAction(toLessenAction);
    toolBar->addAction(deleteAction);
    toolBar->addAction(about);

    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openActionTriggered()));
    connect(closeAction, SIGNAL(triggered(bool)), this, SLOT(closeActionTriggered()));
    connect(lastAction, SIGNAL(triggered(bool)), this, SLOT(lastActionTriggered()));
    connect(nextAction, SIGNAL(triggered(bool)), this, SLOT(nextActionTriggered()));
    connect(toLeftAction, SIGNAL(triggered(bool)), this, SLOT(toLeftActionTriggered()));
    connect(toRightAction, SIGNAL(triggered(bool)), this, SLOT(toRightActionTriggered()));
    connect(toEnlargeAction, SIGNAL(triggered(bool)), this, SLOT(toEnlargeActionTriggered()));
    connect(toLessenAction, SIGNAL(triggered(bool)), this, SLOT(toLessenActionTriggered()));
    connect(deleteAction, SIGNAL(triggered(bool)), this, SLOT(deleteActionTriggered()));

    connect(about, SIGNAL(triggered(bool)), this, SLOT(aboutTriggered()));
    connect(aboutQt, SIGNAL(triggered(bool)), this, SLOT(aboutQtTriggered()));
    connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
}

void MainWindow::aboutQtTriggered(void)
{
    qApp->aboutQt();
}

void MainWindow::aboutTriggered(void)
{
    aboutWidget.setWindowTitle("Help Infomation");
    aboutWidget.setWindowIcon(QIcon(":/images/help.png"));
    aboutWidget.setFixedSize(QABOUT_WIDGET_WIDTH, QABOUT_WIDGET_HEIGHT);

    aboutWidget.show();
}

void MainWindow::initUiComponent(void)
{
    /* set menu and toolbar */
    setWindowComponet();

    /* image show widget */
    setQImageViewerWidget();
}

void MainWindow::initMainWindow(void)
{
    menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    toolBar = new QToolBar(this);
    addToolBar(toolBar);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
}


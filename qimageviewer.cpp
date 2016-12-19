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

QImageViewer::QImageViewer(QWidget *parent) : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/images/add.png"));

    /* init main window */
    initMainWindow();

    /* init ui */
    initUiComponent();

    /* init resource */
    initImageResource();

    //qDebug() << QImageReader::supportedImageFormats();
}

void QImageViewer::initImageResource(void)
{
    index = -1;
    filename.clear();

    imageLabel->clear();
    imageLabel->resize(QSize(200, 100));
    setWindowTitle(tr("QImageViewer"));
}

void QImageViewer::loadImageResource(QString &filename)
{
    QImage image;
    if (!image.load(filename)) {
        QMessageBox::information(this,
                                 tr("Error"),
                                 tr("Open file error"));
        return ;
    }

    QPixmap pixmap = QPixmap::fromImage(image);
    imageSize = pixmap.size();

    imageLabel->setPixmap(pixmap);
    imageLabel->resize(imageSize);
    setWindowTitle(QFileInfo(filename).fileName() + tr(" - QImageViewer"));
}

void QImageViewer::openActionTriggered(void)
{
    filename = QFileDialog::getOpenFileName(this, tr("Select image:"),
        "D:\\Documents\\Pictures", tr("Images (*.jpg *.jpeg *.png *.bmp *.gif)"));
    if (filename.isEmpty()) {
        return ;
    }

    /* get file list */
    path = QFileInfo(filename).absolutePath();
    getImgInfoList(imgInfoList);

    /* load image */
    loadImageResource(filename);
}

void QImageViewer::closeActionTriggered(void)
{
    initImageResource();
}

void QImageViewer::lastActionTriggered(void)
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

void QImageViewer::nextActionTriggered(void)
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

void QImageViewer::toLeftActionTriggered(void)
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

void QImageViewer::toRightActionTriggered(void)
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

void QImageViewer::toEnlargeActionTriggered(void)
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

void QImageViewer::toLessenActionTriggered(void)
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

void QImageViewer::deleteActionTriggered(void)
{
    if (filename.isEmpty()) {
        QMessageBox::information(this,
                                 tr("Error"),
                                 tr("Open a image, please!"));
        return ;
    }

    qDebug() << "remove: " << filename;

    if (QFile::remove(filename)) {
        qDebug() << "remove success: " << filename;
    } else {
        qDebug() << "remove failed: " << filename;
    }

    imageLabel->clear();
    imageLabel->resize(QSize(200, 100));
    setWindowTitle(tr("QImageViewer"));
}

void QImageViewer::getImgInfoList(QFileInfoList &imgInfoList)
{
    imgInfoList.clear();

    QDir dir = QFileInfo(filename).absolutePath();
    QFileInfoList infoList = dir.entryInfoList(QDir::Files);
    //qDebug() << "GET:" << infoList.count() << dir;

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
            //qDebug() << "curImage index:" << index;
        }
    }
}

void QImageViewer::setQImageViewerWidget(void)
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

void QImageViewer::setWindowComponet(void)
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

    QAction *aboutQt = new QAction(tr("AboutQt"), this);
    aboutQt->setStatusTip(tr("About Qt"));
    aboutQt->setIcon(QIcon(":/images/Qt.png"));

#if 0
    QAction *imageListAction = new QAction(tr("Null"), this);
    QMenu *imageListMenu = new QMenu(tr("Image Lists"));
    imageListMenu->setStatusTip(tr("Image Lists."));
    imageListMenu->setIcon(QIcon(":/images/select.png"));
    imageListMenu->addAction(imageListAction);
#endif

    deleteAction = new QAction(tr("Delete"), this);
    deleteAction->setStatusTip(tr("Delete a image"));
    deleteAction->setIcon(QIcon(":/images/clear.png"));
    deleteAction->setShortcut(QKeySequence::Delete);

    QMenu *fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(closeAction);
    fileMenu->addSeparator();
    //fileMenu->addMenu(imageListMenu);
    fileMenu->addAction(deleteAction);

    QMenu *operationMenu = menuBar->addMenu(tr("Operate"));
    operationMenu->addAction(lastAction);
    operationMenu->addAction(nextAction);
    operationMenu->addSeparator();
    operationMenu->addAction(toLeftAction);
    operationMenu->addAction(toRightAction);
    operationMenu->addSeparator();
    operationMenu->addAction(toEnlargeAction);
    operationMenu->addAction(toLessenAction);

    QMenu *aboutMenu = menuBar->addMenu(tr("About"));
    aboutMenu->addAction(aboutQt);

    toolBar->addAction(openAction);
    toolBar->addAction(closeAction);
    toolBar->addAction(lastAction);
    toolBar->addAction(nextAction);
    toolBar->addAction(toLeftAction);
    toolBar->addAction(toRightAction);
    toolBar->addAction(toEnlargeAction);
    toolBar->addAction(toLessenAction);
    toolBar->addAction(deleteAction);

    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openActionTriggered()));
    connect(closeAction, SIGNAL(triggered(bool)), this, SLOT(closeActionTriggered()));
    connect(lastAction, SIGNAL(triggered(bool)), this, SLOT(lastActionTriggered()));
    connect(nextAction, SIGNAL(triggered(bool)), this, SLOT(nextActionTriggered()));
    connect(toLeftAction, SIGNAL(triggered(bool)), this, SLOT(toLeftActionTriggered()));
    connect(toRightAction, SIGNAL(triggered(bool)), this, SLOT(toRightActionTriggered()));
    connect(toEnlargeAction, SIGNAL(triggered(bool)), this, SLOT(toEnlargeActionTriggered()));
    connect(toLessenAction, SIGNAL(triggered(bool)), this, SLOT(toLessenActionTriggered()));
    connect(deleteAction, SIGNAL(triggered(bool)), this, SLOT(deleteActionTriggered()));
}

void QImageViewer::initUiComponent(void)
{
    /* set menu and toolbar */
    setWindowComponet();

    /* image show widget */
    setQImageViewerWidget();
}

void QImageViewer::initMainWindow(void)
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

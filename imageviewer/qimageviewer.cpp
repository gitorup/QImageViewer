#include "qimageviewer.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

QImageViewer::QImageViewer(QWidget *parent) : QWidget(parent)
{

}

QImageViewer::QImageViewer(QWidget *parent,
                           QString &caption,
                           QString &dir,
                           QString &filer)
{
    initImageResource();
    loadImageResource(parent, caption, dir, filer);
}

QImageViewer::~QImageViewer(void)
{

}

int QImageViewer::openImageFile(QWidget *parent,
                                QString &caption,
                                QString &dir,
                                QString &filer)
{
    initImageResource();
    return loadImageResource(parent, caption, dir, filer);
}

int QImageViewer::closeImageFile(void)
{
    initImageResource();
    return 0;
}

void QImageViewer::initImageResource(void)
{
    index = -1;
    angle = 0;
    size = QSize(0, 0);

    filename.clear();
    path.clear();
}

int QImageViewer::loadImageResource(void)
{
    filename = QFileDialog::getOpenFileName(this, tr("Select image:"),
        "D:\\Documents\\Pictures", tr("Images (*.jpg *.jpeg *.png *.bmp *.gif)"));
    if (filename.isEmpty()) {
        return -1;
    }

    fileInfo = QFileInfo(filename);
    path = QFileInfo(filename).absolutePath();
    dir = QFileInfo(filename).absoluteDir();

    /* get file list */
    getFileInfoList();

    if (!image.load(filename)) {
        QMessageBox::information(this,
                                 tr("Error"),
                                 tr("Open file error"));
        return -1;
    }

    /* upgrade pixmap */
    pixmap = QPixmap::fromImage(image);
    size = pixmap.size();

    return 0;
}

int QImageViewer::loadImageResource(QWidget *parent,
                                    QString &caption,
                                    QString &directory,
                                    QString &filer)
{
    filename = QFileDialog::getOpenFileName(parent,caption,directory,filer);
    if (filename.isEmpty()) {
        return -1;
    }

    fileInfo = QFileInfo(filename);
    path = QFileInfo(filename).absolutePath();
    dir = QFileInfo(filename).absoluteDir();

    /* get file list */
    getFileInfoList();

    if (!image.load(filename)) {
        QMessageBox::information(parent,
                                 tr("Error"),
                                 tr("Open file error"));
        return -1;
    }

    /* upgrade pixmap */
    pixmap = QPixmap::fromImage(image);
    size = pixmap.size();

    return 0;
}

void QImageViewer::getFileInfoList(void)
{
    QFileInfo info;
    QFileInfoList infoList = dir.entryInfoList(QDir::Files);
    qDebug() << "GET:" << infoList.count() << dir;

    /* clear list */
    fileInfoList.clear();

    for (int i = 0; i < infoList.count(); i++) {
        info = infoList.at(i);
        QString suffix = info.suffix();

        if (suffix == "jpg" || suffix == "bmp" || suffix == "png"
            || suffix == "gif" || suffix == "jpeg") {
            fileInfoList.append(info);
        }
    }

    for (int j = 0; j < fileInfoList.count(); j++) {
        info = fileInfoList.at(j);
        if (info.fileName() == fileInfo.fileName()) {
            index = j;
            qDebug() << "Current fileInfo index: " << index;
        }
    }
}

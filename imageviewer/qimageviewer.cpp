#include "qimageviewer.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

QImageViewer::QImageViewer(QWidget *parent) : QWidget(parent)
{
    this->parent = parent;
}

QImageViewer::QImageViewer(QWidget *parent,
                           QString &caption,
                           QString &dir,
                           QString &filer)
{
    this->parent = parent;
    initImageResource();
    loadImageResource(caption, dir, filer);
}

QImageViewer::~QImageViewer(void)
{
    this->parent = NULL;
}

int QImageViewer::openImageFile(QString &caption,
                                QString &dir,
                                QString &filer)
{
    initImageResource();
    return loadImageResource(caption, dir, filer);
}

int QImageViewer::closeImageFile(void)
{
    initImageResource();
    return 0;
}

int QImageViewer::delImageFile(void)
{
    if (filename.isEmpty()) {
        QMessageBox::information(parent,
                                 tr("Error"),
                                 tr("Open a image, please!"));
        return -1;
    }

    QMessageBox message(QMessageBox::Warning,
                        tr("Warning"),
                        tr("Do you want to delete this image?"),
                        QMessageBox::Yes|QMessageBox::No,
                        NULL);
    if (message.exec() == QMessageBox::No) {
        return 0;
    }

    if (QFile::remove(filename)) {
        qDebug() << "remove success: " << filename;
    } else {
        qDebug() << "remove failed: " << filename;
        return -1;
    }

    /* delete from list */
    fileInfoList.removeAt(index);

    return 0;
}

int QImageViewer::last(void)
{

}

int QImageViewer::next(void)
{

}

int QImageViewer::zoomIn(void)
{

}

int QImageViewer::zoomOut(void)
{

}

int QImageViewer::spinToRight(void)
{

}

int QImageViewer::spinToLeft(void)
{

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

    /* get file list */
    getFileInfoList();

    index = getFileCurIndex();
    fileInfo = QFileInfo(filename);
    path = QFileInfo(filename).absolutePath();
    dir = QFileInfo(filename).absoluteDir();

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

int QImageViewer::loadImageResource(QString &caption,
                                    QString &directory,
                                    QString &filer)
{
    filename = QFileDialog::getOpenFileName(parent,caption,directory,filer);
    if (filename.isEmpty()) {
        return -1;
    }

    /* get file list */
    getFileInfoList();

    index = getFileCurIndex();
    fileInfo = QFileInfo(filename);
    path = QFileInfo(filename).absolutePath();
    dir = QFileInfo(filename).absoluteDir();

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

int QImageViewer::getFileInfoList(void)
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

    return 0;
}

int QImageViewer::getFileCurIndex(void)
{
    QFileInfo info;

    if (fileInfoList.count() <= 0) {
        qDebug() << "fileInfoList is NULL!";
        return -1;
    }

    for (int j = 0; j < fileInfoList.count(); j++) {
        info = fileInfoList.at(j);
        if (info.fileName() == fileInfo.fileName()) {
            break;
        }
    }

    if (j >= fileInfoList.count()) {
        qDebug() << "Not find current file!";
        return -1;
    }

    index = j;
    qDebug() << "Current fileInfo index: " << index;

    return index;
}

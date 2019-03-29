#include "qimageviewer.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QImageReader>

QImageViewer::QImageViewer(QWidget *parent) : QWidget(parent)
{
    this->parent = parent;
    initImageResource();
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

int QImageViewer::openImageFile(const QString &caption,
                                const QString &dir,
                                const QString &filer)
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
        return -1;
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
    if (index < 0) {
        return -1;
    }

    while (1) {
        index = index - 1;
        int count = fileInfoList.count();
        if (index < 0) {
            QMessageBox::information(this, tr("Tip"), tr("This is the first image."));
            index = count - 1;
        }

        filename.clear();
        filename.append(path);
        filename += "/";
        filename += fileInfoList.at(index).fileName();

        if (!QFile(filename).exists()) {
            fileInfoList.removeAt(index);
            continue;
        } else {
            break;
        }
    }

    angle = 0;
    size = QSize(0, 0);

    /* load file info */
    return upgradeFileInfo(filename, angle, 10);
}

int QImageViewer::next(void)
{
    if (index < 0) {
        return -1;
    }

    while (1) {
        index = index + 1;
        int count = fileInfoList.count();
        if (index == count) {
            QMessageBox::information(this, tr("Tip"), tr("This is the last image."));
            index = 0;
        }

        filename.clear();
        filename.append(path);
        filename += "/";
        filename += fileInfoList.at(index).fileName();

        if (!QFile(filename).exists()) {
            fileInfoList.removeAt(index);
            continue;
        } else {
            break;
        }
    }

    angle = 0;
    size = QSize(0, 0);

    /* load file info */
    return upgradeFileInfo(filename, angle, 10);
}

int QImageViewer::zoomIn(void)
{
    return upgradeFileInfo(filename, angle, 12);
}

int QImageViewer::zoomOut(void)
{
    return upgradeFileInfo(filename, angle, 8);
}

int QImageViewer::spinToRight(void)
{
    angle += 1;
    angle = angle % 4;

    /* load file info */
    return upgradeFileInfo(filename, angle, 10);
}

int QImageViewer::spinToLeft(void)
{
    angle += 3;
    angle = angle % 4;

    /* load file info */
    return upgradeFileInfo(filename, angle, 10);
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
    //qDebug() << QImageReader::supportedImageFormats();
    filename = QFileDialog::getOpenFileName(this, tr("Select image:"),
        "D:\\Documents\\Pictures", tr("Images (*.jpg *.jpeg *.png *.bmp *.gif)"));
    if (filename.isEmpty()) {
        return -1;
    }

    /* get file list */
    getFileInfoList();

    /* load file info */
    upgradeFileInfo(filename, angle, 10);

    return 0;
}

int QImageViewer::loadImageResource(const QString &caption,
                                    const QString &directory,
                                    const QString &filer)
{
    filename = QFileDialog::getOpenFileName(this,caption,directory,filer);
    if (filename.isEmpty()) {
        return -1;
    }

    /* get file list */
    getFileInfoList();

    /* load file info */
    upgradeFileInfo(filename, angle, 10);

    return 0;
}

int QImageViewer::upgradeFileInfo(QString &filename,int angle,int sizeScale)
{
    QImage imgRotate;
    QMatrix matrix;
    QImage imgScaled;

    if (filename.isEmpty()) {
        return -1;
    }

    fileInfo = QFileInfo(filename);
    if (!image.load(filename)) {
        return -1;
    }

    if (size == QSize(0, 0)) {
        size = image.size();
    }

    /* modify size */
    imgScaled = image.scaled(size.width() * sizeScale / 10,
                             size.height() * sizeScale / 10,
                             Qt::KeepAspectRatio);
    if (sizeScale != 10) {
        size = imgScaled.size();
    }

    /* modify angle */
    matrix.rotate(angle * 90);
    imgRotate = imgScaled.transformed(matrix);

    pixmap = QPixmap::fromImage(imgRotate);
    /* upgrade index */
    index = getFileCurIndex();

    return 0;
}

int QImageViewer::getFileInfoList(void)
{
    QFileInfo info;
    QFileInfoList infoList;

    path = QFileInfo(filename).absolutePath();
    dir = QFileInfo(filename).absoluteDir();

    /* clear list */
    fileInfoList.clear();

    infoList = dir.entryInfoList(QDir::Files);
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
    int j;

    if (fileInfoList.count() <= 0) {
        qDebug() << "fileInfoList is NULL!";
        return -1;
    }

    for (j = 0; j < fileInfoList.count(); j++) {
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
    //qDebug() << "Current fileInfo index: " << index;

    return index;
}

#ifndef QIMAGEVIEWER_H
#define QIMAGEVIEWER_H

#include <QObject>
#include <QImage>
#include <QPixmap>
#include <QDir>
#include <QSize>
#include <QFileInfo>
#include <QFileInfoList>

class QImageViewer : public QObject
{
    Q_OBJECT
public:
    explicit QImageViewer(QObject *parent = 0);
    ~QImageViewer();

    int imageIndex;
    int imageAngle;
    QSize imageSize;
    QString imageName;
    QString imagePath;
    QDir imageDir;
    QFileInfo imageInfo;
    QFileInfoList imgInfoList;

private:

public slots:
};

#endif // QIMAGEVIEWER_H

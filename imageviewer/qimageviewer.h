#ifndef QIMAGEVIEWER_H
#define QIMAGEVIEWER_H

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QDir>
#include <QSize>
#include <QFileInfo>
#include <QFileInfoList>

class QImageViewer : public QWidget
{
    Q_OBJECT
public:
    explicit QImageViewer(QWidget *parent = 0);
    explicit QImageViewer(QWidget *parent,QString &caption,QString &dir,QString &filer);
    ~QImageViewer();

    QWidget *parent;

    int index;
    int angle;
    QSize size;
    QString filename;
    QString path;
    QDir dir;
    QFileInfo fileInfo;
    QFileInfoList fileInfoList;

    QImage image;
    QPixmap pixmap;

    /* open a file */
    int openImageFile(const QString &caption,const QString &dir,const QString &filer);

    /* close file */
    int closeImageFile(void);

    /* delete file */
    int delImageFile(void);

    /* file skipping */
    int last(void);
    int next(void);

    /* change image */
    int zoomIn(void);
    int zoomOut(void);
    int spinToRight(void);
    int spinToLeft(void);

private:
    /* init param */
    void initImageResource(void);

    /* open a image */
    int loadImageResource(void);
    int loadImageResource(const QString &caption,const QString &dir,const QString &filer);

    /* get file info list from current path */
    int getFileInfoList(void);
    int getFileCurIndex(void);
    int upgradeFileInfo(QString &filename,int angle,int sizeScale);

public slots:
};

#endif // QIMAGEVIEWER_H

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
    explicit QImageViewer(QWidget *parent,
                          QString &caption,
                          QString &dir,
                          QString &filer);
    ~QImageViewer();

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
    int openImageFile(QWidget *parent,
                      QString &caption,
                      QString &dir,
                      QString &filer);

    /* close file */
    int closeImageFile(void);



private:
    /* init param */
    void initImageResource(void);

    /* open a image */
    int loadImageResource(void);
    int loadImageResource(QWidget *parent,
                          QString &caption,
                          QString &dir,
                          QString &filer);

    /* get file info list from current path */
    void getFileInfoList(void);

public slots:
};

#endif // QIMAGEVIEWER_H

#ifndef QIMAGEVIEWER_H
#define QIMAGEVIEWER_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QFileInfoList>

#include "qabout.h"

class QImageViewer : public QMainWindow
{
    Q_OBJECT
public:
    explicit QImageViewer(QWidget *parent = 0);

private:
    QMenuBar *menuBar;
    QToolBar *toolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;
    QLabel *imageLabel;
    QAbout aboutWidget;

    int index;
    int imageAngle;
    QSize imageSize;
    QString filename;
    QString path;
    QFileInfoList imgInfoList;

    void initMainWindow(void);
    void initUiComponent(void);
    void setQImageViewerWidget(void);
    void setWindowComponet(void);
    void getImgInfoList(QFileInfoList &imgInfoList);
    void initImageResource(void);
    void loadImageResource(QString &filename);

    QAction *openAction;
    QAction *closeAction;
    QAction *lastAction;
    QAction *nextAction;
    QAction *toLeftAction;
    QAction *toRightAction;
    QAction *toEnlargeAction;
    QAction *toLessenAction;
    QAction *deleteAction;

public slots:
    void openActionTriggered(void);
    void closeActionTriggered(void);
    void lastActionTriggered(void);
    void nextActionTriggered(void);
    void toLeftActionTriggered(void);
    void toRightActionTriggered(void);
    void toEnlargeActionTriggered(void);
    void toLessenActionTriggered(void);
    void deleteActionTriggered(void);
    void aboutTriggered(void);
    void aboutQtTriggered(void);
};

#endif // QIMAGEVIEWER_H

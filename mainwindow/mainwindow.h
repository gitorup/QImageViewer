#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QFileInfoList>

#include "qabout.h"
#include "qimageviewer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

private:
    QMenuBar *menuBar;
    QToolBar *toolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;
    QLabel *imageLabel;
    QAbout aboutWidget;

    /* new class */
    QImageViewer *imageViewer;

    void initMainWindow(void);
    void initUiComponent(void);
    void setQImageViewerWidget(void);
    void setWindowComponet(void);
    void initImageResource(void);
    void loadImageResource(void);

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

#endif // MAINWINDOW_H

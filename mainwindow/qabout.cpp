#include "qabout.h"

#include <QFrame>
#include <QFont>
#include <QPalette>
#include <QDebug>

#define SAFE_FREE(p) {if(p != NULL) {delete p; p = NULL;}}

QAbout::QAbout(QWidget *parent) : QWidget(parent)
{
    /* init ui */
    initUiComponent();
}

QAbout::~QAbout()
{
    SAFE_FREE(titleLabel);
    SAFE_FREE(authorLabel);
    SAFE_FREE(infoLabel);
    SAFE_FREE(infoTextEdit);
    SAFE_FREE(exitBtn);
}

void QAbout::exitBtnClicked(void)
{
    this->close();
}

void QAbout::initUiComponent(void)
{
    int label_w = 300, label_h = 20;
    int text_w = 300, text_h = 120;
    int btn_w = 80, btn_h = 30;
    int btn_x = QABOUT_WIDGET_WIDTH - btn_w;
    int btn_y = QABOUT_WIDGET_HEIGHT - btn_h;

    titleLabel = new QLabel(this);
    titleLabel->setText(tr("QImageViewer for Windows(Version v0.2.1)"));
    titleLabel->setGeometry(20, 10, label_w, label_h);

    QFont titleFont("Microsoft YaHei", 10, QFont::Bold);
    titleLabel->setFont(titleFont);

    authorLabel = new QLabel(this);
    authorLabel->setText(tr("Author: gitorup"));
    authorLabel->setGeometry(100, 30, label_w, label_h);

    infoLabel = new QLabel(this);
    infoLabel->setOpenExternalLinks(true);
    infoLabel->setText(tr("<a href=\"https://github.com/gitorup/QImageViewer\">"
                          "[https://github.com/gitorup/QImageViewer]"));
    infoLabel->setGeometry(40, 50, label_w, label_h);

    QString info;
    info.append("                                     Statement\n");
    info.append("QImageViewer is a free and open source project. ");
    info.append("You can according to the published by the free software "
                "foundation GNU free distribution and/or modify it under the GPL; "
                "Using version 3 of the agreement, or any higher versions (according to your choice). "
                "Published the purpose is to hope it can useful to you, but we don't have any guarantee; "
                "Use it for any purpose of any direct or indirect consequences does not undertake any responsibility. "
                "Please see details of the GNU GPL.\n"
                "You should be at the same time of receiving the program received a copy of the GNU GPL. "
                "If not, see (http://www.gnu.org/licenses).");


    infoTextEdit = new QTextEdit(this);
    infoTextEdit->setText(info);
    infoTextEdit->setReadOnly(1);
    infoTextEdit->setGeometry(15, 80, text_w, text_h);

    QPalette palette;
    palette.setColor(QPalette::Text, Qt::red);
    infoTextEdit->setPalette(palette);
    QFont infoFont("Microsoft YaHei", 8, QFont::Cursive);
    infoTextEdit->setFont(infoFont);

    exitBtn = new QPushButton(this);
    exitBtn->setText(tr("OK"));
    exitBtn->setGeometry(btn_x - 10, btn_y - 5, btn_w, btn_h);
    connect(exitBtn, SIGNAL(clicked(bool)), this, SLOT(exitBtnClicked()));
}

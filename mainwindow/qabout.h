#ifndef QABOUT_H
#define QABOUT_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>

#define QABOUT_WIDGET_WIDTH     320
#define QABOUT_WIDGET_HEIGHT    240

class QAbout : public QWidget
{
    Q_OBJECT
public:
    explicit QAbout(QWidget *parent = 0);
    ~QAbout();

private:
    QPushButton *exitBtn;
    QLabel *infoLabel;
    QLabel *titleLabel;
    QLabel *authorLabel;
    QTextEdit *infoTextEdit;
    void initUiComponent(void);

public slots:
    void exitBtnClicked(void);
};

#endif // QABOUT_H

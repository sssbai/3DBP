#pragma once
#include <QWidget>
#include <QLabel>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <QDoubleSpinBox>
#include "packing.h"
//#include "op_excel.h"

class AddWindow : public QWidget
{
    Q_OBJECT

public:
    AddWindow(QWidget *parent = Q_NULLPTR);
    ~AddWindow();
    QLabel *name;
    QLabel *number;
    QLabel *len;
    QLabel *wid;
    QLabel *high;
    QLineEdit *name1;
    QPushButton *create;
    QPushButton *cancel;
    QSpinBox *box;
    QDoubleSpinBox *boxl;
    QDoubleSpinBox *boxw;
    QDoubleSpinBox *boxh;

public slots:
    void creat();
signals:
    void sendinfo(QString, int, double, double, double);
};

#ifndef LOAD_WINDOW_H
#define LOAD_WINDOW_H
#include <QWidget>
#include <QLabel>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <QDoubleSpinBox>
#include "packing.h"
#include <QCoreApplication>

class Load_Window: public QWidget
{
    Q_OBJECT
public:
    Load_Window(QWidget *parent = Q_NULLPTR);
    ~Load_Window();
private slots:
    void run();
};

#endif // LOAD_WINDOW_H


#pragma once

#include<qpushbutton.h>
#include <QtWidgets/QWidget>
#include <qlabel.h>
#include <qcombobox.h>
#include <qlistview.h>
#include <QListWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QJsonObject>
#include "multiselectcombobox.h"
#include <qtablewidget.h>
#include <QDebug>
#include "addwindow.h"
#include "osg_widget.h"
//#include <QtXlsx>

using namespace std;

class Packing : public QWidget
{
    Q_OBJECT

public:
    Packing(QWidget *parent = Q_NULLPTR);
    ~Packing();
    QPushButton *BUT1;
    QPushButton *BUT2;
    QPushButton *BUT3;
    QPushButton *BUT4;
    QLabel *label1;
    QLabel *label2;
    QLabel *image;
    QComboBox *container;
    QComboBox *boxes;
    MultiSelectComboBox *com;
    QTableWidget *table;
    QString text;
    QStringList comtext;
    QStringList p_names;
    QWidget *centralWidget;
    Osg_Widget *osg_widget;
    int count = 1;
    int num = 0;
    int numy = 0;
    bool flag = 0;


public slots:
    void loadcontainer();
    void loadcom();
//    void on_bt_add_clicked();
    void addpacket();
    void addinfo(QString name2, int num1, double l, double w, double h);
    void exportexcel();
    void empytytable();
//    void showdata();
};

#pragma once
#include <QWidget>
#include<QLabel>
#include<QLineEdit>
#include<QTextEdit>
#include<qpushbutton.h>
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QFileDialog>
#include <QDesktopServices>
#include <vector>
#include <QTextCodec>
#include <QDebug>
#include <string>
#include <iostream>
#include<Windows.h>
//#include "cost_packing.h"
using namespace std;
class DataWindow : public QWidget
{
    Q_OBJECT

public:
    DataWindow(QWidget *parent = Q_NULLPTR);
    ~DataWindow();
    QLabel *ute;
    QLabel *aldy_num;
    QLabel *no_num;
    QLabel *order;

    QLineEdit *ute_data;
    QLineEdit *aldy_num_data;
    QLineEdit *no_num_data;
    QTextEdit *order_data;
    QPushButton *expor;

    void DataGet(vector<string> name, vector<vector<float>> wdh, vector<vector<float>> points, vector<string> colors);

public slots:
    void export2txt();
//    void CostCount();
};

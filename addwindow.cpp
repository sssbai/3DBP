#include "addwindow.h"

AddWindow::AddWindow(QWidget *parent)
    : QWidget(parent)
{
    //设置窗口标题
    setWindowTitle(u8"新增包装尺寸");
    resize(450, 380);

    //货物名称
    name = new QLabel(this);
    name->setFixedSize(130, 40);
    name->move(35, 30);
    name->setText(u8"货物名称");

    //货物数量
    number = new QLabel(this);
    number->setFixedSize(130, 40);
    number->move(35, 90);
    number->setText(u8"货物数量");

    //长度
    len = new QLabel(this);
    len->setFixedSize(130, 40);
    len->move(35, 150);
    len->setText(u8"长度");

    //宽度
    wid = new QLabel(this);
    wid->setFixedSize(130, 40);
    wid->move(35, 210);
    wid->setText(u8"宽度");

    //高度
    high = new QLabel(this);
    high->setFixedSize(130, 40);
    high->move(35, 270);
    high->setText(u8"高度");

    create = new QPushButton(u8"创建", this);
    create->setGeometry(250, 330, 60, 30);
    //设置固定尺寸
    create->setFixedSize(80, 30);

    cancel = new QPushButton(u8"取消", this);
    cancel->setGeometry(340, 330, 60, 30);
    //设置固定尺寸
    cancel->setFixedSize(80, 30);

    name1 = new QLineEdit(this);
    name1->setFixedSize(290, 30);
    name1->move(120, 35);
    name1->placeholderText();

    box = new QSpinBox(this);
    box->setFixedSize(290, 30);
    box->move(120, 95);

    boxl = new QDoubleSpinBox(this);
    boxl->setFixedSize(290, 30);
    boxl->setRange(0,100);
    boxl->setSingleStep(1);
    boxl->move(120, 155);

    boxw = new QDoubleSpinBox(this);
    boxw->setFixedSize(290, 30);
    boxw->setRange(0, 100);
    boxw->setSingleStep(1);
    boxw->move(120, 215);

    boxh = new QDoubleSpinBox(this);
    boxh->setFixedSize(290, 30);
    boxh->setRange(0, 100);
    boxh->setSingleStep(1);
    boxh->move(120, 275);
    connect(create, SIGNAL(clicked()), this, SLOT(creat()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(close()));
}

AddWindow::~AddWindow() {
}

void AddWindow::creat() {
    QString name2 = name1->text();
    int num1 = box->value();
    double l = boxl->value();
    double w = boxw->value();
    double h = boxh->value();
    emit sendinfo(name2, num1, l, w, h);
}

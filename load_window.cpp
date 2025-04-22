#include "load_window.h"


Load_Window::Load_Window(QWidget *parent)
{
    setWindowIcon(QIcon(":/new/resources/images/logo_3d.ico"));
    //设置窗口标题
    setWindowTitle(u8"智慧装箱系统");
    resize(900, 730);
    QLabel* ute;
    QLabel *aldy_num;
    QLabel *no_num;
    QLabel *order;
    QLabel *image;
    QLineEdit *ute_data;
    QLineEdit *aldy_num_data;
    QLineEdit *no_num_data;
    QTextEdit *order_data;
    QPushButton *expor;

    QLabel* Name_Welcome;
    QLabel* Name_Project;
    QLabel* Author_Project;
    QLineEdit* Name_Data_Project;
    QLineEdit* Author_Data_Project;
    QPushButton* Data_Read;
    QPushButton* Project_Start;

//  项目启动
    Name_Welcome = new QLabel(this);
    Name_Welcome->setFixedSize(300, 40);
    Name_Welcome->move(320, 500);
    Name_Welcome->setStyleSheet("font-size:25px;font:bold;}");
    Name_Welcome->setText(u8"欢迎使用智慧装箱系统！");

//  设定项目名称
    Name_Project = new QLabel(this);
    Name_Project->setFixedSize(180, 40);
    Name_Project->move(180, 550);
    Name_Project->setStyleSheet("QLabel{border:3px solid rgb(180, 180, 180);border-radius:5px;font-size:18px;font:bold;}");
    Name_Project->setText(u8"智慧装箱方案名称:");
    Name_Data_Project = new QLineEdit(this);
    Name_Data_Project->setFixedSize(320, 35);
    Name_Data_Project->move(380, 552);
    Name_Data_Project->placeholderText();
//    设置为只读模式
//    Name_Data_Project->setReadOnly(true);

//  设定项目名称
    Author_Project = new QLabel(this);
    Author_Project->setFixedSize(180, 40);
    Author_Project->move(180, 600);
//    Author_Project->setAlignment(Qt::AlignVCenter);
    Author_Project->setStyleSheet("QLabel{border:3px solid rgb(180, 180, 180);border-radius:5px;font-size:18px;font:bold;}");
    Author_Project->setText(u8"   项目开发者:");
    Author_Data_Project = new QLineEdit(this);
    Author_Data_Project->setFixedSize(320, 35);
    Author_Data_Project->move(380, 602);
    Author_Data_Project->placeholderText();

    Data_Read = new QPushButton(this);
    Data_Read->setText(u8"读入外部项目");
    Data_Read->setStyleSheet("font-size:16px;font:bold;}");
    Data_Read->setGeometry(180, 650, 200, 30);
    //设置固定尺寸
    Data_Read->setFixedSize(220, 40);

    Project_Start = new QPushButton(this);
    Project_Start->setText(u8"开始装箱");
    Project_Start->setStyleSheet("font-size:16px;font:bold;}");
    Project_Start->setGeometry(480, 650, 200, 30);
    //设置固定尺寸
    Project_Start->setFixedSize(220, 40);

    image = new QLabel(this);
    image->move(10, 10);
    image->setFixedSize(880, 480);
    QPixmap pix(":/logo/resources/images/logo-modified.png");
    qDebug()<<endl;
    pix.scaled(QSize(200, 260), Qt::KeepAspectRatio);
    image->setPixmap(pix);
    image->setScaledContents(true);

    connect(Project_Start, SIGNAL(clicked()), this, SLOT(run()));
    connect(Data_Read, SIGNAL(clicked()), this, SLOT(run()));
}

Load_Window::~Load_Window()
{}
void Load_Window::run(){
    Packing *w = new Packing;
    w->show();
    close();
}

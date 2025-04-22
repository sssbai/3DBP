#include "packing.h"
#include <osgQOpenGL/osgQOpenGLWidget>
#include <QtWidgets/QMainWindow>
Packing::Packing(QWidget *parent)
    : QWidget(parent)
{
    //设置窗口标题
    setWindowTitle(u8"包装装箱方案");
//    设置窗口尺寸
    resize(800, 935);
    //QFont font("Microsoft YaHei", 11);
    //this->setFont(font);

    //集装箱尺寸
    label1 = new QLabel(this);
    label1->setFixedSize(130, 40);
    label1->move(35, 495);
    label1->setText(u8"集装箱尺寸");

    //包装尺寸
    label2 = new QLabel(this);
    label2->setFixedSize(130, 40);
    label2->move(35, 545);
    label2->setText(u8"包装尺寸");

    BUT1 = new QPushButton(u8"计算", this);
    BUT1->setGeometry(650, 890, 60, 30);
    //设置固定尺寸
    BUT1->setFixedSize(120, 30);

    BUT2 = new QPushButton(u8"写入", this);
    BUT2->setGeometry(650, 550, 60, 30);
    //设置固定尺寸
    BUT2->setFixedSize(120, 30);

    BUT3 = new QPushButton(u8"新建包装尺寸", this);
    BUT3->setGeometry(510, 550, 60, 30);
    //设置固定尺寸
    BUT3->setFixedSize(120, 30);

    BUT4 = new QPushButton(u8"清空", this);
    BUT4->setGeometry(500, 890, 60, 30);
    //设置固定尺寸
    BUT4->setFixedSize(120, 30);

    container = new QComboBox(this) ;
    setStyleSheet("QComboBox { min-height: 30px; min-width: 40px; }"
        "QComboBox QAbstractItemView::item { min-height: 40px; min-width: 60px; }");
    QStringList strList;
    strList << u8"请选择..."<< u8"平板车厢(L:245×W:163×H:136)" << u8"厢车车厢(L:260×W:150×H:156)" << u8"双排车厢(L:280×W:165×H:137)" << u8"高栏车厢(L:415×W:235×H:185)";
    container->addItems(strList);
    container->move(130, 500);
    //container->setEditable(true);
    container->setFixedSize(350, 30);
    container->setView(new QListView());

    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    osg_widget = new Osg_Widget(centralWidget);
    osg_widget->setObjectName(QString::fromUtf8("osg_widget"));
    osg_widget->setGeometry(QRect(25, 25, 750, 450));
//    image = new QLabel(this);
//    image->move(30, 30);
//    image->setFixedSize(750, 450);
//    QPixmap pix(":/packing/Resources/img.png");
//    pix.scaled(QSize(180, 240), Qt::KeepAspectRatio);
//    image->setPixmap(pix);
//    image->setScaledContents(true);

    com = new MultiSelectComboBox(this);
    com->move(130, 550);
    com->setFixedSize(350, 30);
    QStringList strList2;
    strList2 << u8"邮政纸箱1号(L:53×W:29×H:37)" << u8"邮政纸箱2号(L:53×W:23×H:29)" << u8"邮政纸箱3号(L:43×W:21×H:27)" << u8"邮政纸箱4号(L:35×W:19×H:23)" << u8"邮政纸箱5号(L:29×W:17×H:19)" << u8"顺丰纸箱2号(L:25×W:20×H:18)" << u8"顺丰纸箱3号(L:30×W:25×H:20)" << u8"顺丰纸箱4号(L:36×W:30×H:25)"<< u8"顺丰纸箱5号(L:53×W:32×H:23)"<< u8"顺丰纸箱6号(L:70×W:40×H:32)";
    com->addItems(strList2);

    table = new QTableWidget(10,5,this);
    table->setFixedSize(750, 280);
    table->move(30, 600);
    p_names = QStringList() << u8"货物名称" << u8"货物数量" << u8"关键尺寸Lenth" << u8"关键尺寸Wideth" << u8"关键尺寸High" ;
    table->setHorizontalHeaderLabels(p_names);
    table->setStyleSheet("QTableWidget::item:selected { background-color: rgb(155,200,33)}");
    for (int i = 0; i < 5; i++) {
        table->setColumnWidth(i, 140);
    }
    connect(BUT2, SIGNAL(clicked()),this,SLOT(loadcontainer()));
    connect(BUT2, SIGNAL(clicked()), this, SLOT(loadcom()));
    connect(BUT3, SIGNAL(clicked()), this, SLOT(addpacket()));
    connect(BUT1, SIGNAL(clicked()), this, SLOT(exportexcel()));
    connect(BUT4, SIGNAL(clicked()), this, SLOT(empytytable()));
}
Packing::~Packing() {
}
//void Packing::on_bt_add_clicked()
//{
//    int iRow = this->table->rowCount();
//    this->table->setRowCount(iRow + 1);//总行数增加1
//    QTableWidgetItem *item = new QTableWidgetItem();
//    this->table->setItem(iRow, 0, item); //添加到界面
//}
QString str2qstr(const string str)
{
    QString qstring;
    qstring = QString(QString::fromLocal8Bit(str.c_str()));
    return qstring;
}

string qstr2str(const QString qstr)
{
    string cstring = std::string((const char *)qstr.toLocal8Bit().constData());
    return cstring;
}

void Packing::loadcontainer() {
    text = container->currentText();
    int num = container->currentIndex();
    //qDebug() << num;
    //qDebug() << text;
    if (num == 0) {
        for (int j = 0; j < 5; ++j) {
            table->setItem(0, j, new QTableWidgetItem(""));
        }
        return;
    }
    else
    {
        //qDebug() << "1111";
        string str = qstr2str(text);
        string name = str.substr(0, str.find("("));
        string len = str.substr(str.find("L:"), str.find("W:")- str.find("L:")-1).erase(0, 2);
        string wid = str.substr(str.find("W:"), str.find("H:") - str.find("W:") - 1).erase(0, 2);
        string high = str.substr(str.find("H:"), str.find(")") - str.find("H:")).erase(0, 2);

        QString name1 = str2qstr(name);
        QString str1 = str2qstr(str);
        QString len1 = str2qstr(len);
        QString wid1 = str2qstr(wid);
        QString high1 = str2qstr(high);
        //qDebug() << high1;
        table->setItem(0, 0, new QTableWidgetItem(name1));
        table->setItem(0, 1, new QTableWidgetItem("1"));
        table->setItem(0, 2, new QTableWidgetItem(len1));
        table->setItem(0, 3, new QTableWidgetItem(wid1));
        table->setItem(0, 4, new QTableWidgetItem(high1));
    }

}

void Packing::loadcom() {
    comtext = com->currentText();
    QString text1 = comtext.join("");
    //qDebug() << text1;
    QStringList list1 = text1.split(";");
    if (list1.size() == 1 && text1 == "") {
        for (int i = 0; i < 5; ++i) {
            for (int j = num+1; j < count+1; ++j) {
                table->setItem(j, i, new QTableWidgetItem(""));
            }
        }
        count = num+1;
    }
    else{
        for (int i = 0; i < 5; ++i) {
            for (int j = num+1; j < count+1 ; ++j) {
                table->setItem(j, i, new QTableWidgetItem(""));
            }
        }
        for (int i = 0; i < list1.size(); ++i)
        {
            QString tmp = list1.at(i);
            //qDebug() << "tmp =" << tmp;
            string str = qstr2str(tmp);
            string name = str.substr(0, str.find("("));
            string len = str.substr(str.find("L"), str.find("W") - str.find("L") - 1).erase(0, 1);
            string wid = str.substr(str.find("W"), str.find("H") - str.find("W") - 1).erase(0, 1);
            string high = str.substr(str.find("H"), str.find(")") - str.find("H")).erase(0, 1);

            QString name1 = str2qstr(name);
            QString str1 = str2qstr(str);
            QString len1 = str2qstr(len);
            QString wid1 = str2qstr(wid);
            QString high1 = str2qstr(high);

            table->setItem(num + i + 1, 0, new QTableWidgetItem(name1));
            table->setItem(num + i + 1, 1, new QTableWidgetItem("1"));
            table->setItem(num + i + 1, 2, new QTableWidgetItem(len1));
            table->setItem(num + i + 1, 3, new QTableWidgetItem(wid1));
            table->setItem(num + i + 1, 4, new QTableWidgetItem(high1));
            numy = i;
            count = num+numy+1;

        }
        }
    }
    //ctrl+k+c/u

void Packing::addpacket() {
    AddWindow * w1 = new AddWindow;
    w1->show();
    connect(w1, SIGNAL(sendinfo(QString, int, double, double, double)), this, SLOT(addinfo(QString, int, double, double, double)));
}

void Packing::addinfo(QString name2,int num1,double l,double w,double h) {
    table->insertRow(num + 1);
    table->setItem(num + 1, 0, new QTableWidgetItem(name2));
    table->setItem(num + 1, 1, new QTableWidgetItem(QString::number(num1)));
    table->setItem(num + 1, 2, new QTableWidgetItem(QString::number(l, 'f', 2)));
    table->setItem(num + 1, 3, new QTableWidgetItem(QString::number(w, 'f', 2)));
    table->setItem(num + 1, 4, new QTableWidgetItem(QString::number(h, 'f', 2)));
    num++;
    count = numy + num + 1;

}
//将QSstring类型转化为Char类型
char* QstringToChar(QString instr) {
    QByteArray ba = instr.toLocal8Bit();
    char* out = ba.data();
    return out;
}
void Packing::exportexcel() {
    vector<string> name_list;
    vector<vector<float>> wdh_list;
    vector<int> num_list;
//    cout<<"count = "<<count<<endl;
    for(int i = 0; i <= count; i++){
        vector<float> wdh_single;
        string name = QstringToChar(table->item(i, 0)->text());
        int num = table->item(i, 1)->text().toInt();
        float l = table->item(i, 2)->text().toFloat();
        float w = table->item(i, 3)->text().toFloat();
        float h = table->item(i, 4)->text().toFloat();
        wdh_single.push_back(w);
        wdh_single.push_back(l);
        wdh_single.push_back(h);
        name_list.push_back(name);
        wdh_list.push_back(wdh_single);
        num_list.push_back(num);
    }
    osg_widget->SetBackgroundBox(name_list[0],
                                 osg::Vec3(table->item(0, 3)->text().toFloat()*0.5,
                                           table->item(0, 2)->text().toFloat()*0.5,
                                           table->item(0, 4)->text().toFloat()*0.5));
//    for(vector<string>::iterator iter = name_list.begin(); iter!=name_list.end(); iter++){
//        cout<<"name_list = "<<*iter<<endl;
//    }
    osg_widget->getData(name_list, wdh_list, num_list);
//    float all_volume=0, used_volume=0;
//    all_volume = wdh_list[0][0]*wdh_list[0][1]*wdh_list[0][2];
//    for(int i = 1; i < count; i++){
//        used_volume += wdh_list[i][0]*wdh_list[i][1]*wdh_list[i][2]*num_list[i];
//    }
//    cout<<"------------------------------------------------"<<endl;
//    cout<<used_volume<<endl;
//    cout<<all_volume<<endl;
//    cout<<"空间利用率为 = "<<used_volume/all_volume*100<<"%"<<endl;
//    cout<<"------------------------------------------------"<<endl;
    osg_widget->run();
    //方法二：
    BUT1->setHidden(true);
    BUT4->setHidden(true);
    resize(800, 900);
}

void Packing::empytytable() {
    table->clear();
    count=1;
}

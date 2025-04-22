#include "datawindow.h"

DataWindow::DataWindow(QWidget *parent)
    : QWidget(parent)
{
    //设置窗口标题
    setWindowTitle(u8"装箱方案数据");
    resize(450, 500);

    //货物名称
    ute = new QLabel(this);
    ute->setFixedSize(130, 40);
    ute->move(35, 30);
    ute->setText(u8"空间利用率");

    //货物数量
    aldy_num = new QLabel(this);
    aldy_num->setFixedSize(130, 40);
    aldy_num->move(35, 90);
    aldy_num->setText(u8"已装入数量");

    //长度
    no_num = new QLabel(this);
    no_num->setFixedSize(130, 40);
    no_num->move(35, 150);
    no_num->setText(u8"未装入数量");

    //宽度
    order = new QLabel(this);
    order->setFixedSize(130, 40);
    order->move(35, 210);
    order->setText(u8"装箱顺序");

    ute_data = new QLineEdit(this);
    ute_data->setFixedSize(290, 30);
    ute_data->move(120, 35);
    ute_data->placeholderText();
    //ute_data->setReadOnly(true);

    aldy_num_data = new QLineEdit(this);
    aldy_num_data->setFixedSize(290, 30);
    aldy_num_data->move(120, 95);
    //aldy_num_data->setReadOnly(true);

    no_num_data = new QLineEdit(this);
    no_num_data->setFixedSize(290, 30);
    no_num_data->move(120, 155);
    //no_num_data->setReadOnly(true);

    order_data = new QTextEdit(this);
//    order_data->se
    order_data->setFixedSize(290, 200);
    order_data->move(120, 215);
    order_data->setReadOnly(true);
//    order_data->append("111111122222222");
    expor = new QPushButton(u8"导出装箱数据", this);
    expor->setGeometry(305, 445, 60, 30);
    //设置固定尺寸
    expor->setFixedSize(130, 30);
//    expor = new QPushButton(u8"导出装箱数据", this);
//    expor->setGeometry(15, 445, 60, 30);
//    //设置固定尺寸
//    expor->setFixedSize(130, 30);

//    QPushButton *data_unload = new QPushButton(this);
//    data_unload->setText(u8"导出未装箱数据");
//    data_unload->setGeometry(160, 445, 60, 30);
//    data_unload->setFixedSize(130, 30);

//    QPushButton *data_count = new QPushButton(this);
//    data_count->setText(u8"计算装箱成本");
//    data_count->setGeometry(305, 445, 60, 30);
//    data_count->setFixedSize(130, 30);
    connect(expor, SIGNAL(clicked()), this, SLOT(export2txt()));
//    connect(data_count, SIGNAL(clicked()),this ,SLOT(CostCount()));

}

DataWindow::~DataWindow() {
}

//inline QString GBK2UTF8(const QString &inStr)
//{
//    QTextCodec *gbk = QTextCodec::codecForName("GBK");
//    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");

//    QString g2u = gbk->toUnicode(gbk->fromUnicode(inStr));			  // gbk  convert utf8
//    return g2u;
//}
char* Gbk2Utf8(const char* src_str)
{
    int len = MultiByteToWideChar(CP_ACP, 0, src_str, -1, nullptr, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_ACP, 0, src_str, -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    char* str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, nullptr, nullptr);
//    string strTemp = str;
//    if (wstr) delete[] wstr;
//    if (str) delete[] str;
    return str;
}
inline QString UTF82GBK(const QString &inStr)
{
    QTextCodec *gbk = QTextCodec::codecForName("GBK");
    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");

    QString utf2gbk = gbk->toUnicode(inStr.toLocal8Bit());
    return utf2gbk;
}

void DataWindow::DataGet(vector<string> name, vector<vector<float>> wdh, vector<vector<float>> points, vector<string> colors){
    QString outline ="";
    for(unsigned int i = 0; i < name.size(); i++){
//        cout<<"箱体名称为："<<name[i]<<endl;
//        qDebug()<<Gbk2Utf8(name[i].data())<<endl;
        outline += "step_"+QString::number(i)+":";
        outline += u8"\n name   = " +  QString::fromUtf8(Gbk2Utf8(name[i].data()))
                +  u8"\n wdh    = "+QString::number(wdh[i][0],'f',1)+","+QString::number(wdh[i][1],'f',1)+","+QString::number(wdh[i][2],'f',1)
                +  u8"\n points = "+QString::number(points[i][0],'f',1)+","+QString::number(points[i][1],'f',1)+","+QString::number(points[i][2],'f',1)
                +  u8"\n colors = "+QString::number(colors[i][0],'f',1)+","+QString::number(colors[i][1],'f',1)+","+QString::number(colors[i][2],'f',1)+"\n";
    }
    order_data->append(outline);
}
void DataWindow::export2txt() {
    QString src_name = QFileDialog::getExistingDirectory(this, "choose src Directory","/");
    QFile file(src_name + "/text.txt");//文件命名
    if (!file.open(QFile::WriteOnly | QFile::Text))     //检测文件是否打开
    {
        QMessageBox::information(this, "Error Message", "Please Select a Text File!");
        return;
    }
    QTextStream out(&file);                 //分行写入文件
    out << QString(u8"空间利用率:")<< ute_data->text() << endl;
    out << QString(u8"已装入数量:") << aldy_num_data->text()<<endl;
    out << QString(u8"未装入数量:") << no_num_data->text()<<endl;
    out << QString(u8"装箱顺序:") << order_data->toPlainText();

    QMessageBox::information(this, tr(u8"提示"), tr(u8"数据导出成功，按ok后自动打开。"));
    QDesktopServices::openUrl(QUrl(src_name + "/text.txt"));


}

//void DataWindow::CostCount()
//{
//    Cost_Packing* cw = new Cost_Packing;
//    cw->show();
//}

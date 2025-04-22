#pragma push_macro("slots")
#undef slots
#include<Python.h>
#pragma pop_macro("slots")
#include<Windows.h>
#include "osg_widget.h"
#include <osg/Node>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/ShapeDrawable>
#include <osgGA/TrackballManipulator>
#include<osg/MatrixTransform>
#include <QDebug>
#include <osg/PolygonMode>
#include <QCoreApplication>

Osg_Widget::Osg_Widget(QWidget *parent)
    :osgQOpenGLWidget(parent)
{

    Box_Shape = osg::Vec3(150, 700, 150);
    name = "names";
    root = new osg::Group;
    mt = osg::Matrix::translate( osg::Vec3(2, 2, 2) ) ;
    connect(this, &Osg_Widget::initialized, this, &Osg_Widget::show);

}

void Osg_Widget::show(){
    pViewer = getOsgViewer();
    pViewer->getCamera()->setClearColor(osg::Vec4(1, 1, 1, 0));
//    定义叶节点
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
//    定义可绘制体
    osg::ref_ptr<osg::ShapeDrawable> sd1 = new osg::ShapeDrawable();
//    定义集装箱箱体
    osg::ref_ptr<osg::Box> car_box = new osg::Box();
//    设置集装箱箱体的空间位置

    car_box->setCenter(osg::Vec3(0,0,0));
//    设定箱体的半尺寸
//    在osg中坐标系为左手坐标系,X方向向右,Y方向向里,Z方向向上
    car_box->setHalfLengths(Box_Shape);
//    向可绘制体中添加箱体
    sd1->setShape(car_box);
//    设置箱体颜色,颜色为半透明颜色
    sd1->setColor(osg::Vec4(1,0,0,0));
//    打开sd节点的透明设置
    osg::StateSet * stateset = sd1->getOrCreateStateSet();
    //开启融合操作
    stateset->setMode(GL_BLEND,osg::StateAttribute::ON);
    //设置渲染模式
    stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    //关闭光照，这样任意面，都可以看到半透明效果。
    stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
//    向geode节点中添加可绘制体的节点
    geode->addDrawable(sd1.get());

    root->addChild(geode.get());
    pViewer->setCameraManipulator(new osgGA::TrackballManipulator);
    pViewer->setSceneData(root.get());
    pViewer->realize();
}
void Osg_Widget::SetBackgroundBox(string name, osg::Vec3 BS){
    Box_Shape=BS;
//pViewer = getOsgViewer();
//    cout<<"x = "<<Box_Shape.x()<<", y = "<<Box_Shape.y()<<", z = "<<Box_Shape.z()<<endl;
    //    定义叶节点
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    //    定义可绘制体
    osg::ref_ptr<osg::ShapeDrawable> sd1 = new osg::ShapeDrawable();
    //    定义集装箱箱体
    osg::ref_ptr<osg::Box> car_box = new osg::Box();
    //    设置集装箱箱体的空间位置
    car_box->setName(name);
    car_box->setCenter(osg::Vec3(0,0,0));
    //    设定箱体的半尺寸
    //    在osg中坐标系为左手坐标系,X方向向右,Y方向向里,Z方向向上
    car_box->setHalfLengths(Box_Shape);
    //    向可绘制体中添加箱体
    sd1->setShape(car_box);
    //    设置箱体颜色,颜色为半透明颜色
    sd1->setColor(osg::Vec4(1,0,0,0.1f));
    //    打开sd节点的透明设置
    osg::StateSet * stateset = sd1->getOrCreateStateSet();
    //开启融合操作
    stateset->setMode(GL_BLEND,osg::StateAttribute::ON);
    //设置渲染模式
    stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    //关闭光照，这样任意面，都可以看到半透明效果。
    stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
    //    向geode节点中添加可绘制体的节点
    geode->addDrawable(sd1.get());

    osg::ref_ptr<osg::ShapeDrawable> sd2 = new osg::ShapeDrawable;
    osg::TessellationHints *hints=new osg::TessellationHints();
    //    表示模型的粗细度。值越大精细度就越大。打个比方，当精细度小时，一个球可能只有几条线组成，很不圆。但是当精细度大时就十分像个球了。
    hints->setDetailRatio(0.5);
    //    绘制一个球型，以(0,0,0)为圆心，以0.08为半径，精细度为hints绘制一个球体
    osg::ref_ptr<osg::Sphere> cone = new osg::Sphere(osg::Vec3(0,0,0),10);
    sd2->setShape(cone);
    sd2->setColor(osg::Vec4(1,0,0,1));
    //    geode->addDrawable(sd2.get());
    //    设置原点
    osg::ref_ptr<osg::MatrixTransform> trans = TansformLocation(sd2);
    geode->addChild(trans);
    root->addChild(geode.get());
}
osg::ref_ptr<osg::MatrixTransform> Osg_Widget::TansformLocation(osg::ref_ptr<osg::ShapeDrawable> sd){
//    目标平移对象
    osg::ref_ptr<osg::MatrixTransform> trans=new osg::MatrixTransform();

    trans->setMatrix(osg::Matrix::translate(Box_Shape*-1));
    trans->addChild(sd.get());
    return trans;
//    root->addChild(trans.get());

}
void Osg_Widget::createBox(string name,osg::Vec3 point_coord, osg::Vec3 wdh_params, osg::Vec4 color)
{
//  pViewer = getOsgViewer();
//  cout<<"name = "<<name<<endl;
//  cout<<"x = "<<point_coord.x()<<", y = "<<point_coord.y()<<", z = "<<point_coord.z()<<endl;
//  cout<<"weight = "<<wdh_params.x()<<", depth = "<<wdh_params.y()<<", height = "<<wdh_params.z()<<endl;
//  cout<<"r = "<<color.r()<<", g = "<<color.g()<<", b = "<<color.b()<<endl;
  osg::ref_ptr<osg::Geode>gnode=new osg::Geode;
  osg::ref_ptr<osg::ShapeDrawable>sd=new osg::ShapeDrawable();
  osg::ref_ptr<osg::Box> box = new osg::Box();
  box->setCenter(point_coord+wdh_params*0.5);
  box->setHalfLengths(wdh_params*0.5);
  sd->setShape(box);
  sd->setColor(color);
  osg::ref_ptr<osg::StateSet>spStateSet = sd->getOrCreateStateSet();
  osg::ref_ptr<osg::PolygonMode> polyMode = new osg::PolygonMode(osg::PolygonMode::BACK, osg::PolygonMode::LINE);
  spStateSet->setAttribute(polyMode);
  osg::ref_ptr<osg::MatrixTransform> trans = TansformLocation(sd);
  gnode->addChild(trans);
  root->addChild(gnode.get());
}

void Osg_Widget::getData(vector<string> name_list, vector<vector<float>> wdh_list, vector<int> num_list){
    Box_Name_List = name_list;
    WDH_List = wdh_list;
    Num_List = num_list;
//    for(vector<string>::iterator iter = name_list.begin(); iter!=name_list.end(); iter++){
//        cout<<"name = "<<(*iter)<<endl;
//    }
//    for(int i = 0; i<wdh_list.size(); i++){
//        cout<<"w = "<<wdh_list[i][0]<<",d = "<<wdh_list[i][1]<<",h = "<<wdh_list[i][2]<<endl;
//    }
//    for(int i = 0; i<num_list.size(); i++){
//        cout<<"num = "<<num_list[i]<<endl;
//    }
//    cout<<Box_Name<<" "<<WHD.x()<<" "<<WHD.y()<<" "<<WHD[2]<<" "<<num<<" "<<updown<<endl;
    return ;

}
//把const char *c转 wchar_t * ，作为Py_SetPythonHome()参数匹配
wchar_t *GetWC(const char *c)
{
   const size_t cSize = strlen(c) + 1;
   wchar_t* wc = new wchar_t[cSize];
   mbstowcs(wc, c, cSize);

   return wc;
}
char* GbkToUtf8(const char* src_str)
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
string UTF8ToGBK(const char* strUTF8)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, nullptr, 0);
    wchar_t* wszGBK = new wchar_t[len + 1];
    memset(wszGBK, 0, len * 2 + 2);
    MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, wszGBK, len);
    len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, nullptr, 0, nullptr, nullptr);
    char* szGBK = new char[len + 1];
    memset(szGBK, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, nullptr, nullptr);
    std::string strTemp(szGBK);

    if (wszGBK) delete[] wszGBK;
    if (szGBK) delete[] szGBK;

    return strTemp;
}
int H2D(char p){
    int n;
    if(p>='A'&&p<='F')//十六进制还要判断他是不是在A-F或者a-f之间a=10。。
        n=p-'A'+10;
    else if(p>='a'&&p<='f')
        n=p-'a'+10;
    else n=p-'0';
    return n;
}
void Osg_Widget::run(){
    QString fileName = QCoreApplication::applicationDirPath();
    QByteArray ba = fileName.toLatin1(); // must
    char *ch=ba.data();
    cout<<ch<<endl;
    Py_SetPythonHome(GetWC(ch));
//    Py_SetPythonHome(GetWC("E:/QTprojects/QT_3DBP/release/python38/"));
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");//这一步很重要，修改Python路径
    PyRun_SimpleString("import os");
    PyRun_SimpleString("print(os.listdir())");
    PyRun_SimpleString("print('success')");
    PyRun_SimpleString("print('Hello Python!')\n");
    PyRun_SimpleString("import os,sys");//执行import语句，把当前路径加入路径中，为了找到math_test.py
    PyRun_SimpleString("sys.path.append('./')");
    PyRun_SimpleString("print('path = '+os.getcwd())");//测试打印当前路径
    PyObject * pModule1 = nullptr;
    PyObject * pModule2 = nullptr;
    PyObject * pFunc = nullptr;
    PyObject * pDict = nullptr;
    PyObject * pReturn = nullptr;
//    pModule1 = PyImport_ImportModule("py3dbp");
//    if(pModule1)cout<<"pModule=py3dbp"<<endl;
    pModule2 = PyImport_ImportModule("new_3dbp_run");
    if(pModule2)cout<<"pModule=qt_3dbp"<<endl;
    pFunc = PyObject_GetAttrString(pModule2, "get_out");
    if(pFunc){
        cout<<"pFunc"<<endl;
    }
    else{
        cout<<"pFunc failed"<<endl;
        return;
    }
//    cout<<"C two-dim Array Pass Into The Python List:"<<endl;
//    vector<string> name_list = {"box", "顺丰", "韵达", "百世"};
//    vector<vector<float>>wdh_list = {{50, 60, 70},{5,6,8},{7,4,5}, {2,7,5}};
//    vector<int> num_list = {1, 5, 4, 2};
   PyObject *PyList1  = PyList_New(Box_Name_List.size());//定义该PyList对象为0和PyList_Append有关，相当于定义PyList为[]
   PyObject *PyList2  = PyList_New(WDH_List.size());
   PyObject *PyList3  = PyList_New(Num_List.size());
   PyObject *ArgList = PyTuple_New(3);
   for(int i = 0; i < PyList_Size(PyList1); i++){
//       char * p = const_cast<char *>(Box_Name_List[i].c_str());
//       cout<<p<<endl;
//       cout<<Box_Name_List[i].data()<<endl;
       PyList_SetItem(PyList1,i, Py_BuildValue("s", GbkToUtf8(Box_Name_List[i].c_str())));//给PyList对象的每个元素赋值
}
   for(int i = 0; i < PyList_Size(PyList2); i++){
       PyObject *PyList2_1  = PyList_New(3);
       for(int j = 0; j < 3; j++){
           PyList_SetItem(PyList2_1,j, Py_BuildValue("d", WDH_List[i][j]));
       }
       PyList_SetItem(PyList2,i, PyList2_1);
   }
//   Num_Load, Num_UnLoad;
   Num_UnLoad=0;
   for(int i = 0; i < PyList_Size(PyList3); i++){
       PyList_SetItem(PyList3,i, Py_BuildValue("i", Num_List[i]));//给PyList对象的每个元素赋值
       if( i!=0){
           Num_UnLoad += Num_List[i];
       }
   }
   //    for(int i = 0; i <3; i++){
//        PyObject *PyList1_1  = PyList_New(3);
//        for(int j = 0; j < 3; j++){

//            PyList_SetItem(PyList1_1,j, PyLong_FromLong(CArray[i][j]));
//        }
//        PyList_Append(PyList1,PyList1_1);//PyList_Append可以参考Python中，list的append的用处
//    }
   float All_Volume = WDH_List[0][0]*WDH_List[0][1]*WDH_List[0][2];
   float Used_Volume=0;
   PyTuple_SetItem(ArgList, 0, PyList1);//将PyList1对象放入PyTuple对象中
   PyTuple_SetItem(ArgList, 1, PyList2);//将PyList2对象放入PyTuple对象中
   PyTuple_SetItem(ArgList, 2, PyList3);//将PyList2对象放入PyTuple对象中
   pReturn=PyObject_CallObject(pFunc, ArgList);//调用函数，返回一个list
   if(PyList_Check(pReturn)){ //检查是否为List对象
//       cout<<"yes"<<endl;
       int SizeOfList = PyList_Size(pReturn);//List对象的大小，这里SizeOfList = 2
//       printf("返回的结果result：\n");
       Num_Load = SizeOfList;
       Num_UnLoad -= Num_Load;
       for(int i = 0; i < SizeOfList; i++){
           PyObject *ListItem = PyList_GetItem(pReturn, i);//获取List对象中的每一个元素
           int NumOfItems = PyList_Size(ListItem);//List对象子元素的大小，这里NumOfItems = 3
           string name;
           osg::Vec3 point_coord;
           osg::Vec3 wdh_params;
           osg::Vec4 color;
           PyObject *Item = PyList_GetItem(ListItem, 0);//遍历List对象中子元素中的每个元素
           char* result;
           PyArg_Parse(Item, "s", &result);//i表示转换成int型变量
           string s2 =UTF8ToGBK(result);//python字符串转换完是utf8编码，需再转成gbk
//           cout<<s2.data()<<" ";
           name = s2;

           for(int j = 1; j < 4; j++){
               PyObject *Item = PyList_GetItem(ListItem, j);//遍历List对象中子元素中的每个元素
               char* result;
               PyArg_Parse(Item, "s", &result);//i表示转换成int型变量
               string str =UTF8ToGBK(result);//python字符串转换完是utf8编码，需再转成gbk
//                cout <<"the type = "<< typeid(s2).name() << endl;
//               cout<<"str.data = "<<str.data()<<" "<<endl;
               float a = stof(str.data());
//               cout<<"a = "<<a<<endl;
               point_coord[j-1]=a;
           }
           for(int j = 4; j < 7; j++){
               PyObject *Item = PyList_GetItem(ListItem, j);//遍历List对象中子元素中的每个元素
               char* result;
               PyArg_Parse(Item, "s", &result);//i表示转换成int型变量
               string str =UTF8ToGBK(result);//python字符串转换完是utf8编码，需再转成gbk
//                cout <<"the type = "<< typeid(s2).name() << endl;
//               cout<<"str.data = "<<str.data()<<" "<<endl;
               float a = stof(str.data());
//               cout<<"a = "<<a<<endl;
               wdh_params[j-4]=a;
           }
           PyObject *Item_color = PyList_GetItem(ListItem, 7);//遍历List对象中子元素中的每个元素
           char* result_color;
           PyArg_Parse(Item_color, "s", &result_color);//i表示转换成int型变量
           string str =UTF8ToGBK(result_color);//python字符串转换完是utf8编码，需再转成gbk
//                cout <<"the type = "<< typeid(s2).name() << endl;
           const char* p = str.data();
           float r = (H2D(p[0])*16+H2D(p[1]))*1.0/255;
           float g = (H2D(p[2])*16+H2D(p[3]))*1.0/255;
           float b = (H2D(p[4])*16+H2D(p[5]))*1.0/255;
           color[0]=r;color[1]=g;color[2]=b;color[3]=1;

           Box_Name_Out.push_back(name);
           WDH_Out.push_back({wdh_params[0], wdh_params[1], wdh_params[2]});
           Used_Volume += wdh_params[0]*wdh_params[1]*wdh_params[2];
           Point_Coord_Out.push_back({point_coord[0], point_coord[1], point_coord[2]});
           Color_Out.push_back(result_color);
//           cout<<"-----"<<r<<" "<<g<<" "<<b<<endl;
           createBox(name, point_coord,wdh_params, color);
       }
//       cout<<"已用体积 = "<<Used_Volume<<endl;
       Space_Utilization=Used_Volume/All_Volume*100;
//       cout<<"空间利用率为 = "<<Space_Utilization<<"%"<<endl;
//       cout<<"已装入数量 = "<<Num_Load<<endl;
//       cout<<"未装入数量 = "<<Num_UnLoad<<endl;
        Show_Data_Window();
   }
   else{
//       cout<<"Not a List"<<endl;
   }
   Py_Finalize();//调用Py_Finalize，这个根Py_Initialize相对应的。
}
void Osg_Widget::Show_Data_Window(){
    DataWindow *data = new DataWindow;
    data->show();
    data->ute_data->setText(QString::number(Space_Utilization,'f',2)+" %");
    data->aldy_num_data->setText(to_string(Num_Load).data());
    data->no_num_data->setText(to_string(Num_UnLoad).data());
    data->DataGet(Box_Name_Out, WDH_Out,Point_Coord_Out,Color_Out);
}
osg::Vec3 Osg_Widget::DealData(string Box_Name,  osg::Vec3 WHD, bool updown){
//    cout<<Box_Name<<" "<<WHD.x()<<" "<<WHD.y()<<" "<<WHD.z()<<updown<<endl;
    return osg::Vec3(0,0,0);
}

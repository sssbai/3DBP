
#ifndef OSG_WIDGET_H
#define OSG_WIDGET_H
//#include <cmath>
//#pragma push_macro("slots")
//#undef slots
//#include<Python.h>
//#pragma pop_macro("slots")
#include <QString>
#include <iostream>
#include<osgQOpenGL/osgQOpenGLWidget>
#include <osg/Node>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include "datawindow.h"
using namespace std;
class Osg_Widget:public osgQOpenGLWidget
{
public:
    Osg_Widget(QWidget* parent = nullptr);
    osg::ref_ptr<osg::MatrixTransform> TansformLocation(osg::ref_ptr<osg::ShapeDrawable> sd);
    string name;
    osg::Vec3 Box_Shape;
    osg::Vec3 DealData(string Box_Name,  osg::Vec3 WHD, bool updown=true);
    void getData(vector<string> Box_Name, vector<vector<float>> WDH, vector<int> num);
    void SetBackgroundBox(string name, osg::Vec3 BS);
    void run();
    vector<string> Box_Name_List;
    vector<vector<float>> WDH_List;
    vector<int> Num_List;
    vector<string> Box_Name_Out;
    vector<vector<float>> WDH_Out;
//    name, point_coord,wdh_params, color
    vector<vector<float>> Point_Coord_Out;
    vector<string> Color_Out;
    float Space_Utilization;
    int Num_Load, Num_UnLoad;
    void Show_Data_Window();
private slots:
    void show();
private:

    osg::Matrix mt;
    void createBox(string name,osg::Vec3 point_coord,
                                      osg::Vec3 lwh_params,
                                      osg::Vec4 color);
    osgViewer::Viewer* pViewer;
    osg::ref_ptr<osg::Group> root;
};

#endif // OSG_WIDGET_H

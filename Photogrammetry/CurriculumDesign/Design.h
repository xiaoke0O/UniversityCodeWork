//
// Created by xiaoke on 2020/2/23.
//

#ifndef COEFFICIENT_MATRIX14_DESIGN_H
#define COEFFICIENT_MATRIX14_DESIGN_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <eigen3/Eigen/Geometry>

using namespace std;
using namespace Eigen;

class Design {
public:
    Design();

    ~Design();

    Matrix3d rotate;//旋转矩阵
    MatrixXd _42points;//点位数据
    MatrixXd Finall;//结果矩阵
    const double camera_focal = 0.006;;//mm
    int number_photo=0;//照片数
    int ControlNumber=0;//控制点数
    int ConnectNumber=0;//非控制点数
    int AllMarkPointsNumber=0;
    int AllPhotoPointsNumber=0;
    long long int Finall_cols=0;

    void setControlNumber(int number){ControlNumber=number;};//得到控制点个数
    void setInputPath(const string &path);//输入文件路径
    void setOutPath(const string &path);//输出文件路径

private:
    void InitMember();//成员初始化
    void setMatrix();

};


#endif //COEFFICIENT_MATRIX14_DESIGN_H

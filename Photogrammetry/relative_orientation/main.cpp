#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
/********************
*     读取点文件      *
*********************/
    double left_points[6][2];
    double right_points[6][2];
    ifstream left_pf, right_pf;
    left_pf.open("../left_points.txt");
    right_pf.open("../right_points.txt");
    if (!left_pf.is_open() || !right_pf.is_open()) {
        cout << "Some files failed to open!" << endl;
        return 1;
    }
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 2; j++) {
            left_pf >> left_points[i][j];
            right_pf >> right_points[i][j];
            if (left_pf.eof() && right_pf.eof()) {
                left_pf.close();
                right_pf.close();
                cout << "All files have been read and closed!" << endl;
            }
        }
    //cout<<left_points<<endl;
    //cout<<right_points<<endl;
/*****************
*     初始值      *
******************/
    double focal_length = 24; //mm

    double varphi = 0, omega = 0, kappa = 0;
    double Bx, By = 0, Bz = 0;
    Bx = left_points[0][0] - right_points[0][0];
/*****************
*     大迭代      *
******************/

    //计算像点在像空系的坐标
    double left_space[3][1];
    Mat right_space(3, 1, CV_64F, 0.0);
    double Left_N = 0, Right_N = 0;

    Mat A(6, 5, CV_64F, 0.0);

    Mat L(6, 1, CV_64F, 0.0);

    Mat X(5, 1, CV_64F, 0.0);

    int count = 0;

    while (true) {

        //右片的旋转矩阵
        Mat right_rotate = (Mat_<double>(3, 3) << 1, -kappa, -varphi, kappa, 1, -omega, varphi, omega, 1);

        /***************************** *
       *小循环，计算所有定向点，并计算A和L *
       ****************************** */
        for (int i = 0; i < 6; i++) {
            left_space[0][0] = left_points[i][0];
            left_space[1][0] = left_points[i][1];
            left_space[2][0] = -focal_length;
            right_space = right_rotate * (Mat_<double>(3, 1) << right_points[i][0], right_points[i][1], -focal_length);

            double X2 = right_space.at<double>(0, 0);
            double Y2 = right_space.at<double>(1, 0);
            double Z2 = right_space.at<double>(2, 0);

            Left_N = (Bx * Z2 - Bz * X2) / (left_space[0][0] * Z2 - left_space[2][0] * X2);
            Right_N = (Bx * left_space[2][0] - Bz * left_space[0][0]) / (left_space[0][0] * Z2 - left_space[2][0] * X2);

            A.at<double>(i, 0) = Bx;
            A.at<double>(i, 1) = -Y2 * Bx / Z2;
            A.at<double>(i, 2) = -X2 * Y2 * Right_N / Z2;
            A.at<double>(i, 3) = -(Z2 + (pow(Y2, 2) / Z2)) * Right_N;
            A.at<double>(i, 4) = X2 * Right_N;

            L.at<double>(i, 0) = Left_N * left_space[1][0] - Right_N * Y2 - By;
        }
        X = (A.t() * A).inv() * A.t() * L;

        By += Bx * X.at<double>(0, 0);
        Bz += Bx * X.at<double>(1, 0);
        varphi += X.at<double>(2, 0);
        omega += X.at<double>(3, 0);
        kappa += X.at<double>(4, 0);

        count++;
        if (abs(X.at<double>(2, 0)) < 1E-5 && abs(X.at<double>(3, 0)) < 1E-5 && abs(X.at<double>(4, 0)) < 1E-5) {
            break;
        }

    }

/******************************* *
 *         输出迭代结果           *
 ****************************** */
    cout << "迭代次数：" << count << endl;
    cout << "By= " << By / Bx << endl;
    cout << "Bz= " << Bz / Bx << endl;
    cout << "varphi= " << varphi << endl;
    cout << "omega= " << omega << endl;
    cout << "kappa= " << kappa << endl;
    cout << "Loop over!" << endl;

/******************************* *
 *         求模型点坐标           *
 ****************************** */
    //模型点的坐标
    double model_coor[1][3];
    
    Mat right_rotate = (Mat_<double>(3, 3) << 1, -kappa, -varphi, kappa, 1, -omega, varphi, omega, 1);
    Mat Right_point(3,1,CV_64F,0.0);

    for (int l = 0; l < 6; ++l) {
        left_space[0][0] = left_points[l][0];
        left_space[1][0] = left_points[l][1];
        left_space[2][0] = -focal_length;

        Right_point.at<double >(0,0)=right_points[l][0];
        Right_point.at<double >(1,1)=right_points[l][1];
        Right_point.at<double >(2,1)=-focal_length;
        right_space=right_rotate*Right_point;
        //提出左右像空系坐标，简化N的计算公式
        double X1 = left_space[0][0];
        double Y1 = left_space[1][0];
        double Z1 = left_space[2][0];

        double X2 = right_space.at<double>(0, 0);
        double Y2 = right_space.at<double>(1, 0);
        double Z2 = right_space.at<double>(2, 0);
        //计算左右N
        Left_N=(Bx*Z2-Bz*X2)/(X1*Z2-X2*Z1);
        Right_N=(Bx*Z1-Bz*X1)/(X1*Z2-X2*Z1);
        // 每个点的模型坐标
        model_coor[0][0]=Left_N*X1;
        model_coor[0][1]=0.5*(Left_N*Y1+Right_N*Y2+By);
        model_coor[0][2]=Left_N*Z1;
        printf("第%d个点的模型坐标为(%f,%f,%f)\n",l+1,model_coor[0][0],model_coor[0][1],model_coor[0][2]);
    }

    return 0;
}

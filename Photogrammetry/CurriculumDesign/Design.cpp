//
// Created by xiaoke on 2020/2/23.
//

#include "Design.h"
/*
 * 读CSV文件到Eigen矩阵
 * */
template<typename M>
M load_csv(const string &path) {
    ifstream indata;
    indata.open(path);

    string line;
    vector<double> values;
    int rows = 0;
    while (getline(indata, line)) {
        stringstream lineStream(line);
        string cell;
        while (getline(lineStream, cell, ',')) {
            values.push_back(std::stod(cell));
        }
        ++rows;
    }
    return Eigen::Map<const Eigen::Matrix<typename M::Scalar, M::RowsAtCompileTime, M::ColsAtCompileTime, Eigen::RowMajor>>(
            values.data(),
            rows,
            values.size() /
            rows);
}
//构造函数
Design::Design() {
    //ctor
    cout << "Object is being created" << endl;
}
//****************输入数据*********************//
void Design::setInputPath(const string &path) {
    _42points = load_csv<Eigen::MatrixXd>(path);
    InitMember();
}
/*
 * 输出数据
 * IOfromat规定了Eigen矩阵输出的格式
 * 输出文件在主函数的类对象传入
 * 先执行setMatrix()函数执行Finall矩阵的赋值
 * 再输出Finall矩阵到文件
 */
void Design::setOutPath(const string &path) {
    IOFormat xlsx(5, 0, "\t", "\n");
    ofstream outfile;
    outfile.open(path);
    setMatrix();
    outfile << Finall.format(xlsx);
    if (!outfile) {
        cout << "File  output failed!" << endl;
        exit(-1);
    }
}

/*
 * 类成员初始化，
 * 之所以没放在构造函数使用为要先通过类的对象传入输入文件
 * 初始化旋转矩阵rotate
 * AAA.获取照片数，用于确定A矩阵大小
 *  1.提取读入的点位数据第一列AllPhotoNumber
 *  2.对其进行排序
 *  3.用unique()剔除重复项
 *  4.剔除后的数据个数就是像片数 number_photo
 * AAA.获取标记点数AllMarkPointsNumber(控制点与连接点数之和)
 *  原理同上，提取了点的地面点坐标的X值
 *  得到连接点个数，用于确定B矩阵大小
 * AAA.获取照片上所有点AllPhotoPointsNumber(控制点＋连接点＋转刺点)
 *  数值上等于读入数据的行数
 */
void Design::InitMember() {
    rotate << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;
//*********************像片数***************************//
    Eigen::VectorXd AllPhotoNumber = _42points.col(0);
    vector<double> vec;
    vec.resize(AllPhotoNumber.size());
    Eigen::VectorXd::Map(&vec[0], AllPhotoNumber.size()) = AllPhotoNumber;
    sort(vec.begin(), vec.end());
    auto last = unique(vec.begin(), vec.end());
    vec.erase(last, vec.end());
    number_photo = vec.size();
//*********************总点数***************************//

//TODO:不完美，可能存在不同点同X值的情况
    VectorXd All_Mark = _42points.col(3);
    vector<double> v;
    v.resize(All_Mark.size());
    VectorXd::Map(&v[0], All_Mark.size()) = All_Mark;
    sort(v.begin(), v.end());
    auto lastt = unique(v.begin(), v.end());
    v.erase(lastt, v.end());
    AllMarkPointsNumber = v.size();
    ConnectNumber = AllMarkPointsNumber - ControlNumber;

    AllPhotoPointsNumber = _42points.rows();
    Finall_cols = number_photo * 6 + ConnectNumber * 3 + 1;
    Finall.resize(AllPhotoPointsNumber * 2, Finall_cols);
    Finall.setZero();

}
/*为Finall矩阵赋值
 *
 */
void Design::setMatrix() {
    double ave_Z;
    double x, y;
    double xp, yp;
    double X, Y, Z;
    double Xs, Ys, Zs;
    double phi, omega, kapa;
    double a1 = rotate(0, 0), a2 = rotate(0, 1), a3 = rotate(0, 2);
    double b1 = rotate(1, 0), b2 = rotate(1, 1), b3 = rotate(1, 2);
    double c1 = rotate(2, 0), c2 = rotate(2, 1), c3 = rotate(2, 2);

    int indexA;
    int A_begin_col;
    int B_begin_col = 6 * number_photo;
    int flag;
//遍历读入数据。
    for (int i = 0; i < _42points.rows(); ++i) {
        indexA = _42points(i, 0);
        xp = _42points(i, 1);
        yp = _42points(i, 2);
        X = _42points(i, 3);
        Y = _42points(i, 4);
        Z = _42points(i, 5);
        Xs = _42points(i, 6);
        Ys = _42points(i, 7);
        Zs = _42points(i, 8);
        phi = _42points(i, 9);
        omega = _42points(i, 10);
        kapa = _42points(i, 11);
        flag = _42points(i, 12);
//*******************A矩阵*****************************//
        ave_Z = a3 * (X - Xs) + b3 * (Y - Ys) + c3 * (Z - Zs);
        x = -1.0 * camera_focal * (a1 * (X - Xs) + b1 * (Y - Ys) + c1 * (Z - Zs)) /
            (a3 * (X - Xs) + b3 * (Y - Ys) + c3 * (Z - Zs));
        y = -1.0 * camera_focal * (a2 * (X - Xs) + b2 * (Y - Ys) + c2 * (Z - Zs)) /
            (a3 * (X - Xs) + b3 * (Y - Ys) + c3 * (Z - Zs));
        //A_begin_col是定位到数值开始填充的列
        //由输入矩阵的第一列，判断是哪个像片，由A_begin_col得到这个像片所对应的初始列
        //每次计算两行
        A_begin_col = (indexA - 1) * 6;
        Finall(i * 2, A_begin_col) = (a1 * camera_focal + a3 * x) / ave_Z;
        Finall(i * 2, A_begin_col + 1) = (b1 * camera_focal + b3 * x) / ave_Z;
        Finall(i * 2, A_begin_col + 2) = (c1 * camera_focal + c3 * x) / ave_Z;
        Finall(i * 2, A_begin_col + 3) = y * sin(omega) - cos(omega) * (camera_focal * cos(kapa) + x / camera_focal *
                                                                           (x * cos(kapa) -y * sin(kapa)));
        Finall(i * 2, A_begin_col + 4) = -camera_focal * sin(kapa) - x / camera_focal * (x * sin(kapa) + y * cos(kapa));
        Finall(i * 2, A_begin_col + 5) = y;
        Finall(i * 2 + 1, A_begin_col) = (a2 * camera_focal + a3 * y) / ave_Z;
        Finall(i * 2 + 1, A_begin_col + 1) = (b2 * camera_focal + b3 * y) / ave_Z;
        Finall(i * 2 + 1, A_begin_col + 2) = (c2 * camera_focal + c3 * y) / ave_Z;
        Finall(i * 2 + 1, A_begin_col + 3) = -x * sin(omega) - cos(omega) * (-camera_focal * sin(kapa) +
                                                                             x / camera_focal *(x * cos(kapa) - y * sin(kapa)));
        Finall(i * 2 + 1, A_begin_col + 4) =
                -camera_focal * cos(kapa) - y / camera_focal * (x * sin(kapa) + y * cos(kapa));
        Finall(i * 2 + 1, A_begin_col + 5) = -x;
//***********************B矩阵***************************
        if (flag == 0) {
            Finall(i * 2, B_begin_col) = -Finall(i * 2, A_begin_col);
            Finall(i * 2, B_begin_col + 1) = -Finall(i * 2, A_begin_col + 1);
            Finall(i * 2, B_begin_col + 2) = -Finall(i * 2, A_begin_col + 2);
            Finall(i * 2 + 1, B_begin_col) = -Finall(i * 2 + 1, A_begin_col);
            Finall(i * 2 + 1, B_begin_col + 1) = -Finall(i * 2 + 1, A_begin_col + 1);
            Finall(i * 2 + 1, B_begin_col + 2) = -Finall(i * 2 + 1, A_begin_col + 2);
         //下一行的X值不等于这一行的X值(点变了)，就像右挪3格
            if (_42points(i, 3) != _42points(i + 1, 3)) {
                B_begin_col += 3;
            }
        }
//**********************L矩阵**************************//
        Finall(i * 2, Finall_cols - 1) = xp - x;
        Finall(i * 2 + 1, Finall_cols - 1) = yp - y;
    }
}

Design::~Design() {
    //dtor
    cout << "Object is being deleted" << endl;
}

#include "widget.h"
#include "ui_widget.h"
#include <Eigen/Geometry>

using namespace Eigen;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(To_calculate()));

}

void Widget::To_calculate(){

    QList<double> element_16;
    element_16<<431834.729<<3896023.910<<1261.736<<0.002194288<<0.00078372700<<-0.01758355;
    QList<double> element_17;
    element_17<<432224.292<< 3896015.360<< 1266.845<< 0.001888322<<0.00067279300<< -0.005601195;
    QList<double> element_18;
    element_18<< 432616.141<<3896018.089<<1269.803<<	0.001182511<<	0.0007234885<<0.007524145;
    QList<double> element_26;
    element_26<< 432028.494<< 3894841.515<<  1273.147<<-0.005528028<< 0.0007792605<< -0.01138808;
    QList<double> element_27;
    element_27<<432438.565<<  3894841.049<<1274.012<< -0.005785603<< 0.0003784083<< -0.01880947;
    QList<double> element_28;
    element_28<< 432847.537<< 3894836.718<< 1272.414<<-0.006604103<< 0.00053947040<< 0.000761938;

    double Xs2 = 0.0 , Ys2 = 0.0 , Zs2 = 0.0,varphi2 = 0.0 , omega2 = 0.0  , kappa2 = 0.0 ;
    double Xs1 = 0.0 , Ys1 = 0.0 , Zs1 = 0.0,varphi1 = 0.0 , omega1 = 0.0  , kappa1 = 0.0 ;
    switch (ui->comboBox->currentIndex()) {
    case 0:
        Xs1=element_16[0];
        Ys1=element_16[1];
        Zs1=element_16[2];
        varphi1=element_16[3];
        omega1=element_16[4];
        kappa1=element_16[5];
        Xs2=element_17[0];
        Ys2=element_17[1];
        Zs2=element_17[2];
        varphi2=element_17[3];
        omega2=element_17[4];
        kappa2=element_17[5];
        break;
    case 1:
        Xs1=element_17[0];
        Ys1=element_17[1];
        Zs1=element_17[2];
        varphi1=element_17[3];
        omega1=element_17[4];
        kappa1=element_17[5];
        Xs2=element_18[0];
        Ys2=element_18[1];
        Zs2=element_18[2];
        varphi2=element_18[3];
        omega2=element_18[4];
        kappa2=element_18[5];
        break;
    case 2:
        Xs1=element_26[0];
        Ys1=element_26[1];
        Zs1=element_26[2];
        varphi1=element_26[3];
        omega1=element_26[4];
        kappa1=element_26[5];
        Xs2=element_27[0];
        Ys2=element_27[1];
        Zs2=element_27[2];
        varphi2=element_27[3];
        omega2=element_27[4];
        kappa2=element_27[5];
        break;
    case 3:
        Xs1=element_27[0];
        Ys1=element_27[1];
        Zs1=element_27[2];
        varphi1=element_27[3];
        omega1=element_27[4];
        kappa1=element_27[5];
        Xs2=element_28[0];
        Ys2=element_28[1];
        Zs2=element_28[2];
        varphi2=element_28[3];
        omega2=element_28[4];
        kappa2=element_28[5];
        break;
    default:
        ui->resulttext->append("ok?");

    }

    double focal_length = 70.5;//mm
     //同名像点在左像的坐标
     Vector3d Left_image_coordinate;
     Left_image_coordinate << ui->LX->text().toDouble(),  ui->LY->text().toDouble(), -focal_length;
     //同名像点在右像的坐标
     Vector3d Right_image_coordinate;
     Right_image_coordinate << ui->RX->text().toDouble(),  ui->RY->text().toDouble(), -focal_length;


    //摄影基线的三个分量
    double Bx = Xs2 - Xs1;
    double By = Ys2 - Ys1;
    double Bz = Zs2 - Zs1;
    /**********************************计算旋转矩阵******************************/
    //左像片的旋转矩阵
    Matrix3d Left_Rotate;
    Left_Rotate(0, 0) = cos(varphi1) * cos(kappa1) - sin(varphi1) * sin(omega1) * sin(kappa1);
    Left_Rotate(0, 1) = (-1.0) * cos(varphi1) * sin(kappa1) - sin(varphi1) * sin(omega1) * cos(kappa1);
    Left_Rotate(0, 2) = (-1.0) * sin(varphi1) * cos(omega1);
    Left_Rotate(1, 0) = cos(omega1) * sin(kappa1);
    Left_Rotate(1, 1) = cos(omega1) * cos(kappa1);
    Left_Rotate(1, 2) = (-1.0) * sin(omega1);
    Left_Rotate(2, 0) = sin(varphi1) * cos(kappa1) + cos(varphi1) * sin(omega1) * sin(kappa1);
    Left_Rotate(2, 1) = (-1.0) * sin(varphi1) * sin(kappa1) + cos(varphi1) * sin(omega1) * cos(kappa1);
    Left_Rotate(2, 2) = cos(varphi1) * cos(omega1);
    //右像片的旋转矩阵
    Matrix3d Right_Rotate;
    Right_Rotate(0, 0) = cos(varphi2) * cos(kappa2) - sin(varphi2) * sin(omega2) * sin(kappa2);
    Right_Rotate(0, 1) = (-1.0) * cos(varphi2) * sin(kappa2) - sin(varphi2) * sin(omega2) * cos(kappa2);
    Right_Rotate(0, 2) = (-1.0) * sin(varphi2) * cos(omega2);
    Right_Rotate(1, 0) = cos(omega2) * sin(kappa2);
    Right_Rotate(1, 1) = cos(omega2) * cos(kappa2);
    Right_Rotate(1, 2) = (-1.0) * sin(omega2);
    Right_Rotate(2, 0) = sin(varphi2) * cos(kappa2) + sin(varphi2) * sin(omega2) * sin(kappa2);
    Right_Rotate(2, 1) = (-1.0) * sin(varphi2) * sin(kappa2) + cos(varphi2) * sin(omega2) * cos(kappa2);
    Right_Rotate(2, 2) = cos(varphi2) * cos(omega2);
//同名像点的像空间辅助坐标
    Vector3d Left_aux_coordinate;
    Left_aux_coordinate = Left_Rotate * Left_image_coordinate;
    Vector3d Right_aux_coordinate;
    Right_aux_coordinate = Right_Rotate * Right_image_coordinate;
//计算投影系数Left_N Right_N
    double X1 = Left_aux_coordinate(0, 0);
    double Y1 = Left_aux_coordinate(1, 0);
    double Z1 = Left_aux_coordinate(2, 0);

    double X2 = Right_aux_coordinate(0, 0);
    double Y2 = Right_aux_coordinate(1, 0);
    double Z2 = Right_aux_coordinate(2, 0);

    double Left_N = (Bx * Z2 - Bz * X2) / (X1 * Z2 - X2 * Z1);
    double Right_N = (Bx * Z1 - Bz * X1) / (X1 * Z2 - X2 * Z1);

    //计算地面点的左像像辅系坐标
    double delta_X = Left_N * X1;
    double delta_Y = (Left_N * Y1 + Right_N * Y2 + By) / 2.0;
    double delta_Z = Left_N * Z1;
//    printf("地面点的左像像辅系坐标\n%.3lf,%.3lf,%.3lf\n", delta_X, delta_Y, delta_Z);
    //地面点的地面坐标
    double ground_X = Xs1 + delta_X;
    double ground_Y = Ys1 + delta_Y;
    double ground_Z = Zs1 + delta_Z;

   ui->resulttext->setText(QString::fromLocal8Bit("地面点坐标为:\n")+QString::number(ground_X,'f',3)+"\t"+QString::number(ground_Y,'f',3)+"\t"+QString::number(ground_Z,'f',3));


}
Widget::~Widget()
{
    delete ui;
}


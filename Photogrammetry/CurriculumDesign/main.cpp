#include <ctime>
#include "Design.h"

clockid_t startime, endtime;//计算程序运行时间的

int main() {
    startime = clock();
    Design project;
    project.setCameraFocal(70.50);//设置相机焦距
    project.setControlNumber(6);//设置控制点数
    project.setInputPath("../files/42.csv");//输入文件路径
    project.setOutPath("../files/output.xls");//输出文件路径
    cout << "像片数：" << project.number_photo << endl;
    cout << "所有点：" << project.AllMarkPointsNumber << endl;
    cout << "所有图上点：" << project.AllPhotoPointsNumber << endl;
    endtime = clock();
    double totaltime = (double) (endtime - startime) / CLOCKS_PER_SEC;
    cout << "Total Time:" << totaltime * 1000 << " ms" << endl;
    return 0;
}



#include <ctime>
#include "Design.h"

clockid_t startime, endtime;

int main() {
    startime = clock();
    Design project;
    project.setControlNumber(6);
    project.setInputPath("../files/42.csv");
    project.setOutPath("../files/output.xlsx");
    cout << "像片数：" << project.number_photo << endl;
    cout << "所有点：" << project.AllMarkPointsNumber << endl;
    cout << "所有图上点：" << project.AllPhotoPointsNumber << endl;
    endtime = clock();
    double totaltime = (double) (endtime - startime) / CLOCKS_PER_SEC;
    cout << "Total Time:" << totaltime * 1000 << " ms" << endl;
    return 0;
}



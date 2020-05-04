//
// Created by kk on 2020/4/27.
//

#include "ImgMatch.h"
#include <iostream>

/*构造函数*/
ImgMatch::ImgMatch() {
        std::cout << "对象已创建,开始执行程序" << std::endl;
}

void ImgMatch::ShowImage(cv::Mat &Image, cv::Point2i lu, cv::Point2i rd, const cv::Scalar &color) {
        cv::rectangle(Image, lu, rd, color);
//
        cv::imshow("origin", Image);
}

/*匹配函数*/
void ImgMatch::MatchingImage() {
        //画出搜索区域
        ShowImage(*originImage, leftup, rightdown, cv::Scalar(255, 0, 0));
        cv::putText(*originImage, "SearchArea", leftup, cv::FONT_HERSHEY_TRIPLEX, 0.5, cv::Scalar(255, 0, 0));
        //获取匹配窗口大小
        int targetWindowWidth = templateImage->cols;
        int targetWIndowHeight = templateImage->rows;
        //在搜索区域内进行模板匹配
        for (int i = 0; i < rightdown.x - leftup.x - targetWindowWidth; ++i) {
                for (int j = 0; j < rightdown.y - leftup.y - targetWIndowHeight; ++j) {
                        cv::Mat newIMage;
                        originImage->copyTo(newIMage);
                        cv::Point2i newleftup(leftup.x + i, leftup.y + j);
                        cv::Point2i newrightdown(newleftup.x + targetWindowWidth, newleftup.y + targetWIndowHeight);
                        ShowImage(newIMage, newleftup, newrightdown, cv::Scalar(0, 255, 0));
                        if (cv::waitKey(1) == 27)
                                break;
                }
        }


}

float ImgMatch::getCorrelation(cv::Mat &targetImage, cv::Mat &searchImage) {

        return 0;
}

//
// Created by kk on 2020/4/27.
//

#ifndef IMAGEMATCHING_IMGMATCH_H
#define IMAGEMATCHING_IMGMATCH_H

#include <opencv2/opencv.hpp>

class ImgMatch {
public:
    ImgMatch();//构造函数
    void getImage(cv::Mat& Image) {
            originImage = &Image;
            leftup.x = 0;
            leftup.y = 0;
            rightdown.x=originImage->cols-1;
            rightdown.y=originImage->rows-1;
    }

    void getTemplateImage(cv::Mat& Image) { templateImage = &Image; }
    //获取区域角点坐标
    void getCornerPoint(int leftupX, int leftupY, int rightdownX, int rightdownY)
    {        leftup.x = leftupX;
            leftup.y = leftupY;
            rightdown.x=rightdownX;
            rightdown.y=rightdownY;}
    void MatchingImage();

private:
    std::vector<float> *CCORR;
    cv::Mat *originImage{};
    cv::Mat *templateImage{};
    cv::Mat *resultImage{};
    cv::Point2i leftup{};
    cv::Point2i rightdown{};
    static void ShowImage(cv::Mat Imag ,cv::Point2i lu,cv::Point2i rd,const cv::Scalar& color);
    static float getCorrelation(cv::Mat & targetImage,cv::Mat &searchImage);
    void MarkResult();


};


#endif //IMAGEMATCHING_IMGMATCH_H

//
// Created by kk on 2020/4/27.
//

#ifndef IMAGEMATCHING_IMGMATCH_H
#define IMAGEMATCHING_IMGMATCH_H

#include <opencv2/opencv.hpp>

class ImgMatch {
public:
    ImgMatch();//构造函数
    void getImage(cv::Mat Image) { originImage = Image; };

    void getTemplateImage(cv::Mat Image) { templateImage = Image; };
    void MatchingImage();
private:
    cv::Mat originImage;
    cv::Mat templateImage;


};


#endif //IMAGEMATCHING_IMGMATCH_H

//
// Created by kk on 2020/4/27.
//
#include<iostream>
#include<opencv2/opencv.hpp>
#include "ImgMatch.h"

int main(){

        cv::Mat image=cv::imread("../Assets/airport.bmp");
        cv::Mat templateImage=cv::imread("../Assets/template.bmp");
        //创建对象
        ImgMatch ImgMatching;
        //输入模板影像
        ImgMatching.getTemplateImage(templateImage);
        //输入待匹配影像
        ImgMatching.getImage(image);
        //指定搜索区域,若不指定即在全图范围内匹配
        ImgMatching.getCornerPoint(250,250,330,330);
        //进行匹配
        ImgMatching.MatchingImage();
        return 0;
}



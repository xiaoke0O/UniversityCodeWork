//
// Created by kk on 2020/4/27.
//
#include<iostream>
#include<opencv2/opencv.hpp>
#include "ImgMatch.h"

int main(){
        std::cout<<"Hello"<<std::endl;

        cv::Mat image=cv::imread("../Assets/airport.bmp");
        cv::Mat templateImage=cv::imread("../Assets/template.bmp");
        ImgMatch ImgMatching;
        ImgMatching.getImage(image);
        ImgMatching.getTemplateImage(templateImage);
        ImgMatching.MatchingImage();
        return 0;
}



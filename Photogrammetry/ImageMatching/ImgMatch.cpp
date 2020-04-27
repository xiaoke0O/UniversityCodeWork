//
// Created by kk on 2020/4/27.
//

#include "ImgMatch.h"
#include <iostream>
ImgMatch::ImgMatch(){
std::cout<<"对象已创建\n开始执行程序"<<std::endl;
}
void ImgMatch::MatchingImage() {
        cv::imshow("OriginImage",originImage);
        cv::waitKey(0);

}
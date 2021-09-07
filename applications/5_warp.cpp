#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>

/// warp images
int main(){
    
    std::string path = "../../resources/cards.jpg";
    cv::Mat img = cv::imread(path);
    float w = 250, h = 350; // width and height of a card
    
    std::vector<cv::Point2f> src = {{529,142}, {771,190}, {405,395}, {674,457}};
    std::vector<cv::Point2f> dst = {{0.0f,0.0f}, {w,0.0f}, {0.0f,h}, {w,h}};
    
    cv::Mat matrix = cv::getPerspectiveTransform(src, dst);
    
    cv::Mat imgWarp;
    cv::warpPerspective(img, imgWarp, matrix, cv::Size(w, h));
    
    for (int i=0; i < src.size(); ++i) {
        cv::circle(img, src[i], 5, cv::Scalar(0, 0, 255), cv::FILLED);
    }
    
    cv::imshow("Image", img);
    cv::imshow("ImageWarp", imgWarp);
    cv::waitKey(0);
    return 0;
}

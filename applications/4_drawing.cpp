#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

/// drawing shapes and text
int main() {
    
    // blank image
    cv::Mat img(512, 512, CV_8UC3, cv::Scalar(255, 255, 255));
    
    // create circle last parameter controls thickness
//    cv::circle(img, cv::Point(256, 256), 155, cv::Scalar(0, 69, 255), 10);
    
    // create circle last parameter defines it as a filled circle
    cv::circle(img, cv::Point(256, 256), 155, cv::Scalar(0, 69, 255), cv::FILLED);
    
    // draw rectangle
    cv::rectangle(img, cv::Point(130, 226), cv::Point(382, 286), cv::Scalar(255, 255, 255), cv::FILLED);
    
    // draw line
    cv::line(img, cv::Point(130, 296), cv::Point(382, 296), cv::Scalar(255, 255, 255), 2);
    
    // draw text
    cv::putText(img, "Omar's Workshop", cv::Point(143, 262), cv::FONT_HERSHEY_DUPLEX, 0.8, cv::Scalar(0, 69, 255), 2);
    
    cv::imshow("Image", img);
    cv::waitKey(0);
    return 0;
}

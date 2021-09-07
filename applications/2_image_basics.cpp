#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

/// basic functions for images
int main() {
    std::string path = "../../resources/test.png";
    cv::Mat img = cv::imread(path);
    
    // initialise a matrix with zeros
    cv::Mat imgZeros = cv::Mat::zeros(img.size(), CV_64FC3);
    
    // convert to grayscale
    cv::Mat imgGray;
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    
    // add Gaussian blur
    cv::Mat imgBlur;
    cv::GaussianBlur(imgGray, imgBlur, cv::Size(3,3), 5, 0);
    
    // Canny edge detector
    cv::Mat imgCanny;
    cv::Canny(imgBlur, imgCanny, 50, 150);
    
    // dilate an image (increase thickness)
    cv::Mat imgDilate;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::dilate(imgCanny, imgDilate, kernel);
    
    // erode an image (decrease thickness)
    cv::Mat imgErode;
    cv::erode(imgDilate, imgErode, kernel);
    
    cv::imshow("Original", img);
    cv::imshow("Zeros", imgZeros);
    cv::imshow("Grayscale", imgGray);
    cv::imshow("Blur", imgBlur);
    cv::imshow("Canny", imgCanny);
    cv::imshow("Dilate", imgDilate);
    cv::imshow("Erode", imgErode);
    
    cv::waitKey(0);
    return 0;
}

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int hmin = 0, smin = 110, vmin = 153;
int hmax = 19, smax = 240, vmax = 255;

/// color detection in images
//int main(){
//    std::string path = "../../resources/lambo.png";
//    cv::Mat img = cv::imread(path);
//
//    // convert to HSV color space
//    cv::Mat imgHSV, mask;
//    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);
//
//    // values hardcoded for orange
//    cv::Scalar lower(hmin, smin, vmin);
//    cv::Scalar upper(hmax, smax, vmax);
//
//    // collect the color orange
//    cv::inRange(imgHSV, lower, upper, mask);
//
//    cv::imshow("Image", img);
//    cv::imshow("ImageHSV", imgHSV);
//    cv::imshow("Mask", mask);
//    cv::waitKey(0);
//    return 0;
//}

///// color detection in images with a trackbar
//int main(){
//    std::string path = "../../resources/shapes.png";
//    cv::Mat img = cv::imread(path);
//
//    // convert to HSV color space
//    cv::Mat imgHSV, mask;
//    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);
//
//    // create trackbars
//    cv::namedWindow("Trackbars");
//    cv::createTrackbar("Hue Min", "Trackbars", &hmin, 179);
//    cv::createTrackbar("Hue Max", "Trackbars", &hmax, 179);
//    cv::createTrackbar("Sat Min", "Trackbars", &smin, 255);
//    cv::createTrackbar("Sat Max", "Trackbars", &smax, 255);
//    cv::createTrackbar("Val Min", "Trackbars", &vmin, 255);
//    cv::createTrackbar("Val Max", "Trackbars", &vmax, 255);
//
//    while (true) {
//        cv::Scalar lower(hmin, smin, vmin);
//        cv::Scalar upper(hmax, smax, vmax);
//        cv::inRange(imgHSV, lower, upper, mask);
//
//        cv::imshow("Image", img);
//        cv::imshow("ImageHSV", imgHSV);
//        cv::imshow("Mask", mask);
//        cv::waitKey(1);
//    }
//    return 0;
//}

/// color picker with a webcam
int main(){
    cv::VideoCapture capture(1);
    cv::Mat frame, frameHSV, mask;
    
    // create trackbars
    cv::namedWindow("Settings");
    cv::createTrackbar("Hue Min", "Settings", &hmin, 179);
    cv::createTrackbar("Hue Max", "Settings", &hmax, 179);
    cv::createTrackbar("Sat Min", "Settings", &smin, 255);
    cv::createTrackbar("Sat Max", "Settings", &smax, 255);
    cv::createTrackbar("Val Min", "Settings", &vmin, 255);
    cv::createTrackbar("Val Max", "Settings", &vmax, 255);
    
    while (capture.read(frame)) {
        cv::cvtColor(frame, frameHSV, cv::COLOR_BGR2HSV);
        cv::Scalar lower(hmin, smin, vmin);
        cv::Scalar upper(hmax, smax, vmax);
        cv::inRange(frameHSV, lower, upper, mask);
        
        cv::imshow("Image", frame);
        cv::imshow("Mask", mask);
        if (cv::waitKey(10) == 't') {
            std::cout << hmin << " "
                      << hmax << " "
                      << smin << " "
                      << smax << " "
                      << vmin << " "
                      << vmax << " " << std::endl;
        } else if (cv::waitKey(10) == 'q') {
            break;
        }
    }
    
    capture.release();
    cv::destroyAllWindows();
    return 0;
}

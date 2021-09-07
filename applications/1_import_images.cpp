#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

/// working with images
//int main() {
//    std::string path = "../../resources/test.png";
//    cv::Mat img = cv::imread(path);
//    cv::imshow("Image", img);
//    cv::waitKey(0);
//    return 0;
//}

/// working with videos
//int main() {
//    std::string path = "../../resources/test_video.mp4";
//    cv::VideoCapture cap(path);
//    cv::Mat img;
//
//    while (true) {
//        cap.read(img);
//        cv::imshow("Image", img);
//        cv::waitKey(20);
//    } // error when it ends because no more images
//    return 0;
//}

/// working with webcam
int main() {
    cv::VideoCapture cap(1); // 0 for internal webcam, 1 for external webcam
    cv::Mat img;
    
    while (true) {
        cap.read(img);
        cv::imshow("Image", img);
        cv::waitKey(1);
    }
    return 0;
}

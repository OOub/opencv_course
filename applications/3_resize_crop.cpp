#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

/// resize and crop images
int main() {
    std::string path = "../../resources/test.png";
    cv::Mat img = cv::imread(path);
    
    // print image size
    std::cout << img.size() << std::endl;
    
    // resize image
    cv::Mat imgResize;
    cv::resize(img, imgResize, cv::Size(640, 480));
    
    // resize image with scale instead of size
    cv::Mat imgResizeScale;
    cv::resize(img, imgResizeScale, cv::Size(), 0.5, 0.5);
    
    // crop an image
    cv::Rect roi(200, 50, 300, 350);
    cv::Mat imgCrop = img(roi);
    
    cv::imshow("Original", img);
    cv::imshow("Resized", imgResize);
    cv::imshow("Resized with scale", imgResizeScale);
    cv::imshow("Crop", imgCrop);
    
    cv::waitKey(0);
    return 0;
}

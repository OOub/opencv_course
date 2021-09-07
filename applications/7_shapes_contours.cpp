#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

void getContours(cv::Mat src_image, cv::Mat dst_image) {
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(src_image, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    
    // filter noise before drawing
    std::vector<std::vector<cv::Point>> conPoly(contours.size());
    std::vector<cv::Rect> boundRect(contours.size());
    for (int i=0; i<contours.size(); i++) {
        int area = cv::contourArea(contours[i]);
        if (area > 1000) {
            // find contour perimeter
            float perimeter = cv::arcLength(contours[i], true);
            
            // find corner points
            cv::approxPolyDP(contours[i], conPoly[i], 0.02*perimeter, true);
            
            // draw
            cv::drawContours(dst_image, conPoly, i, cv::Scalar(0, 0, 255), 2);
            cv::drawContours(dst_image, contours, i, cv::Scalar(255, 0, 255), 2);
            
            // find bounding box around object
            boundRect[i] = cv::boundingRect(conPoly[i]);
            cv::rectangle(dst_image, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 2);
            
            // print the name of the polygones
            std::string objectType;
            int objCor = static_cast<int>(conPoly[i].size());
            if (objCor == 3) {
                objectType = "Triangle";
            } else if (objCor == 4) {
                float aspRatio = static_cast<float>(boundRect[i].width) / static_cast<float>(boundRect[i].height);
                
                if (aspRatio > 0.95 && aspRatio < 1.05) {
                    objectType = "Square";
                } else {
                    objectType = "Rectangle";
                }
            } else if (objCor > 4) {
                objectType = "Circle";
            }
            
            cv::putText(dst_image, objectType, cv::Point(boundRect[i].x, boundRect[i].y - 5), cv::FONT_HERSHEY_PLAIN, 0.75, cv::Scalar(0, 0, 0), 1);
        }
    }
}

/// detect shapes and contours in images
int main(){
    std::string path = "../../resources/shapes.png";
    cv::Mat img = cv::imread(path);
    
    // pre-processing pipeline
    cv::Mat imgGray, imgBlur, imgCanny, imgDil;
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY); // start with grayscale
    cv::GaussianBlur(imgGray, imgBlur, cv::Size(3,3), 3, 0); // gaussian blur
    cv::Canny(imgBlur, imgCanny, 25, 75); // canny edge detector
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));// dilation kernel
    cv::dilate(imgCanny, imgDil, kernel); // dilation
    
    // find contours
    getContours(imgDil, img);
    
    cv::imshow("Image", img);

    cv::waitKey(0);
    return 0;
}

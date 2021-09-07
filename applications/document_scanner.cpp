#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;

Mat preprocess(Mat image) {
    Mat processed;
    cv::cvtColor(image, processed, cv::COLOR_BGR2GRAY); // start with grayscale
    cv::GaussianBlur(processed, processed, cv::Size(3,3), 3, 0); // gaussian blur
    cv::Canny(processed, processed, 25, 75); // canny edge detector
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));// dilation kernel
    cv::dilate(processed, processed, kernel); // dilation
    return processed;
}

std::vector<Point> getContours(Mat mask, Mat image) {
    std::vector<std::vector<Point>> contours;
    std::vector<Vec4i> hierarchy;
    
    cv::findContours(mask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    
    std::vector<std::vector<Point>> conPoly(contours.size());
    std::vector<Rect> boundRect(contours.size());
    std::vector<Point> biggest; // need to find the biggest contour
    
    int maxArea = 0;
    for (int i=0; i<contours.size(); i++) {
        int area = cv::contourArea(contours[i]);
        if (area > 1000) {
            // find contour perimeter
            float perimeter = cv::arcLength(contours[i], true);
            
            // find corner points
            cv::approxPolyDP(contours[i], conPoly[i], 0.02*perimeter, true);
            
            // ignoring non-rectangular shapes
            if (area > maxArea && conPoly[i].size() == 4) {
                maxArea = area;
                biggest = conPoly[i];
            }
        }
    }
    
    return biggest;
}

std::vector<Point> reorderPoints(std::vector<Point> points) {
    std::vector<Point> new_points;
    std::vector<int> sum_points, sub_points;
    
    for (int i=0;  i<points.size(); ++i) {
        sum_points.push_back(points[i].x + points[i].y);
        sub_points.push_back(points[i].x - points[i].y);
    }
    
    // 0
    auto min = std::min_element(sum_points.begin(), sum_points.end());
    auto min_index = std::distance(sum_points.begin(), min);
    new_points.push_back(points[min_index]);
    
    // 1
    auto first = std::max_element(sub_points.begin(), sub_points.end());
    auto first_index = std::distance(sub_points.begin(), first);
    new_points.push_back(points[first_index]);
    
    // 2
    auto second = std::min_element(sub_points.begin(), sub_points.end());
    auto second_index = std::distance(sub_points.begin(), second);
    new_points.push_back(points[second_index]);
    
    // 3
    auto max = std::max_element(sum_points.begin(), sum_points.end());
    auto max_index = std::distance(sum_points.begin(), max);
    new_points.push_back(points[max_index]);
    
    return new_points;
}

void drawPoints(Mat image, std::vector<Point> points, Scalar color) {
    for (int i=0; i<points.size(); ++i) {
        circle(image, points[i], 10, color, FILLED);
        putText(image, std::to_string(i), points[i], FONT_HERSHEY_PLAIN, 4, color, 4);
    }
}

Mat warp(Mat image, std::vector<Point> points, float w=420, float h=596) {
    
    std::vector<cv::Point2f> src = {points[0], points[1], points[2], points[3]};
    std::vector<cv::Point2f> dst = {{0.0f,0.0f}, {w,0.0f}, {0.0f,h}, {w,h}};
    cv::Mat matrix = getPerspectiveTransform(src, dst);
    
    cv::Mat imageWarp;
    cv::warpPerspective(image, imageWarp, matrix, cv::Size(w, h));
    return imageWarp;
}

int main() {
    std::string path = "../../resources/paper.jpg";
    cv::Mat image = cv::imread(path);
    
    // pre-processing pipeline
    Mat image_processed = preprocess(image);
    
    // get contours
    std::vector<Point> initialPoints = getContours(image_processed, image);
    
    // reorder points so they are consistent
    std::vector<Point> reorderedPoints = reorderPoints(initialPoints);

    // warp
    float w = 420;
    float h = 596;
    Mat image_warped = warp(image, reorderedPoints, w, h);
    
    // crop
    int cropVal = 5;
    cv::Rect roi(cropVal, cropVal, w-(2*cropVal), h-(2*cropVal));
    cv::Mat image_cropped = image_warped(roi);
    
    // draw contours on original
    drawContours(image, std::vector<std::vector<Point>>({initialPoints}), -1, Scalar(0, 0, 255), 2);
    drawPoints(image, reorderedPoints, Scalar(0, 0, 255));

    cv::imshow("Image", image);
    cv::imshow("Image Warped", image_warped);
    cv::imshow("Image Cropped", image_cropped);
    cv::waitKey(0);
    return 0;
}

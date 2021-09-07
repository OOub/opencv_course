#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

/// virtual painter

using namespace cv;

Point getContours(Mat& mask, Mat& frame) {
    std::vector<std::vector<Point>> contours;
    std::vector<Vec4i> hierarchy;
    
    cv::findContours(mask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    
    std::vector<std::vector<Point>> conPoly(contours.size());
    std::vector<Rect> boundRect(contours.size());
    Point point(0,0);
    for (int i=0; i<contours.size(); i++) {
        int area = cv::contourArea(contours[i]);
        if (area > 1000) {
            // find contour perimeter
            float perimeter = cv::arcLength(contours[i], true);
            
            // find corner points
            cv::approxPolyDP(contours[i], conPoly[i], 0.02*perimeter, true);
            
            // find bounding box around object
            boundRect[i] = boundingRect(conPoly[i]);
            point.x = boundRect[i].x + boundRect[i].width / 2;
            point.y = boundRect[i].y;
            
            // draw
            cv::drawContours(frame, conPoly, i, Scalar(0, 0, 255), 2);
            cv::rectangle(frame, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 2);
        }
    }
    
    return point;
}

void findColor(Mat& frame, std::vector<std::vector<int>>& new_points, std::vector<std::vector<int>>& colors) {
    Mat frameHSV;
    cvtColor(frame, frameHSV, cv::COLOR_BGR2HSV);
    
    for (int i=0; i<colors.size(); ++i) {
        Scalar lower(colors[i][0], colors[i][2], colors[i][4]);
        Scalar upper(colors[i][1], colors[i][3], colors[i][5]);
        Mat mask;
        inRange(frameHSV, lower, upper, mask);
        imshow(std::to_string(i), mask);
        Point point = getContours(mask, frame);
        if (point.x != 0 && point.y != 0) {
            new_points.push_back({point.x, point.y, i});
        }
    }
    
}

void drawOnCanvas(Mat& frame, std::vector<std::vector<int>>& new_points, std::vector<Scalar>& color_values) {
    for (int i=0; i<new_points.size(); ++i) {
        circle(frame, Point(new_points[i][0], new_points[i][1]), 10, color_values[new_points[i][2]], FILLED);
    }
}

int main() {
    
    // choosing the colors
    std::vector<std::vector<int>> colors{
        {60,92,45,254,232,255}, // green
        {170,179,62,254,232,255}, // red
        {102,124,60,254,232,255}}; //blue

    std::vector<Scalar> color_values{
        {0, 255, 0}, // green
        {0, 0, 255}, // red
        {255, 0, 0}}; // blue
    
    VideoCapture capture(1);
    Mat frame;
    std::vector<std::vector<int>> new_points; // {x, y, color_value index}
    
    while (capture.read(frame)) {
        // exit when no more frames
        if (frame.empty()) {
            std::cout << "No frame captured from camera" << std::endl;
            break;
        }
        
        findColor(frame, new_points, colors);
        drawOnCanvas(frame, new_points, color_values);
        
        imshow("Webcam", frame);
        
        // exit when q is pressed
        if (waitKey(10) == 'q') {
            break;
        };
    }
    
    capture.release();
    destroyAllWindows();
    return 0;
}

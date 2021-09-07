#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

// face detection in an image using Viola Jones method of Harr Cascades
//int main(){
//    std::string path = "../../resources/test.png";
//    cv::Mat img = cv::imread(path);
//
//    // load the pretrained network
//    cv::CascadeClassifier faceCascade;
//    faceCascade.load("../../resources/haarcascade_frontalface_default.xml");
//
//    std::vector<cv::Rect> faces;
//    faceCascade.detectMultiScale(img, faces, 1.1, 10);
//
//    for (int i=0; i<faces.size(); ++i) {
//        cv::rectangle(img, faces[i].tl(), faces[i].br(), cv::Scalar(0, 255, 0), 2);
//    }
//
//    cv::imshow("Image", img);
//    cv::waitKey(0);
//    return 0;
//}

// face detection with a webcam using Viola Jones method of Harr Cascades
int main(){
    // load the pretrained network
    cv::CascadeClassifier face_cascade;
    face_cascade.load("../../resources/haarcascade_frontalface_default.xml");
    
    // error handling for wrong file
    if (face_cascade.empty()) {
        std::cout << "XML file not loaded properly" << std::endl;
        return -1;
    }
    
    // capture from external webcam
    cv::VideoCapture capture(0);
    cv::Mat frame;
    while (capture.read(frame)) {
        // exit when no more frames
        if (frame.empty()) {
            std::cout << "No frame captured from camera" << std::endl;
            break;
        }
        
        // convert to grayscale
        cv::Mat frame_gray;
        cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
        
        // apply viola jones algorithm
        std::vector<cv::Rect> faces;
        face_cascade.detectMultiScale(frame_gray, faces);
        
        // display rectangles around face
        for (int i=0; i<faces.size(); ++i) {
            cv::rectangle(frame, faces[i].tl(), faces[i].br(), cv::Scalar(0, 255, 0), 2);
        }

        cv::imshow("Webcam", frame);
        
        // press q to exit
        if (cv::waitKey(10) == 'q') {
            break;
        }
    }
    
    capture.release();
    cv::destroyAllWindows();
    return 0;
}


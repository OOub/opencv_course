#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;

// plate detection with a webcam using Viola Jones method of Harr Cascades
int main(){
    // load the pretrained network
    CascadeClassifier plate_cascade;
    plate_cascade.load("../../resources/haarcascade_russian_plate_number.xml");
    
    // error handling for wrong file
    if (plate_cascade.empty()) {
        std::cout << "XML file not loaded properly" << std::endl;
        return -1;
    }
    
    // capture from external webcam
    VideoCapture capture(1);
    Mat frame;
    while (capture.read(frame)) {
        // exit when no more frames
        if (frame.empty()) {
            std::cout << "No frame captured from camera" << std::endl;
            break;
        }
        
        // apply viola jones algorithm
        std::vector<Rect> plates;
        plate_cascade.detectMultiScale(frame, plates, 1.1, 10);
        
        // display rectangles around plate
        for (int i=0; i<plates.size(); ++i) {
            Mat cropped = frame(plates[i]);
            imshow("License plate", cropped);
            imwrite("../../resources/plate.png", cropped);
            rectangle(frame, plates[i].tl(), plates[i].br(), Scalar(0, 255, 0), 2);
        }

        imshow("Webcam", frame);
        
        // press q to exit
        if (waitKey(10) == 'q') {
            break;
        }
    }
    
    capture.release();
    destroyAllWindows();
    return 0;
}


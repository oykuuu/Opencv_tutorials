#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include <numeric>

using namespace cv;
int main()
{
    VideoCapture video("./videos/bottle-detection.mp4");
    VideoWriter writer("./videos/processed-bottle-detection.avi", VideoWriter::fourcc('M','J','P','G'), 10, Size(video.get(CAP_PROP_FRAME_WIDTH), video.get(CAP_PROP_FRAME_HEIGHT))); ;

    while(1)
    {
        Mat frame, processed;
        video >> frame;

        if (frame.empty())
            break;

        Canny(frame, processed, 150, 200, 3);
        cvtColor(processed, processed, COLOR_GRAY2BGR);
        writer.write(processed);
        
    }

    video.release();
    writer.release();

    return 0;
}
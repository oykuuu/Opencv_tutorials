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
    const auto width_video = video.get(CAP_PROP_FRAME_WIDTH);
    const auto height_video = video.get(CAP_PROP_FRAME_HEIGHT);
    VideoWriter writer("./videos/corner-bottle-detection.avi", VideoWriter::fourcc('M','J','P','G'), 10, Size(width_video, height_video));

    Mat m_template = imread("images/bottleCap.png", IMREAD_COLOR);
    const auto scale = m_template.rows/height_video;
    const auto width = m_template.cols/scale;
    const auto height = height_video;
    resize(m_template, m_template, Size(width, height));

    Mat match_template;

    while(1)
    {
        Mat frame_color, frame;
        video >> frame_color;

        if (frame_color.empty())
            break;

        Mat processed(frame_color.size(), CV_32FC1);
        cvtColor(frame_color, frame, COLOR_BGR2GRAY);

        int matchVal = 0;
        Point matchLoc;
        int m_cols, m_rows;
        for(double alpha = 0.5; alpha < 1.0; alpha+=0.1)
        {
            resize(m_template, match_template, Size(width*alpha, height*alpha));
            cvtColor(match_template, match_template, COLOR_BGR2GRAY);
            matchTemplate(frame, match_template, processed, TM_CCOEFF);
            normalize(processed, processed, 0, 1, NORM_MINMAX, -1, Mat());
            double maxVal, minVal;
            Point maxIndex, minIndex;
            minMaxLoc(processed, &minVal, &maxVal, &minIndex, &maxIndex);
            if(maxVal > matchVal & maxVal > 0.7)
            {
                matchVal = maxVal;
                matchLoc = maxIndex;
                m_cols = match_template.cols;
                m_rows = match_template.rows;
            }
        }
        
        Point bottomPoint(matchLoc.x + m_cols, matchLoc.y + m_rows);
        rectangle(frame_color, matchLoc, bottomPoint, Scalar(128, 255, 230), 4);
        writer.write(frame_color);
        
    }

    video.release();
    writer.release();

    return 0;
}
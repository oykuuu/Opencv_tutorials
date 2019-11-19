#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>

using namespace cv;

int main()
{
    Mat image = imread("images/shapes.jpg", IMREAD_GRAYSCALE);
    Mat color = imread("images/shapes.jpg", IMREAD_COLOR);

    Mat edges, curves;
    std::vector<std::vector<Point>> contours, approxContours;
    GaussianBlur(image, image, Size(3, 3), 3);
    Canny(image, edges, 150, 200, 3);
    findContours(edges, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    approxContours.resize(contours.size());
    Mat contour_image = Mat::zeros(image.size(), CV_8UC3);
    for (auto i = 0; i < contours.size(); ++i)
    {
        approxPolyDP(contours[i], approxContours[i], 5, true);
        /*if(approxContours[i].size() == 3)
        {
            drawContours(color, approxContours, static_cast<int>(i), Scalar(255,255,200));
        } 
        else if(approxContours[i].size() == 4)
        {
            drawContours(color, approxContours, static_cast<int>(i), Scalar(255,0,255));
        }*/
    }
    drawContours(color, approxContours, -1, Scalar(255,255,255));
    std::vector<Mat> imageArray;
    imageArray.push_back(color);
    cvtColor(edges, edges, COLOR_GRAY2BGR);
    imageArray.push_back(edges);
    //imageArray.push_back(contour_image);
    Mat printImage;
    hconcat(imageArray, printImage);
    namedWindow("contour");
    imshow("contour", printImage);
    waitKey(0);

    return 0;
}
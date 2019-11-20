#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include <numeric>

using namespace cv;

// take the sum of all the coordinates in a given shape
// using lambda expression
auto sum_coordinates = [](Point coord1, Point coord2){
    return Point(coord1.x + coord2.x, coord1.y + coord2.y);
};

int main()
{
    Mat edges, curves, printImage;
    std::vector<std::vector<Point>> contours, approxContours;
    std::vector<Mat> imageArray;
    
    Mat image = imread("images/shapes.jpg", IMREAD_GRAYSCALE);
    Mat color = imread("images/shapes.jpg", IMREAD_COLOR);

    // finds the contours of the shapes by feeding the edges identified with Canny
    GaussianBlur(image, image, Size(3, 3), 3);
    Canny(image, edges, 150, 200, 3);
    findContours(edges, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    approxContours.resize(contours.size());
    Mat contour_image = Mat::zeros(image.size(), CV_8UC3);
    for (auto i = 0; i < contours.size(); ++i)
    {
        // detects the closed polygonal shapes given the contours
        approxPolyDP(contours[i], approxContours[i], 5, true);
        // finds the center of the shapes via the accumulate function
        // the center can also be calculated using the cv::Moments() function (mean(x) = m10/m00, mean(y)=m01/m00)
        Point center = std::accumulate(approxContours[i].begin(), approxContours[i].end(), Point(0,0), sum_coordinates);
        center.x /= approxContours[i].size();
        center.y /= approxContours[i].size();
        circle(color, center, 2, Scalar(0,0,0), 3);
    }

    drawContours(color, approxContours, -1, Scalar(255,255,255));
    cvtColor(edges, edges, COLOR_GRAY2BGR);
    imageArray.push_back(color);
    imageArray.push_back(edges);
    hconcat(imageArray, printImage);
    namedWindow("contour");
    imshow("contour", printImage);
    waitKey(0);

    return 0;
}
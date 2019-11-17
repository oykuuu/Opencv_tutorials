#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>

using namespace cv;

Mat triangles;
int thres = 0;
int minline;
int maxgap;

void addLines(std::vector<Vec4i> hough_lines, Mat &outImage);
void on_trackbar(int, void*);
void createTrackbars(const char* winName);
void showImage(const char* name, Mat& image, bool track=true);

int main()
{
    triangles = imread("images/triangles.jpg", IMREAD_COLOR);
    createTrackbars("lines");

    on_trackbar(thres, nullptr);
    return 0;
}

void addLines(std::vector<Vec4i> hough_lines, Mat &outImage)
{
    for (auto i = 0; i < hough_lines.size(); ++i)
    {
        const auto currentLine = hough_lines[i];
        line(outImage, Point(currentLine[0], currentLine[1]), Point(currentLine[2], currentLine[3]), Scalar(200, 0, 0), 3);
    }
}

void on_trackbar(int, void*)
{
    Mat edges, grayScaledTriangles, lines;
    cvtColor(triangles, grayScaledTriangles, COLOR_BGR2GRAY);

    GaussianBlur(grayScaledTriangles, grayScaledTriangles, Size(5,5), 30);

    // auto thres = getTrackbarPos("thres", "lines");
    // auto minLine = getTrackbarPos("Min Line Length", "lines");
    // auto maxLineGap = getTrackbarPos("Max Line Gap", "lines");

    Canny(grayScaledTriangles, edges, 50, 200);
    cvtColor(edges, lines, COLOR_GRAY2BGR);
    
    //std::cout << thres << std::endl;
    std::vector<Vec4i> hough_lines;
    HoughLinesP(edges, hough_lines, 1, CV_PI/180, thres, minline, maxgap);

    addLines(hough_lines, triangles);

    showImage("lines", triangles);
}

void createTrackbars(const char* winName)
{
    //createTrackbar("Threshold", winName, &thres, 300, on_trackbar);
    createTrackbar("Min Line Length", winName, &minline, 300, on_trackbar);
    //createTrackbar("Max Line Gap", winName, &maxgap, 300, on_trackbar);
}

void showImage(const char* name, Mat& image, bool track)
{
    namedWindow(name);
    if (track)
        createTrackbars(name);
    imshow(name, image);
    waitKey();
}
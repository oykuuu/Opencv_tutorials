#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void show_image(Mat &img)
{
    /* Shows image
    img
       cv::Mat, input image
    */
    string name = "image";
    namedWindow(name);
    imshow(name, img);
    waitKey();
}

Mat sobel_filter(Mat &img, Mat &sobel_x, Mat &sobel_y)
{
    /* Convolution with Sobel filter to detect edges
    img
        cv::Mat, input image
    sobel_x
        cv::Mat, sobel filter for derivate along x direction
    sobel_y
        cv::Mat, sobel filter for derivate along y direction
    */
    Mat sobel(3, 3, CV_32FC1, &sobel_x);
    Mat output(img.size(), CV_32FC1);
    Mat padded;
    Mat rect_img;
    float val_x, val_y;
    copyMakeBorder(img, padded, 1, 1, 1, 1, BORDER_REPLICATE);
    for(int i = 1; i < img.rows-1; ++i)
    {
        for(int j = 1; j < img.cols-1; ++j)
        {
            rect_img = padded(Rect(j-1, i-1, 3, 3));
            val_x = rect_img.dot(sobel_x);
            val_y = rect_img.dot(sobel_y);
            output.at<float>(i,j) = sqrt(pow(val_x, 2) + pow(val_y, 2));
        }
    }
    return output;
}

int main()
{
    Mat image;
    image = imread("images/lenna.jpg", IMREAD_GRAYSCALE);
    image.convertTo(image, CV_32FC1);

    float sobel_val[3][3] = {{1, 0, -1},{2, 0, -2},{1, 0, -1}};
    Mat filter_x(3,3,CV_32FC1, &sobel_val);
    Mat filter_y;
    transpose(filter_x, filter_y);

    Mat output = sobel_filter(image, filter_x, filter_y);
    image.convertTo(image, CV_8UC1);
    output.convertTo(output, CV_8UC1);
    hconcat(image, output, output);

    show_image(output);

    return 0;
}


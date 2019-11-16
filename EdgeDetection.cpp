#include <iostream>
#include <vector>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void show_image(Mat &img)
{
    string name = "image";
    namedWindow(name);
    imshow(name, img);
    waitKey();
}

Mat convolve(Mat &img, Mat &sobel_value)
{
    Mat sobel(3, 3, CV_8UC1, &sobel_value);
    Mat output(img.size(), 3, CV_8UC1);
    Mat padded;
    copyMakeBorder(img, padded, 1, 1, 1, 1, BORDER_REPLICATE);
    for(int i = 1; i < img.rows-1; ++i)
    {
        //uchar* padded_row_ptr = padded.ptr(i+1);
        for(int j = 1; j < img.cols-1; ++j)
        {
            // uchar col_ptr = row_ptr[j+1];
            Mat rect_img = padded(Rect(j-1, i-1, 3, 3));
            float val = rect_img.dot(sobel_value)/255;
            //cout << val << endl;
            if (val < 0)
                val = 0;
            if (val > 255)
                val = 255;
            output.at<float>(i,j) = val;
        }
    }
    return output;
}

int main()
{
    Mat image, image_color;
    image_color = imread("images/lenna.jpg", IMREAD_COLOR);
    //cvtColor(image_color, image_color, COLOR_BGR2GRAY);

    //double minVal, maxVal;
    //minMaxLoc(image_color, &minVal, &maxVal);
    //image_color.convertTo(image, CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));
    
    cout << image.size() << endl;
    cout << image.at<float>(149, 123) << endl;



    show_image(image);
    float sobel_val[3][3] = {{1, 0, -1},{2, 0, -2},{1, 0, -1}}; //Iy * Ix
    Mat filter(3,3,CV_8UC1, &sobel_val);
    Mat output = convolve(image, filter);
    show_image(output);
    cout << output.size() << endl;

    return 0;
}


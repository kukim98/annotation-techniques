#include <stdio.h>
#include <opencv2/opencv.hpp>


cv::Mat edgeDetection(cv::Mat image)
{
    cv::Mat img_gray;
    cvtColor(image, img_gray, cv::COLOR_BGR2GRAY);
    // apply binary thresholding
    cv::Mat thresh;
    cv::threshold(img_gray, thresh, 100, 255, cv::THRESH_BINARY);

    // detect the contours on the binary image using cv2.CHAIN_APPROX_NONE
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(thresh, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
    // draw contours on the original image
    cv::Mat image_copy = image.clone();
    cv::drawContours(image_copy, contours, -1, cv::Scalar(0, 255, 0), 2);
    return image_copy;
}
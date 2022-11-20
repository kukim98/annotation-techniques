#include <stdio.h>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    cv::Mat image;
    image = imread( argv[1], cv::IMREAD_UNCHANGED );
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }

    // convert image to grayscale
    cv::Mat image_gray;
    cv::cvtColor(image, image_gray, cv::COLOR_BGR2GRAY);

    // onvert image to blck and white
    cv::Mat thresh;
    cv::threshold(image_gray, thresh, 100, 255, cv::THRESH_BINARY);

    // create canvas
    cv::Mat canvas = cv::Mat::zeros(cv::Size(image.cols,image.rows), CV_8UC1);

    // create background mask
    cv::Mat mask = cv::Mat::zeros(cv::Size(image.cols,image.rows), CV_8UC1);

    // create new background
    cv::Mat new_background = cv::Mat::zeros(cv::Size(image.cols,image.rows), CV_8UC1);

    // get all contours
    std::vector<std::vector<cv::Point>> contours_draw;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(thresh, contours_draw, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    // get most significant contours
    std::vector<std::vector<cv::Point>> contours_mask;
    cv::findContours(thresh, contours_mask, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

    // draw all contours
    // cv::drawContours(canvas, contours_draw, 1, (0, 0, 0), 3)

    // contours traversal
    for (size_t i = 0; i < contours_draw.size(); i++)
    {
        // draw current contour
        cv::drawContours(canvas, contours_draw, i, (0, 0, 0), 3);
    }
    // most significant contours traversal
    for (size_t i = 0; i < contours_mask.size(); i++)
    {
        // create mask
        if (i != 1)
        {
            cv::fillConvexPoly(mask, contours_mask[i], (0, 0, 0));
        }

        // create background
        if (i != 1)
        {
            cv::fillConvexPoly(new_background, contours_mask[i], (0, 255, 0));
        }
    }

    // display the image in a window
    cv::imshow("Original", image);
    cv::imshow("Contours", canvas);
    cv::imshow("Background mask", mask);
    cv::imshow("New background", new_background);
    cv::Mat result;
    cv::bitwise_and(image, new_background, result);
    cv::imshow("Output", result);

    // escape condition
    cv::waitKey(0);

    // clean up windows
    cv::destroyAllWindows();
}

#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "EdgeDetection.hpp"


int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    cv::Mat image;
    image = cv::imread( argv[1], 1 );
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    cv::Mat edges;
    cv::Canny(image, edges, 100, 200);
    cv::imshow("Canny Edge", edges);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}
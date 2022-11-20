#include <stdio.h>
#include <opencv2/opencv.hpp>

#include "EdgeDetection.hpp"

using namespace std;
using namespace cv;
int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    Mat image;
    image = imread( argv[1], 1 );
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    // convert the image to grayscale format
    Mat reformed;
    reformed = edgeDetection(image);
    imshow("None approximation", reformed);
    waitKey(0);
    destroyAllWindows();
    return 0;
}
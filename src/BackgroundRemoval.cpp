#include <stdio.h>
#include <random>
#include <opencv2/opencv.hpp>


int computeMedian(std::vector<int> elements) 
{
  nth_element(elements.begin(), elements.begin()+elements.size()/2, elements.end());
 
  //sort(elements.begin(),elements.end());
  return elements[elements.size()/2];
}
 
cv::Mat compute_median(std::vector<cv::Mat> vec) 
{
  // Note: Expects the image to be CV_8UC3
  cv::Mat medianImg(vec[0].rows, vec[0].cols, CV_8UC3, cv::Scalar(0, 0, 0));
 
  for(int row=0; row<vec[0].rows; row++) 
  {
    for(int col=0; col<vec[0].cols; col++) 
    {
      std::vector<int> elements_B;
      std::vector<int> elements_G;
      std::vector<int> elements_R;
 
      for(int imgNumber=0; imgNumber<vec.size(); imgNumber++) 
      {
        int B = vec[imgNumber].at<cv::Vec3b>(row, col)[0];
        int G = vec[imgNumber].at<cv::Vec3b>(row, col)[1];
        int R = vec[imgNumber].at<cv::Vec3b>(row, col)[2];
 
        elements_B.push_back(B);
        elements_G.push_back(G);
        elements_R.push_back(R);
      }
 
      medianImg.at<cv::Vec3b>(row, col)[0]= computeMedian(elements_B);
      medianImg.at<cv::Vec3b>(row, col)[1]= computeMedian(elements_G);
      medianImg.at<cv::Vec3b>(row, col)[2]= computeMedian(elements_R);
    }
  }
  return medianImg;
}

int main(int argc, char const *argv[])
{
  // // Read video file
  // if ( argc != 2 )
  // {
  //     printf("usage: DisplayImage.out <Image_Path>\n");
  //     return -1;
  // }

  std::vector<cv::String> fn;
  // std::strcat(argv[1], "/*")
  cv::glob(argv[1], fn, false);
  std::vector<cv::Mat> images;
  size_t count = fn.size(); //number of png files in images folder
  if ( count == 0 )
  {
      printf("No image data \n");
      return -1;
  }
  std::default_random_engine generator;
  std::uniform_int_distribution<int>distribution(0, count);
  for (size_t i=0; i<100; i++)
  {
    int fid = distribution(generator);
    cv::Mat item = cv::imread(fn[fid]);
    if (item.empty())
      continue;
    images.push_back(item);
  }

  // Calculate the median along the time axis
  cv::Mat medianFrame = compute_median(images);
 
  // Display median frame
  cv::imshow("frame", medianFrame);
  cv::waitKey(0);

  cv::Mat grayBack;
  cv::cvtColor(medianFrame, grayBack, cv::COLOR_BGR2GRAY);
  int k = distribution(generator);
  cv::Mat frame = cv::imread(fn[k]);
  std::cout << k << std::endl;
  // Convert current frame to grayscale
  cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
 
  // Calculate absolute difference of current frame and the median frame
  cv::Mat dframe;
  absdiff(frame, grayBack, dframe);
 
  // Threshold to binarize
  threshold(dframe, dframe, 30, 255, cv::THRESH_BINARY);
 
  // Display Image
  cv::imshow("frame", dframe);
  cv::waitKey(0);
}
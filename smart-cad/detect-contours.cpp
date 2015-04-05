// 

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

void findCountours(Mat src)
{
  Mat src_gray;
  /// Convert image to gray and blur it
  cvtColor( src, src_gray, CV_BGR2GRAY );
  blur( src_gray, src_gray, Size(4,4) );

  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  /// Detect edges using canny
  Canny( src_gray, canny_output, thresh, thresh*2, 3 );
  /// Find contours
  findContours( canny_output, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Draw contours
  RNG rng(12345);
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  for( int i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
     }
  fprintf(stderr, "Found %d contours\n", contours.size());

  /// Show in a window
  namedWindow( "Contours", CV_WINDOW_NORMAL );
  imshow( "Contours", drawing );
}

/** @function main */
int main( int argc, char** argv )
{
    Mat src;

    int thresh = 100;

    src = imread( argv[1], 1 );





    while (1) {
        waitKey(0);
    }
    return(0);
}



// Idea is to automatically detect holes (for screws bolts) in images used for reference
// when modelling replacement or connecting parts
// Based on http://docs.opencv.org/doc/tutorials/imgproc/imgtrans/hough_circle/hough_circle.html

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <unistd.h>

using namespace cv;

/** @function main */

void
visualize_circles(Mat src, vector<Vec3f> circles)
{

  /// Draw the circles detected
  for( size_t i = 0; i < circles.size(); i++ )
  {
      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);
      // circle center
      circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );
      // circle outline
      circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );
   }

  /// Show your results
  namedWindow( "Hough Circle Transform Demo", CV_WINDOW_NORMAL );
  imshow( "Hough Circle Transform Demo", src );

  while (1) {
    waitKey(0);
  }

}

void
print_output(vector<Vec3f> circles)
{
    for (int i=0; i<circles.size(); i++) {
        Vec3f &c = circles[i];
        fprintf(stdout, "circle %f %f %f\n", c[0], c[1], c[2]); // x,y,radius
    }
}

int main(int argc, char** argv)
{
  Mat src, src_gray;

  /// Read the image
  src = imread( argv[1], 1 );

  if( !src.data )
    { return -1; }

  /// Convert it to gray
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Reduce the noise so we avoid false circle detection
  GaussianBlur( src_gray, src_gray, Size(9, 9), 3, 3 );

  vector<Vec3f> circles;

  /// Apply the Hough Transform to find the circles
  HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/16, 150, 30, 0, 0 );

  fprintf(stderr, "found %d circles\n", circles.size());
  
  print_output(circles);
//  visualize_circles(src, circles);

  return 0;
}

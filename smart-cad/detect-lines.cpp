#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

void help()
{
 cout << "\nThis program demonstrates line finding with the Hough transform.\n"
         "Usage:\n"
         "./houghlines <image_name>, Default is pic1.jpg\n" << endl;
}

int main(int argc, char** argv)
{
 const char* filename = argc >= 2 ? argv[1] : "pic1.jpg";

 Mat src = imread(filename, 0);
 if(src.empty())
 {
     help();
     cout << "can not open " << filename << endl;
     return -1;
 }

 Mat src_gray, blurred, edges;

 cvtColor(src, src_gray, CV_GRAY2BGR);
 blur(src_gray, blurred, Size(3,3) );
 Canny(blurred, edges, 50, 200, 3);

  vector<Vec4i> lines;
  const float threshold = 50;
  HoughLinesP(edges, lines, 1, CV_PI/180, threshold, 30, 10 );
  for( size_t i = 0; i < lines.size(); i++ )
  {
    Vec4i l = lines[i];
    line(src, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
  }

 imshow("detected lines", src);

 waitKey();

 return 0;
}

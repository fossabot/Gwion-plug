#include <cv.hpp>

#include "loup.hpp"
#include "fx.hpp"
#include "vaisseau.hpp"

void Vaisseau::run(Loup* loup, Mat mat) {
  int width = 640;
  int height = 480;
  int x = 0;
  int y = 0;


  Mat m = Mat::zeros(mat.size(), mat.type());
  //Point2f p[4], q[4];
  std::vector<Point2f> p(4);
  std::vector<Point2f> q(4);
  int i;
  for(i = 0; i < 10; i++) {

    p[0].x = x;     p[0].y = y;
    p[1].x = width; p[1].y = y;
    p[2].x = x;     p[2].y = height;
    p[3].x = width;     p[3].y = height;

    x += 5; y += 5;
    width -= 5; height -= 5;
    q[0].x = x;     q[0].y = y;
    q[1].x = width; q[1].y = y;
    q[2].x = x;     q[2].y = height;
    q[3].x = width;     q[3].y = height;

    Mat H = findHomography(p, q); //get homography
Size warped_image_size = Size(cvRound(q[2].x), cvRound(q[2].y));
    
    Mat warped_image;
    warpPerspective(mat, warped_image, H, mat.size()); // do perspective transformation
    //warpPerspective(mat, warped_image, H, warped_image_size); // do perspective transformation
    addWeighted(warped_image, .9, m, .9, 0, m); 
  }
  imshow("Warped Image", m);

}

#include <cv.h>
#include "type.h"
#include "object.h"
#include "cvcam.h"
#include "vaisseau.h"

struct Vaisseau_ {
  IplImage* img;
  CvMat* mat;
};

Vaisseau vaisseau_ini(IplImage* base) {
  Vaisseau vs = malloc(sizeof(struct Vaisseau_));
  CvSize size = cvSize(base->width, base->height);
  vs->img = cvCreateImage(size, CV_DEPTH, base->nChannels);
  vs->mat = cvCreateMat(3, 3, CV_32FC1);
  return vs;
}

void vaisseau_run(Vaisseau vs, M_Object o) {
  IplImage* base = BASE(o);
  /// Generate grad_x
  /*IplImage* grad_x = cvCreateImage(cvGetSize(base), IPL_DEPTH_16S, 1);*/
 cvShowImage("Bacjground", bg); 
IplImage* grad_x = cvCreateImage(cvGetSize(base), IPL_DEPTH_8U, base->nChannels);
IplImage* abs_grad_x = cvCreateImage(cvGetSize(base), 8, base->nChannels);

IplImage* _bg = cvCreateImage(cvGetSize(base), IPL_DEPTH_8U, base->nChannels);
/*cvMask(_bg, bg);*/
cvCopy(base, _bg, bg);
/*cvNot(bg, _bg);*/

 
 
 cvApplyColorMap(_bg, _bg, 1);
 
 cvShowImage("Bacjground2", _bg); 

 
 /// Gradient X
cvSobel(base, grad_x, 1, 0, 3);
cvConvertScaleAbs(grad_x, abs_grad_x, 1, 0);
/*cvThreshold(abs_grad_x, abs_grad_x, 0, 255, CV_THRESH_BINARY|CV_THRESH_OTSU);*/
 cvShowImage("Gradix", grad_x); 
cvAddWeighted(grad_x, .5, base, .5, 0, base);
  CvPoint2D32f  in[4];
  CvPoint2D32f out[4];
  CvScalar scalar = cvScalar(0, 0, 0, 255);

  in[0].x = 0;
  in[0].y = 0;

  in[1].x = CV_WIDTH;
  in[1].y = 0;

  in[2].x = 0;
  in[2].y = CV_HEIGHT;

  in[3].x = CV_WIDTH;
  in[3].y = CV_HEIGHT;

  out[0].x = 35 + X(o);
  out[0].y = 70 + Y(o);

  out[1].x = - 35 + CV_WIDTH + X(o);
  out[1].y = 70 + Y(o);

  out[2].x = 35 + X(o);
  out[2].y = - 70 + CV_HEIGHT+ Y(o);

  out[3].x = - 35 + 640 + X(o);
  out[3].y = - 70 + CV_HEIGHT + Y(o);

  cvCopy(base, vs->img, NULL);
  cvGetPerspectiveTransform(in, out, vs->mat);

  for(int i = 0; i < X(o); i++) {
    cvWarpPerspective(vs->img, vs->img, vs->mat, CV_FILL, scalar);
    cvAddWeighted(vs->img, i/10.0, base, 1 - (i/10.0), 0, vs->img);
  }
  cvAddWeighted(vs->img, 1, base, 1, 0, base); 
}

void vaisseau_del(Vaisseau vs) {
  cvReleaseImage(&vs->img);
  cvReleaseMat(&vs->mat);
  free(vs);
}

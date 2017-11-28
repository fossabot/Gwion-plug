#include <cv.h>
#include "type.h"
#include "object.h"
#include "cvcam.h"
#include "trounoir.h"

struct TrouNoir_ {
  IplImage* visuel;
  IplImage* cercle;
  CvPoint   centre;
};

TrouNoir trounoir_ini(IplImage* base) {
  TrouNoir tn = malloc(sizeof(struct TrouNoir_));
  CvSize size = cvSize(base->width, base->height);
  tn->visuel  = cvCreateImage(size, CV_DEPTH, base->nChannels);
  tn->cercle  = cvCreateImage(size, CV_DEPTH, base->nChannels);
  tn->centre  = cvPoint(base->width/2, base->height/2);
  return tn;
}

void trounoir_run(TrouNoir tn, M_Object o) {
  cvCopy(BASE(o), tn->visuel, NULL);
  cvZero(BASE(o));
  cvZero(tn->cercle);
  cvCircle(tn->cercle, tn->centre,
      CV_WIDTH/15   * SCALE(o), cvScalar(255,255,255,0), 
      CV_WIDTH*1.15 * SCALE(o), 8, 0 );
  cvCopy(tn->visuel, BASE(o), tn->cercle);
} 

void trounoir_del(TrouNoir tn) {
  cvReleaseImage(&tn->visuel);
  cvReleaseImage(&tn->cercle);
  free(tn);
}



#include <cv.h>
#include <highgui.h>
#include "opencv2/videoio/videoio_c.h"
#include "type.h"
#include "instr.h"
#include "import.h"

// project specific
#include "cvcam.h"
#include "vaisseau.h"
#include "trounoir.h"

static struct Type_ t_cvcam = { "CvCam", SZ_INT, &t_object };
m_int o_cvcam_cam;
m_int o_cvcam_base;
m_int o_cvcam_thread;
m_int o_cvcam_running;
m_int o_cvcam_scale;
m_int o_cvcam_show;

m_int o_cvcam_trounoir;
m_int o_cvcam_x;
m_int o_cvcam_y;

static void* cvcam_process(void* data) {
  M_Object o = (M_Object)data;
  int iter;
  IplImage* base = cvQueryFrame(CAM(o)); // get frame
  CvSize size = cvSize(base->width, base->height);
  bg = cvCreateImage(size, CV_DEPTH, base->nChannels);
  cvCopy(base, bg, NULL);
  cvNot(bg, bg);
  Vaisseau vs = vaisseau_ini(base);
  TrouNoir tn = trounoir_ini(base);
_
  while(RUNNING(o)) {
    base = BASE(o) = cvQueryFrame(CAM(o)); // get frame
    if(*(m_int*)(o->data + o_cvcam_show)) {
      vaisseau_run(vs, o);
      if(TROUNOIR(o))
        trounoir_run(tn, o);
    } else
      cvZero(base);
    cvShowImage("Base", base); // show frame
    cvWaitKey(CV_WAIT);
  }
  /*cvDestroyWindow("Base");*/
  trounoir_del(tn);
  vaisseau_del(vs);
  cvReleaseCapture(&CAM(o));
  return NULL;
}

CTOR(cvcam_ctor) {
  CAM(o) = cvCaptureFromCAM(0);
  cvSetCaptureProperty(CAM(o), CV_CAP_PROP_FRAME_WIDTH, CV_WIDTH);
  cvSetCaptureProperty(CAM(o), CV_CAP_PROP_FRAME_HEIGHT, CV_HEIGHT);

  cvNamedWindow("Base", CV_WINDOW_OPENGL); // create window
  /*cvSetWindowProperty("Base", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);*/
  pthread_create(&THREAD(o), NULL, cvcam_process, o);
  SCALE(o)   = 1;
  RUNNING(o) = 1;
}

static DTOR(cvcam_dtor) {
  RUNNING(o) = 0;
  /*pthread_cancel(THREAD(o));*/
  pthread_join(THREAD(o), NULL);

}

IMPORT {
  CHECK_BB(importer_class_ini(importer, &t_cvcam,cvcam_ctor, cvcam_dtor))

  CHECK_BB(importer_item_ini(importer, "int",  "@cam"))
  CHECK_BB((o_cvcam_cam = importer_item_end(importer, ae_flag_member, NULL)))
  CHECK_BB(importer_item_ini(importer, "int",  "@base"))
  CHECK_BB((o_cvcam_base = importer_item_end(importer, ae_flag_member, NULL)))
  CHECK_BB(importer_item_ini(importer, "float",  "@thread"))
  CHECK_BB((o_cvcam_thread = importer_item_end(importer, ae_flag_member, NULL)))
  CHECK_BB(importer_item_ini(importer, "float",  "running"))
  CHECK_BB((o_cvcam_running = importer_item_end(importer, ae_flag_member, NULL)))
  CHECK_BB(importer_item_ini(importer, "int",  "trounoir"))
  CHECK_BB((o_cvcam_trounoir = importer_item_end(importer, ae_flag_member, NULL)))
  CHECK_BB(importer_item_ini(importer, "float",  "x"))
  CHECK_BB((o_cvcam_x = importer_item_end(importer, ae_flag_member, NULL)))
  CHECK_BB(importer_item_ini(importer, "float",  "y"))
  CHECK_BB((o_cvcam_y = importer_item_end(importer, ae_flag_member, NULL)))
  CHECK_BB(importer_item_ini(importer, "float",  "scale"))
  CHECK_BB((o_cvcam_scale = importer_item_end(importer, ae_flag_member, NULL)))
  CHECK_BB(importer_item_ini(importer, "int",  "show"))
  CHECK_BB((o_cvcam_show = importer_item_end(importer, ae_flag_member, NULL)))

  CHECK_BB(importer_class_end(importer))
  return 1;
}

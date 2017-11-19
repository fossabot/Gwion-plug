
#include <cv.h>
#include <highgui.h>
#include "type.h"
#include "instr.h"
#include "import.h"
//#include "err_msg.h"
//#include "lang.h"
//#include "ugen.h"

static struct Type_ t_cvcam = { "CvCam", SZ_INT, &t_object };
// TODO: put in member var
static CvCapture* cap;
static pthread_t cvcam_thread;
static int is_running = 1;
m_int o_cvcam_angle;
m_int o_cvcam_scale;
m_int o_cvcam_show;
m_int o_cvcam_x;
m_int o_cvcam_y;

static void* cvcam_process(void* data) {
  M_Object o = (M_Object)data;
  int iter;
  CvMat *map = cvCreateMat( 2, 3, CV_32FC1 );
    IplImage* base = cvQueryFrame(cap); // get frame

    CvPoint2D32f center;
    center.x = base->width/2.0f;
    center.y = base->height/2.0f;
//    center.y = base->width;
//center.x = base->width;

//  sleep(10);
  while(is_running) {
    base = cvQueryFrame(cap); // get frame

    IplImage *rot  = cvCreateImage(cvSize(base->width,base->height), IPL_DEPTH_8U, base->nChannels);

//float x = base->width;
//float x = 0.0f;
//float y = 0.0f;
//float y = base->height;
if(*(m_int*)(o->data + o_cvcam_show)) {
cv2DRotationMatrix(center, (*(m_float*)(o->data + o_cvcam_angle)), *(m_float*)(o->data + o_cvcam_scale), map);
//cvmSet(map,0,1,y);
cvmSet(map, 1, 1, *(m_float*)(o->data + o_cvcam_x));
//cvmSet(map, 0, 1, *(m_float*)(o->data + o_cvcam_x));

//cvmSet(map, 0, 1, *(m_float*)(o->data + o_cvcam_y));

//cvmSet(map, 0, 1, 0.5);
//cvmSet(map, 1, 2, x);
cvWarpAffine(base, rot, map, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS, cvScalarAll(0));
//cvWarpAffine(base, rot, map, CV_INTER_LINEAR, cvScalarAll(0));
//
}
       if(base != 0)
//           cvShowImage("Video", base); // show frame
//           cvShowImage("Video", rot); // show frame
        cvShowImage("Rotated", rot); // show frame
        char c = cvWaitKey(10); // wait 10 ms or for key stroke
        if(c == 27)
            break; // if ESC, break and quit

  //sleep(1);

  }
//  cvReleaseMat(&map);
//  cvReleaseImage(&rot);
  return NULL;
}




CTOR(cvcam_ctor) {
  cap = cvCaptureFromCAM(0);
//  cvNamedWindow("Video", CV_WINDOW_NORMAL); // create window
  cvNamedWindow("Rotated", CV_WINDOW_NORMAL); // create window
//  cvSetWindowProperty("Rotated", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
  pthread_create(&cvcam_thread, NULL, cvcam_process, o);
// *(m_float*)(o->data + o_cvcam_x) = 0.5;
 *(m_float*)(o->data + o_cvcam_scale) = 0.5;
}

void* cvcam_dtor_process(void* data) {
  is_running = 0;
  pthread_cancel(cvcam_thread);
  pthread_join(cvcam_thread, NULL);
  cvReleaseCapture(&cap);
}

DTOR(cvcam_dtor) {
  pthread_t thread;
  pthread_create(&thread, NULL, cvcam_dtor_process, NULL);
}


m_int o_cvcam_member_data;
m_int o_cvcam_static_data;
m_int* cvcam_static_value;

static MFUN(mfun) { /*code here */ }
static SFUN(sfun) { /*code here */ }

IMPORT
{
  CHECK_BB(importer_class_ini(importer, &t_cvcam,cvcam_ctor, cvcam_dtor))

  CHECK_BB(importer_item_ini(importer, "float",  "x"))
  CHECK_BB((o_cvcam_x = importer_item_end(importer, ae_flag_member, NULL)))
  CHECK_BB(importer_item_ini(importer, "float",  "y"))
  CHECK_BB((o_cvcam_y = importer_item_end(importer, ae_flag_member, NULL)))
  CHECK_BB(importer_item_ini(importer, "float",  "angle"))
  CHECK_BB((o_cvcam_angle = importer_item_end(importer, ae_flag_member, NULL)))
  CHECK_BB(importer_item_ini(importer, "float",  "scale"))
  CHECK_BB((o_cvcam_scale = importer_item_end(importer, ae_flag_member, NULL)))
  CHECK_BB(importer_item_ini(importer, "float",  "show"))
  CHECK_BB((o_cvcam_show = importer_item_end(importer, ae_flag_member, NULL)))

  cvcam_static_value = malloc(sizeof(m_int));
  CHECK_BB(importer_item_ini(importer, "int", "static"))
  CHECK_BB(o_cvcam_static_data = importer_item_end(importer, ae_flag_static, cvcam_static_value))

  CHECK_BB(importer_func_ini(importer, "int", "mfun",  (m_uint)mfun))
  CHECK_BB(importer_func_arg(importer, "int", "arg"))
  CHECK_BB(importer_func_end(importer, ae_flag_member))

  CHECK_BB(importer_func_ini(importer, "int", "sfun",  (m_uint)sfun))
  CHECK_BB(importer_func_arg(importer, "int", "arg"))
  CHECK_BB(importer_func_end(importer, ae_flag_static))

  CHECK_BB(importer_class_end(importer))
  return 1;
}

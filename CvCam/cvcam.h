#define CV_DEPTH IPL_DEPTH_8U
#define CV_FILL  CV_WARP_FILL_OUTLIERS
#define CV_WAIT  10
#define CV_WIDTH  480
#define CV_HEIGHT 640

extern m_int o_cvcam_cam;
extern m_int o_cvcam_base;
extern m_int o_cvcam_thread;
extern m_int o_cvcam_running;
extern m_int o_cvcam_scale;
extern m_int o_cvcam_show;

extern m_int o_cvcam_trounoir;
extern m_int o_cvcam_x;
extern m_int o_cvcam_y;

IplImage* bg;



#define CAM(o)      (*(CvCapture**) (o->data + o_cvcam_cam))
#define BASE(o)     (*(IplImage**)  (o->data + o_cvcam_base))
#define THREAD(o)   (*(pthread_t*)  (o->data + o_cvcam_thread))
#define RUNNING(o)  (*(m_int*)      (o->data + o_cvcam_running))
#define TROUNOIR(o) (*(m_int*)      (o->data + o_cvcam_trounoir))
#define SCALE(o)    (*(m_float*)    (o->data + o_cvcam_scale))
#define X(o)        (*(m_float*)    (o->data + o_cvcam_x))
#define Y(o)        (*(m_float*)    (o->data + o_cvcam_y))


typedef struct TrouNoir_* TrouNoir;

TrouNoir trounoir_ini(IplImage* base);
void     trounoir_run(TrouNoir tn, M_Object o);
void     trounoir_del(TrouNoir tn);

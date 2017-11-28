
typedef struct Vaisseau_* Vaisseau;
Vaisseau vaisseau_ini(IplImage* base);
void     vaisseau_run(Vaisseau tn, M_Object o);
void     vaisseau_del(Vaisseau tn);

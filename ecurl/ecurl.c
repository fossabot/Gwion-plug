#include "type.h"
#include "instr.h"
#include "import.h"

static struct Type_ t_ecurl = { "ECurl", SZ_INT, &t_object };
m_int o_ecurl_obj, o_ecurl_len;
#define ECURL_OBJ(o) *((M_Object*(o->data + o_ecurl_obj)))
#define ECURL_LEN(o) *((M_Object*(o->data + o_ecurl_len)))
CTOR(ecurl_ctor) { 
  ECURL_OBJ(o) = curl_easy_init();
  ECURL_LEN(o) = 256; 
}

DTOR(ecurl_dtor) {
  curl_easy_cleanup(ECURL_OBJ(o));
}

static MFUN(ecurl_perform) {
  *(m_int*)RETURN = curl_easy_perform(ECURL_OBJ(o));
}

static MFUN(ecurl_dup) {
  M_Object obj = new_M_Object;
  initialize_object(obj, &tecurl);
  ECURL_OBJ(obj) = curl_easy_duphandle(ECURL_OBJ(o));
  *(M_Object*)RETURN = obj;
}

static MFUN(ecurl_reset) {
  curl_easy_reset(ECURL_OBJ(o));
}

static MFUN(ecurl_recv) {
  size_t n;
  char buf[ECURL_LEN(o)];
  *(m_int)RETURN = curl_easy_recv(ECURL_OBJ(o), buf, ECURL_LEN(o), &n);
  *(M_Object*)RETURN = n ? new_String(shred, buf) : NULL;
}

static MFUN(ecurl_send) {
  size_t n;
  char buf[ECURL_LEN(o)];
  *(m_int)RETURN = curl_easy_send(ECURL_OBJ(o), buf, ECURL_LEN(o), &n);
  *(M_Object*)RETURN = n ? new_String(shred, buf) : NULL;
}

IMPORT
 {
  CHECK_BB(importer_class_ini(importer, &t_ecurl,ecurl_ctor, ecurl_dtor))

  CHECK_BB(importer_item_ini(importer, "int",  "@ecurl_obj"))
  CHECK_BB(o_ecurl_obj = importer_item_end(importer, ae_flag_member, NULL))

  CHECK_BB(importer_item_ini(importer, "int",  "size"))
  CHECK_BB(o_ecurl_len = importer_item_end(importer, ae_flag_member, NULL))
  
  CHECK_BB(importer_func_ini(importer, "int", "perform", (m_uint)ecurl_perform))
  CHECK_BB(importer_func_end(importer, ae_flag_member))

  CHECK_BB(importer_func_ini(importer, "ECurl", "dup",  (m_uint)ecurl_dup))
  CHECK_BB(importer_func_end(importer, ae_flag_member))
  
  CHECK_BB(importer_func_ini(importer, "int", "reset", (m_uint)ecurl_reset))
  CHECK_BB(importer_func_end(importer, ae_flag_member))

  CHECK_BB(importer_func_ini(importer, "int", "recv", (m_uint)ecurl_recv))
  CHECK_BB(importer_func_end(importer, ae_flag_member))
  
  CHECK_BB(importer_func_ini(importer, "int", "send", (m_uint)ecurl_sznd))
  CHECK_BB(importer_func_end(importer, ae_flag_member))
  
  CHECK_BB(importer_class_end(importer))
  return 1;
}

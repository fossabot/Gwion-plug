#include "type.h"
#include "instr.h"
#include "import.h"

static struct Type_ t_inotify_wrap = { "inotify_wrap", SZ_INT, &t_object };
static struct Type_ t_inotify_event = { (m_str)"inotify_event", SZ_INT, &t_object };
static m_int o_inotify_event_swig;
#define GW_inotify_event(a) *(void**)(o->data + o_inotify_event_swig)
static MFUN(gw_inotify_event_wd_set) {
  m_uint offset = SZ_INT;
  struct inotify_event *arg1 = (struct inotify_event *) 0 ;
  int arg2 ;
  int result;
  
  arg1 = (inotify_event*)GW_inotify_event(o);
  arg2 = (int)*(m_int*)MEM(offset);
  offset += SZ_INT;
  result = arg2;
  if (arg1) (arg1)->wd = arg2;
  *(m_int*)RETURN = (m_int)result;
}


static MFUN(gw_inotify_event_wd_get) {
  struct inotify_event *arg1 = (struct inotify_event *) 0 ;
  int result;
  
  arg1 = (inotify_event*)GW_inotify_event(o);
  result = (int) ((arg1)->wd);
  *(m_int*)RETURN = (m_int)result;
}


static MFUN(gw_inotify_event_mask_set) {
  m_uint offset = SZ_INT;
  struct inotify_event *arg1 = (struct inotify_event *) 0 ;
  uint32_t arg2 ;
  uint32_t result;
  
  arg1 = (inotify_event*)GW_inotify_event(o);
  arg2 = (unsigned int)*(m_uint*)MEM(offset);
  offset += SZ_INT;
  result = arg2;
  if (arg1) (arg1)->mask = arg2;
  *(m_int*)RETURN = (m_int)result;
}


static MFUN(gw_inotify_event_mask_get) {
  struct inotify_event *arg1 = (struct inotify_event *) 0 ;
  uint32_t result;
  
  arg1 = (inotify_event*)GW_inotify_event(o);
  result =  ((arg1)->mask);
  *(m_int*)RETURN = (m_int)result;
}


static MFUN(gw_inotify_event_cookie_set) {
  m_uint offset = SZ_INT;
  struct inotify_event *arg1 = (struct inotify_event *) 0 ;
  uint32_t arg2 ;
  uint32_t result;
  
  arg1 = (inotify_event*)GW_inotify_event(o);
  arg2 = (unsigned int)*(m_uint*)MEM(offset);
  offset += SZ_INT;
  result = arg2;
  if (arg1) (arg1)->cookie = arg2;
  *(m_int*)RETURN = (m_int)result;
}


static MFUN(gw_inotify_event_cookie_get) {
  struct inotify_event *arg1 = (struct inotify_event *) 0 ;
  uint32_t result;
  
  arg1 = (inotify_event*)GW_inotify_event(o);
  result =  ((arg1)->cookie);
  *(m_int*)RETURN = (m_int)result;
}


static MFUN(gw_inotify_event_len_set) {
  m_uint offset = SZ_INT;
  struct inotify_event *arg1 = (struct inotify_event *) 0 ;
  uint32_t arg2 ;
  uint32_t result;
  
  arg1 = (inotify_event*)GW_inotify_event(o);
  arg2 = (unsigned int)*(m_uint*)MEM(offset);
  offset += SZ_INT;
  result = arg2;
  if (arg1) (arg1)->len = arg2;
  *(m_int*)RETURN = (m_int)result;
}


static MFUN(gw_inotify_event_len_get) {
  struct inotify_event *arg1 = (struct inotify_event *) 0 ;
  uint32_t result;
  
  arg1 = (inotify_event*)GW_inotify_event(o);
  result =  ((arg1)->len);
  *(m_int*)RETURN = (m_int)result;
}


static MFUN(gw_inotify_event_name_set) {
  m_uint offset = SZ_INT;
  struct inotify_event *arg1 = (struct inotify_event *) 0 ;
  char *arg2 = (char *) 0 ;
  char *result = 0 ;
  
  arg1 = (inotify_event*)GW_inotify_event(o);
  M_Object arg2_obj = *(M_Object*)MEM(offset);
  arg2 = (char*)STRING(arg2_obj);
  offset += SZ_INT;
  result = arg2;
  {
    free(arg1->name);
    if (arg2) {
      arg1->name = (char *) malloc(strlen((const char *)arg2)+1);
      strcpy((char *)arg1->name, (const char *)arg2);
    } else {
      arg1->name = 0;
    }
  }
  *(M_Object*)RETURN = result ? new_String(shred, result) : NULL;
  release(arg2_obj, shred);
}


static MFUN(gw_inotify_event_name_get) {
  struct inotify_event *arg1 = (struct inotify_event *) 0 ;
  char *result = 0 ;
  
  arg1 = (inotify_event*)GW_inotify_event(o);
  result = (char *) ((arg1)->name);
  *(M_Object*)RETURN = result ? new_String(shred, result) : NULL;
}


static CTOR(gw_inotify_event_ctor) {
  struct inotify_event *result = 0 ;
  
  if(o->type_ref->xid == t_inotify_event.xid)GW_inotify_event(o) = malloc(sizeof(inotify_event));
}


static DTOR(gw_inotify_event_dtor) {
  if(GW_inotify_event(o)) {
    free(GW_inotify_event(o));
    GW_inotify_event(o) = NULL;
  }
}


static MFUN(gw_inotify_init) {
  int result;
  
  GW_inotify(o) =  (int)inotify_init();
  *(m_int*)RETURN = (m_int)result;
}


static MFUN(gw_inotify_init1) {
  m_uint offset = SZ_INT;
  int arg1 ;
  int result;
  
  arg1 = (int)*(m_int*)MEM(offset);
  offset += SZ_INT;
  GW_inotify(o) =  (int)inotify_init1(arg1);
  *(m_int*)RETURN = (m_int)result;
}


static MFUN(gw_inotify_add_watch) {
  m_uint offset = SZ_INT;
  int arg1 ;
  char *arg2 = (char *) 0 ;
  uint32_t arg3 ;
  int result;
  
  arg1 = (inotify*)GW_inotify(o);
  M_Object arg2_obj = *(M_Object*)MEM(offset);
  arg2 = (char*)STRING(arg2_obj);
  offset += SZ_INT;
  arg3 = (unsigned int)*(m_uint*)MEM(offset);
  offset += SZ_INT;
  result = (int)inotify_add_watch(arg1,(char const *)arg2,arg3);
  *(m_int*)RETURN = (m_int)result;
  release(arg2_obj, shred);
}


static SFUN(gw_inotify_rm_watch) {
  m_uint offset = SZ_INT;
  int arg1 ;
  int arg2 ;
  int result;
  
  arg1 = (int)*(m_int*)MEM(offset);
  offset += SZ_INT;
  arg2 = (int)*(m_int*)MEM(offset);
  offset += SZ_INT;
  result = (int)inotify_rm_watch(arg1,arg2);
  *(m_int*)RETURN = (m_int)result;
}


IMPORT {
  CHECK_BB(importer_class_ini(importer, &t_inotify_wrap, NULL, NULL))
  CHECK_BB(importer_class_ini(importer, &t_inotify_event, gw_inotify_event_ctor, gw_inotify_event_dtor));
  CHECK_BB(importer_item_ini(importer,"int", "@Swig_inotify_event_Object"))
  CHECK_BB((o_inotify_event_swig = importer_item_end(importer, ae_flag_member, NULL)))
  CHECK_BB(importer_func_ini(importer, "int", "wd", (m_uint)gw_inotify_event_wd_set))
  CHECK_BB(importer_func_arg(importer, "int", "arg1"))
  CHECK_BB(importer_func_end(importer, ae_flag_member))
  CHECK_BB(importer_func_ini(importer, "int", "wd", (m_uint)gw_inotify_event_wd_get))
  CHECK_BB(importer_func_end(importer, ae_flag_member))
  CHECK_BB(importer_func_ini(importer, "void", "mask", (m_uint)gw_inotify_event_mask_set))
  CHECK_BB(importer_func_arg(importer, "uint32_t", "arg1"))
  CHECK_BB(importer_func_end(importer, ae_flag_member))
  CHECK_BB(importer_func_ini(importer, "void", "mask", (m_uint)gw_inotify_event_mask_get))
  CHECK_BB(importer_func_end(importer, ae_flag_member))
  CHECK_BB(importer_func_ini(importer, "void", "cookie", (m_uint)gw_inotify_event_cookie_set))
  CHECK_BB(importer_func_arg(importer, "uint32_t", "arg1"))
  CHECK_BB(importer_func_end(importer, ae_flag_member))
  CHECK_BB(importer_func_ini(importer, "void", "cookie", (m_uint)gw_inotify_event_cookie_get))
  CHECK_BB(importer_func_end(importer, ae_flag_member))
  CHECK_BB(importer_func_ini(importer, "void", "len", (m_uint)gw_inotify_event_len_set))
  CHECK_BB(importer_func_arg(importer, "uint32_t", "arg1"))
  CHECK_BB(importer_func_end(importer, ae_flag_member))
  CHECK_BB(importer_func_ini(importer, "void", "len", (m_uint)gw_inotify_event_len_get))
  CHECK_BB(importer_func_end(importer, ae_flag_member))
  CHECK_BB(importer_func_ini(importer, "string", "name", (m_uint)gw_inotify_event_name_set))
  CHECK_BB(importer_func_arg(importer, "string", "arg1"))
  CHECK_BB(importer_func_end(importer, ae_flag_member))
  CHECK_BB(importer_func_ini(importer, "string", "name", (m_uint)gw_inotify_event_name_get))
  CHECK_BB(importer_func_end(importer, ae_flag_member))
  CHECK_BB(importer_class_end(importer));
  ALLOC_PTR(IN_ACCESS_value, m_int, 0x00000001);
  CHECK_BB(importer_item_ini(importer, "int", "IN_ACCESS"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_ACCESS_value))
  
  ALLOC_PTR(IN_MODIFY_value, m_int, 0x00000002);
  CHECK_BB(importer_item_ini(importer, "int", "IN_MODIFY"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_MODIFY_value))
  
  ALLOC_PTR(IN_ATTRIB_value, m_int, 0x00000004);
  CHECK_BB(importer_item_ini(importer, "int", "IN_ATTRIB"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_ATTRIB_value))
  
  ALLOC_PTR(IN_CLOSE_WRITE_value, m_int, 0x00000008);
  CHECK_BB(importer_item_ini(importer, "int", "IN_CLOSE_WRITE"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_CLOSE_WRITE_value))
  
  ALLOC_PTR(IN_CLOSE_NOWRITE_value, m_int, 0x00000010);
  CHECK_BB(importer_item_ini(importer, "int", "IN_CLOSE_NOWRITE"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_CLOSE_NOWRITE_value))
  
  ALLOC_PTR(IN_CLOSE_value, m_int, (0x00000008|0x00000010));
  CHECK_BB(importer_item_ini(importer, "int", "IN_CLOSE"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_CLOSE_value))
  
  ALLOC_PTR(IN_OPEN_value, m_int, 0x00000020);
  CHECK_BB(importer_item_ini(importer, "int", "IN_OPEN"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_OPEN_value))
  
  ALLOC_PTR(IN_MOVED_FROM_value, m_int, 0x00000040);
  CHECK_BB(importer_item_ini(importer, "int", "IN_MOVED_FROM"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_MOVED_FROM_value))
  
  ALLOC_PTR(IN_MOVED_TO_value, m_int, 0x00000080);
  CHECK_BB(importer_item_ini(importer, "int", "IN_MOVED_TO"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_MOVED_TO_value))
  
  ALLOC_PTR(IN_MOVE_value, m_int, (0x00000040|0x00000080));
  CHECK_BB(importer_item_ini(importer, "int", "IN_MOVE"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_MOVE_value))
  
  ALLOC_PTR(IN_CREATE_value, m_int, 0x00000100);
  CHECK_BB(importer_item_ini(importer, "int", "IN_CREATE"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_CREATE_value))
  
  ALLOC_PTR(IN_DELETE_value, m_int, 0x00000200);
  CHECK_BB(importer_item_ini(importer, "int", "IN_DELETE"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_DELETE_value))
  
  ALLOC_PTR(IN_DELETE_SELF_value, m_int, 0x00000400);
  CHECK_BB(importer_item_ini(importer, "int", "IN_DELETE_SELF"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_DELETE_SELF_value))
  
  ALLOC_PTR(IN_MOVE_SELF_value, m_int, 0x00000800);
  CHECK_BB(importer_item_ini(importer, "int", "IN_MOVE_SELF"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_MOVE_SELF_value))
  
  ALLOC_PTR(IN_UNMOUNT_value, m_int, 0x00002000);
  CHECK_BB(importer_item_ini(importer, "int", "IN_UNMOUNT"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_UNMOUNT_value))
  
  ALLOC_PTR(IN_Q_OVERFLOW_value, m_int, 0x00004000);
  CHECK_BB(importer_item_ini(importer, "int", "IN_Q_OVERFLOW"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_Q_OVERFLOW_value))
  
  ALLOC_PTR(IN_IGNORED_value, m_int, 0x00008000);
  CHECK_BB(importer_item_ini(importer, "int", "IN_IGNORED"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_IGNORED_value))
  
  ALLOC_PTR(IN_ONLYDIR_value, m_int, 0x01000000);
  CHECK_BB(importer_item_ini(importer, "int", "IN_ONLYDIR"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_ONLYDIR_value))
  
  ALLOC_PTR(IN_DONT_FOLLOW_value, m_int, 0x02000000);
  CHECK_BB(importer_item_ini(importer, "int", "IN_DONT_FOLLOW"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_DONT_FOLLOW_value))
  
  ALLOC_PTR(IN_EXCL_UNLINK_value, m_int, 0x04000000);
  CHECK_BB(importer_item_ini(importer, "int", "IN_EXCL_UNLINK"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_EXCL_UNLINK_value))
  
  ALLOC_PTR(IN_MASK_ADD_value, m_int, 0x20000000);
  CHECK_BB(importer_item_ini(importer, "int", "IN_MASK_ADD"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_MASK_ADD_value))
  
  ALLOC_PTR(IN_ISDIR_value, m_int, 0x40000000);
  CHECK_BB(importer_item_ini(importer, "int", "IN_ISDIR"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_ISDIR_value))
  
  ALLOC_PTR(IN_ONESHOT_value, m_int, 0x80000000);
  CHECK_BB(importer_item_ini(importer, "int", "IN_ONESHOT"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_ONESHOT_value))
  
  ALLOC_PTR(IN_ALL_EVENTS_value, m_int, (0x00000001|0x00000002|0x00000004|0x00000008|0x00000010|0x00000020|0x00000040|0x00000080|0x00000100|0x00000200|0x00000400|0x00000800));
  CHECK_BB(importer_item_ini(importer, "int", "IN_ALL_EVENTS"))
  CHECK_BB(importer_item_end(importer, ae_flag_const | ae_flag_static,  (const m_uint*)IN_ALL_EVENTS_value))
  
  CHECK_BB(importer_func_ini(importer, "int", "inotify_init", (m_uint)gw_inotify_init))
  CHECK_BB(importer_func_end(importer, ae_flag_member))
  CHECK_BB(importer_func_ini(importer, "int", "inotify_init1", (m_uint)gw_inotify_init1))
  CHECK_BB(importer_func_arg(importer, "int", "arg0"))
  CHECK_BB(importer_func_end(importer, ae_flag_member))
  CHECK_BB(importer_func_ini(importer, "int", "inotify_add_watch", (m_uint)gw_inotify_add_watch))
  CHECK_BB(importer_func_arg(importer, "string", "arg1"))
  CHECK_BB(importer_func_arg(importer, "uint32_t", "arg2"))
  CHECK_BB(importer_func_end(importer, ae_flag_member))
  CHECK_BB(importer_func_ini(importer, "int", "inotify_rm_watch", (m_uint)gw_inotify_rm_watch))
  CHECK_BB(importer_func_arg(importer, "int", "arg0"))
  CHECK_BB(importer_func_arg(importer, "int", "arg1"))
  CHECK_BB(importer_func_end(importer, ae_flag_static))
  CHECK_BB(importer_class_end(importer))
  return 1;
}


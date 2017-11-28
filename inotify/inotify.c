#include "type.h"
#include "instr.h"
#include "import.h"
//#include "err_msg.h"
//#include "lang.h"
//#include "ugen.h"

static struct Type_ t_inotify = { "inotify", SZ_INT, &t_object };

CTOR(inotify_ctor) { /*code here */ }

DTOR(inotify_dtor) { /*code here */ }

m_int o_inotify_member_data;
m_int o_inotify_static_data;
m_int* inotify_static_value;

static MFUN(mfun) { /*code here */ }
static SFUN(sfun) { /*code here */ }

IMPORT
{
  CHECK_BB(importer_class_ini(importer, &t_inotify,inotify_ctor, inotify_dtor))

  CHECK_BB(importer_item_ini(importer, "int",  "member"))
  CHECK_BB(o_inotify_member_data = importer_item_end(importer, ae_flag_member, NULL))

  inotify_static_value = malloc(sizeof(m_int));
  CHECK_BB(importer_item_ini(importer, "int", "static"))
  CHECK_BB(o_inotify_static_data = importer_item_end(importer, ae_flag_static, inotify_static_value))

  CHECK_BB(importer_func_ini(importer, "int", "mfun",  (m_uint)mfun))
  CHECK_BB(importer_func_arg(importer, "int", "arg"))
  CHECK_BB(importer_func_end(importer, ae_flag_member))

  CHECK_BB(importer_func_ini(importer, "int", "sfun",  (m_uint)sfun))
  CHECK_BB(importer_func_arg(importer, "int", "arg"))
  CHECK_BB(importer_func_end(importer, ae_flag_static))

  CHECK_BB(importer_class_end(importer))
  return 1;
}

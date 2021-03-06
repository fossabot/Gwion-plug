#include <stdlib.h>
#include <string.h>
#include "type.h"
#include "instr.h"
#include "import.h"
#include "emit.h"

#include "func.h"
#include "type.h"
#include "mpool.h"

#define MAP_INFO(o) (*(struct Map_Info_**)(o->data + t_array->nspc->offset))
#define MAP_KEY(p) ((m_bit*)(p->data))
#define MAP_VAL(p, o) ((m_bit*)(p->data + MAP_INFO(o)->key_size))

typedef m_bool (*f_cmp)(const m_bit* restrict , const unsigned char* restrict , const m_uint);

struct Map_Info_ {
  Type t;
  m_uint key_size;
  m_uint val_size;
  f_cmp cmp;
};
POOL_HANDLE(Map_Info, 16)

static m_bool string_cmp(const m_bit* restrict a, const unsigned char* restrict b, const m_uint size __attribute__((unused))) {
  const M_Object o = (M_Object)b;
  if(!o && !a)
    return 1;
  return o ? !strcmp((char*)a, STRING(o)) : 1;
}

static m_bool cmp(const m_bit* restrict a, const unsigned char*restrict b, const m_uint size) {
  return !memcmp(a, b, size);
}

static CTOR(map_ctor) {
  struct Map_Info_* info = mp_alloc(Map_Info);
  info->t = array_base(o->type_ref->parent);
  const Env env = shred->vm_ref->emit->env;
  const Nspc curr = env->curr;
  const m_str key_name = get_type_name(info->t->name, 1);
  m_uint depth;
  Type_Decl* key_decl = str2decl(env, key_name, &depth);
  const Type key_type = type_decl_resolve(env, key_decl);
  free_type_decl(key_decl);
  info->key_size = key_type->size;
  const m_str val_name = get_type_name(info->t->name, 2);
  Type_Decl* val_decl = str2decl(env, val_name, &depth);
  const Type val_type = type_decl_resolve(env, val_decl);
  free_type_decl(val_decl);
  info->val_size = val_type->size;
  MAP_INFO(o) = info;
  env->curr = curr;
  if(isa(key_type, t_string) > 0)
    MAP_INFO(o)->cmp = string_cmp;
  else
    MAP_INFO(o)->cmp = cmp;
  ADD_REF(o->type_ref->parent);
}

static DTOR(map_dtor) {
  mp_free(Map_Info, MAP_INFO(o));
}


static MFUN(gw_map_get) {
  const VM_Vec v = ARRAY(o);
  const m_uint size = vm_vec_size(v);
  for(m_uint i = 0; i < size; i++) {
    M_Object p;
    vm_vec_get(v, i, &p);
    if(MAP_INFO(o)->cmp(MAP_KEY(p), MEM(SZ_INT), MAP_INFO(o)->key_size)) {
      memcpy((m_bit*)RETURN, MAP_VAL(p, o), MAP_INFO(o)->key_size);
      return;
    }
  }
  memset((m_bit*)RETURN, 0, MAP_INFO(o)->key_size);
}

static MFUN(gw_map_set) {
  const VM_Vec v = ARRAY(o);
  const m_uint size = vm_vec_size(v);
  memcpy((m_bit*)RETURN, MEM(SZ_INT + MAP_INFO(o)->key_size), MAP_INFO(o)->val_size);
  for(m_uint i = 0; i < size; i++) {
    M_Object p;
    vm_vec_get(v, i, &p);
    if(MAP_INFO(o)->cmp(MAP_KEY(p), MEM(SZ_INT), MAP_INFO(o)->key_size)) {
      memcpy(MAP_VAL(p, o), MEM(SZ_INT + MAP_INFO(o)->key_size), MAP_INFO(o)->key_size);
      return;
    }
  }
  const M_Object pair = new_object(NULL, MAP_INFO(o)->t);
  memcpy(pair->data, MEM(SZ_INT), MAP_INFO(o)->key_size + MAP_INFO(o)->val_size);
  vm_vec_add(v, (m_bit*)&pair);
}

GWION_IMPORT(map) {
  const m_str types[] = { "A", "B" };
  const Type t_map = gwi_mk_type(gwi, "Map", SZ_INT, NULL);
  CHECK_BB(gwi_tmpl_ini(gwi, 2, types))
  CHECK_BB(gwi_class_ini(gwi, t_map, map_ctor, map_dtor))
  CHECK_BB(gwi_tmpl_end(gwi))
  Type_Decl* td  = new_type_decl(new_id_list(insert_symbol("Pair"), 0), 0, 0);
  Type_Decl* td0 = new_type_decl(new_id_list(insert_symbol("A"), 0), 0, 0);
  Type_Decl* td1 = new_type_decl(new_id_list(insert_symbol("B"), 0), 0, 0);
  Type_List tl1  = new_type_list(td1, NULL);
  Type_List tl0  = new_type_list(td0, tl1);
  td->types = tl0;
  const Exp e = new_exp_prim_int(0, 0);
  const Array_Sub array = new_array_sub(e, 0);
  add_type_decl_array(td, array);
  CHECK_BB(gwi_class_ext(gwi, td))
  CHECK_BB(gwi_item_ini(gwi, "int", "@map_info"))
  CHECK_BB(gwi_item_end(gwi, 0, NULL));
  CHECK_BB(gwi_func_ini(gwi, "B", "set", gw_map_set))
  CHECK_BB(gwi_func_arg(gwi, "A", "key"))
  CHECK_BB(gwi_func_arg(gwi, "B", "val"))
  CHECK_BB(gwi_func_end(gwi, 0))
  CHECK_BB(gwi_func_ini(gwi, "B", "get", gw_map_get))
  CHECK_BB(gwi_func_arg(gwi, "A", "key"))
  CHECK_BB(gwi_func_end(gwi, 0))
  CHECK_BB(gwi_class_end(gwi))
  return 1;
}

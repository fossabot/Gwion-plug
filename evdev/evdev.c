#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <libevdev/libevdev.h>
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include "defs.h"
#include "type.h"
#include "err_msg.h"
#include "lang.h"
#include "import.h"

#define EVDEV_PREFIX "/dev/input/event"

#define INFO(o) *(EvdevInfo**)(o->data + o_evdev_info)
#define VALUE(o) *(m_uint*)(o->data + o_evdev_value)
#define CODE(o) *(m_uint*)(o->data + o_evdev_code)
#define TYPE(o) *(m_uint*)(o->data + o_evdev_type)

struct Type_ t_evdev_base     = { "Evdev", sizeof(m_uint), &t_event };

m_int o_evdev_info;
m_int o_evdev_time;
m_int o_evdev_type;
m_int o_evdev_code;
m_int o_evdev_value;

static void* evdev_process(void* arg);

typedef struct {
  m_uint type;
  m_uint code;
  m_int  value;
} EvdevArg;

typedef struct {
  struct libevdev* evdev;
  int index;
  int fd;
  pthread_t thread;
  pthread_mutex_t mutex;
  Vector args;
  m_uint pos;
} EvdevInfo;

static CTOR(evdev_base_ctor) {
  EvdevInfo* info = INFO(o) = calloc(1, sizeof(EvdevInfo));
  info->index    = -1;
  info->args     = new_vector();
}

static DTOR(evdev_dtor) {
  EvdevInfo* info = INFO(o);
  if(info->index != -1) {
    libevdev_get_fd(info->evdev);
    pthread_cancel(info->thread);
    pthread_join(info->thread, NULL);
    pthread_mutex_destroy(&info->mutex);
    close(info->fd);
  }
  libevdev_free(info->evdev);
  free_vector(info->args);
  free(INFO(o));
}

static void* evdev_process(void* arg) {
  int rc;
  struct input_event event;
  M_Object o = (M_Object)arg;
  EvdevInfo* info = INFO(o);
  struct pollfd curr;

  curr.fd = info->fd;
  curr.events = POLL_IN;
  curr.revents = 0;
  do {
    poll(&curr, 1, -1);
    rc = libevdev_next_event(info->evdev, LIBEVDEV_READ_FLAG_BLOCKING, &event);
    if(rc == 0 && event.type) {
      EvdevArg* ev = malloc(sizeof(EvdevArg));
      ev->type  = event.type;
      ev->code  = event.code;
      ev->value = event.value;
      pthread_mutex_lock(&info->mutex);
      vector_add(info->args, (vtype)ev);
//      if(shred->vm_ref->sp->pos != info->pos) {
//        info->pos = shred->vm_ref->sp->pos;
        broadcast(o);
      pthread_mutex_unlock(&info->mutex);
//      }
    }
  } while((rc == 1 || rc == 0 || rc == -EAGAIN));
  return NULL;
}

static MFUN(evdev_index) {
  m_int index = *(m_int*)(shred->mem + SZ_INT);
  EvdevInfo* info = INFO(o);
  char c[strlen(EVDEV_PREFIX) + num_digit(index) + 1];
  *(m_uint*)RETURN = -1;
  if(info->index != -1) {
    pthread_cancel(info->thread);
    pthread_join(info->thread, NULL);
    pthread_mutex_destroy(&info->mutex);
    close(libevdev_get_fd(info->evdev));
    libevdev_free(info->evdev);
    info->evdev = NULL;
    info->index = -1;
  }
  sprintf(c, "%s%li", EVDEV_PREFIX, index);
  if((info->fd = open((const char*)c, O_RDONLY|O_NONBLOCK)) == -1) {
    err_msg(INSTR_, 0, "EVDEV: no such event");
    return;
  }
  info->evdev = libevdev_new();
  libevdev_set_fd(info->evdev, info->fd);
  info->index = index;
/*
  struct input_event event;
if(libevdev_has_event_pending(info->evdev))
    libevdev_next_event(info->evdev, LIBEVDEV_READ_FLAG_NORMAL, &event);
*/
  pthread_mutex_init(&info->mutex, NULL);
  pthread_create(&info->thread, NULL, evdev_process, o);
  *(m_uint*)RETURN = 1;
}

static MFUN(evdev_recv) {
  EvdevInfo* info = INFO(o);
  Vector v= info->args;
  pthread_mutex_lock(&info->mutex);
  EvdevArg* arg = (EvdevArg*)vector_front(v);
  vector_rem(v, 0);
  pthread_mutex_unlock(&info->mutex);
  if(!arg) {
    *(m_uint*)RETURN = 0;
    return;
  }
  TYPE(o)   = arg->type;
  CODE(o)   = arg->code;
  VALUE(o)  = arg->value;
  free(arg);
  *(m_uint*)RETURN = 1;
}

static MFUN(evdev_get_index) {
  EvdevInfo* info = INFO(o);
  *(m_uint*)RETURN = info->index;
}

static MFUN(evdev_name) {
  EvdevInfo* info = INFO(o);
  *(M_Object*)RETURN  = new_String(shred, (m_str)libevdev_get_name(info->evdev));
}

IMPORT {
  CHECK_BB(importer_class_ini(importer, &t_evdev_base, evdev_base_ctor, evdev_dtor))

  CHECK_BB(importer_item_ini(importer, "int", "@info"))
  CHECK_BB((o_evdev_info = importer_item_end(importer, ae_flag_const, NULL)))

  CHECK_BB(importer_item_ini(importer, "int", "type"))
  CHECK_BB((o_evdev_type  = importer_item_end(importer, ae_flag_const, NULL)))

  CHECK_BB(importer_item_ini(importer, "int", "code"))
  CHECK_BB((o_evdev_code  = importer_item_end(importer, ae_flag_const, NULL)))

  CHECK_BB(importer_item_ini(importer, "int", "value"))
  CHECK_BB((o_evdev_value  = importer_item_end(importer, ae_flag_const, NULL)))

  CHECK_BB(importer_func_ini(importer, "int", "index", (m_uint)evdev_index))
  CHECK_BB(importer_func_arg(importer, "int", "i"))
  CHECK_BB(importer_func_end(importer, 0))

  CHECK_BB(importer_func_ini(importer, "int", "index", (m_uint)evdev_get_index))
  CHECK_BB(importer_func_end(importer, 0))

  CHECK_BB(importer_func_ini(importer, "string", "name", (m_uint)evdev_name))
  CHECK_BB(importer_func_end(importer, 0))

  CHECK_BB(importer_func_ini(importer, "int", "recv", (m_uint)evdev_recv))
  CHECK_BB(importer_func_end(importer, 0))

  CHECK_BB(importer_class_end(importer))

  return 1;
}

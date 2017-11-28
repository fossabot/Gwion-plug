//%gwclassini(inotify);
//%feature("gwstrip", "inotify_");
%feature("gwctor", "inotify") inotify_init;
%feature("gwctor", "inotify") inotify_init1;
%feature("gwmember", "inotify") inotify_add_watch;
%rename("%(strip:[inotify_event_])s") "";
%include "inotify.h";
//%gwclassend;

#USE_LD=1 # needed for e.g. sporth static lib
include ../config.mk
NAME=CvCam
CFLAGS+=-I/usr/include/opencv
LDFLAGS+=`pkg-config --cflags --libs opencv`
include ../config_post.mk

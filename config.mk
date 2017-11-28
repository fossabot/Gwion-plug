BASEDIR  ?= ../..
GWION    ?= ${BASEDIR}/gwion
INC      ?= ${BASEDIR}/include
CC       ?= gcc
PLUG_DIR ?= $(shell ${GWION} -C 2>&1 | head -n 1 | cut -d '"' -f 2)
SRC       = $(wildcard *.c)
CPP_SRC  += $(wildcard *.cpp)
OBJ       = $(SRC:.c=.o)
OBJ      += $(CPP_SRC:.cpp=.o)
CFLAGS    = -I${INC}
CFLAGS   += -I.. -g
LDFLAGS   = -shared -fPIC -g

ifeq ( $(shell (${GWION} -C 2>&1 | grep double)), 1)
CFLAGS   += -DSPFLOAT=double
else
CFLAGS   += -DSPFLOAT=float
endif

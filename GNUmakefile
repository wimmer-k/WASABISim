name := WasabiSim
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

COMMON_DIR = $(HOME)/common
SALVA_DIR = $(HOME)/progs/salvador/inc
LIB_DIR = $(HOME)/lib
EXTRA_INCLUDES = -I./ -I./include -I$(COMMON_DIR) -I$(SALVA_DIR)

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/architecture.gmk

CPPFLAGS += $(shell $(ROOTSYS)/bin/root-config --cflags) $(EXTRA_INCLUDES)
LDFLAGS  += $(shell $(ROOTSYS)/bin/root-config --libs)
CPPFLAGS  += -Wl,--no-as-needed -Woverloaded-virtual -Wno-shadow -Wno-unused-variable -Wunused-parameter
LDFLAGS  += -Wl,--no-as-needed -Woverloaded-virtual -Wno-shadow -Wno-unused-variable -Wunused-parameter
EXTRALIBS = -L$(LIB_DIR) -lCommandLineInterface -lSalvador

include $(G4INSTALL)/config/binmake.gmk

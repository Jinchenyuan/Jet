
# Compiler settings
CC      ?= cc
CFLAGS = -g -O2 -Wall -lpthread
SHARED = -fPIC --shared

#targets
INI_PATH = 3rd/ini
INI_TARGET = $(INI_PATH)/libiniparser.so

JET_TARGET = Jet

all : $(INI_TARGET) $(JET_TARGET)
.PHONY : all

#iniparser
$(INI_TARGET) : $(INI_PATH)/dictionary.c $(INI_PATH)/iniparser.c | $(INI_PATH)
	$(CC) $(CFLAGS) $(SHARED) -I$(INI_PATH) $^ -o $@ -I$(INI_PATH)


#Jet
JET_WORKER_PATH = worker
JET_CORE_PATH = core

JET_CORE_SRC = jet_main.c jet_malloc.c jet_thread.c jet_shm.c jet_process.c
JET_WORKER_SRC = worker.c

$(JET_TARGET) : $(foreach v, $(JET_CORE_SRC), $(JET_CORE_PATH)/$(v)) $(foreach v, $(JET_WORKER_SRC), $(JET_WORKER_PATH)/$(v))
	$(CC) -o $@ $^ $(INI_TARGET) $(CFLAGS)

clean:
	rm -f Jet

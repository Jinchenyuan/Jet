
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
JET_MASTER_PATH = master
JET_CORE_PATH = core

JET_CORE_SRC = jet_main.c jet_malloc.c jet_thread.c

$(JET_TARGET) : $(foreach v, $(JET_CORE_SRC), $(JET_CORE_PATH)/$(v))
	$(CC) $(CFLAGS) $^ $(INI_TARGET) -o $@

clean:
	rm -f Jet


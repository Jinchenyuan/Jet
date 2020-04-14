
# Compiler settings
CC      ?= gcc
CFLAGS = -g -O2 -Wall
SHARED = -fPIC --shared

#targets
INI_PATH = 3rd/ini
INI_TARGET = $(INI_PATH)/libiniparser.so

JET_MASTER_PATH = master
JET_TARGET = Jet

all : $(INI_TARGET) $(JET_TARGET)
.PHONY : all

#iniparser
$(INI_TARGET) : $(INI_PATH)/dictionary.c $(INI_PATH)/iniparser.c | $(INI_PATH)
	$(CC) $(CFLAGS) $(SHARED) -I$(INI_PATH) $^ -o $@ -I$(INI_PATH)

#gcc main.c -L. -lhello -o main
$(JET_TARGET) : $(JET_MASTER_PATH)/main.c
	$(CC) $(CFLAGS) $^ $(INI_TARGET) -o $@


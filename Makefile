
# Compiler settings
CC      ?= gcc
CFLAGS = -g -O2 -Wall
SHARED = -fPIC --shared

#iniparser
INI_PATH = 3rd/ini

#gcc main.c -L. -lhello -o main
Jet : /master/main.c
	$(CC) $(CFLAGS) -L. $(INI_PATH)/-llibiniparser.so -I $^ -o $@

$(INI_PATH)/libiniparser.so : $(INI_PATH)/dictionary.c $(INI_PATH)/iniparser.c | $(INI_PATH)
	$(CC) $(CFLAGS) $(SHARED) -I$(INI_PATH) $^ -o $@ -I$(INI_PATH)


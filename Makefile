
# Compiler settings
CC      ?= gcc
CFLAGS = -g -O2 -Wall

#iniparser
INI_SRCS = 3rd/ini/iniparser.c \
	   3rd/ini/dictionary.c

INI_OBJS = $(INI_SRCS:.c=.o)

libiniparser.a:	$(INI_OBJS)

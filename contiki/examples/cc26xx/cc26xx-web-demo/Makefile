DEFINES+=PROJECT_CONF_H=\"project-conf.h\"

all: cc26xx-web-demo


PROJECT_SOURCEFILES += cetic-6lbr-client.c mqtt-client.c
PROJECT_SOURCEFILES += httpd-simple.c

CONTIKI_WITH_IPV6 = 1

#####USER ADDED
# Inlcude the debugging symbols in the elf file
# CFLAGS += -g -O0


####################


# REST Engine shall use Erbium CoAP implementation
APPS += mqtt

CONTIKI=../../..
include $(CONTIKI)/Makefile.include

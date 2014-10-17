SUBDIRS	:= src draw font
.PHONY: $(SUBDIRS)

LIBS	:= $(PWD)/src/camera.a \
	$(PWD)/draw/draw.a \
	$(PWD)/font/font.a
INCLUDE	:= -I$(PWD)/include/
	
APPS	:= app
AOBJS	:= $(patsubst %.s, %.o, $(wildcard *.s))
COBJS	:= $(patsubst %.c, %.o, $(wildcard *.c))
CPPOBJS	:= $(patsubst %.cpp, %.o, $(wildcard *.cpp))
OBJS	:= $(AOBJS) $(COBJS) $(CPPOBJS)

CROSS	:= arm-none-linux-gnueabi-
CC	:= $(CROSS)gcc 
AR	:= $(CROSS)ar

CFLAGS	:= -Wall -O2 -g -std=c99 $(INCLUDE)
LDFLAGS	:= -lpthread -static
export CC AR CFLAGS INCLUDE
   
all: $(OBJS)
	@for dir in $(SUBDIRS) ; \
		do $(MAKE) -C $$dir all; \
	done

#	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $(APPS)
	$(CC) $(OBJS) $(LIBS) -o $(APPS) $(LDFLAGS)
#	cp $(APPS) /root/rootfs/test
clean:
#	rm -f $(APPS) $(OBJS)   /root/2410/rootfs/test/$(APPS)
	rm -f $(APPS) $(OBJS)   $(APPS)
	@for dir in $(SUBDIRS) ; \
		do $(MAKE) -C $$dir clean ; \
	done

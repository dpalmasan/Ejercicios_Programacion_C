# Compiler to use
CC = gcc

# flags to pass compiler
CFLAGS = -ggdb3 -O0 -std=c99 -Wall -Werror

# Name for the executable
EXE = cuaterniones

# space-separated list of header files
HDRS = cuaternion.h

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS = -lm

# space-separated list of source files
SRCS = main.c cuaternion.c

# automatically generated list of object files
OBJS = $(SRCS:.c=.o)

# default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# dependencies 
$(OBJS): $(HDRS) Makefile

# housekeeping
clean:
	rm -f core $(EXE) *.o

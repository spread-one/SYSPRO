SRCS = main.c
LIBSRCS = open.c close.c put.c get.c
TARG = kvs_static
TARG_DYNAMIC = kvs_dynamic

CC = gcc
OPTS = -Wall -g
LIBS = -L. -lkvs

OBJS = $(SRCS:.c=.o)
LOBJS = $(LIBSRCS:.c=.o)
LARS = libkvs.a
LSOS = libkvs.so

all: static dynamic

static: $(TARG)

$(TARG): $(OBJS) $(LARS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS) -static

$(LARS): $(LOBJS)
	ar rs $(LARS) $(LOBJS)

$(LSOS): $(LOBJS)
	$(CC) -shared -o $(LSOS) $(LOBJS)  # libkvs.so 생성

%.o: %.c
	$(CC) $(OPTS) -c $< -o $@

dynamic: $(TARG_DYNAMIC)

$(TARG_DYNAMIC): $(OBJS) $(LSOS)
	$(CC) -o $(TARG_DYNAMIC) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS) $(LOBJS) $(LARS) $(LSOS) $(TARG) $(TARG_DYNAMIC)

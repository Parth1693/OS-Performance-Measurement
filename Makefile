CC = gcc
SRC = rdtsc_overhead.c \
procedure_call.c \
create_thread.c \
create_process.c \
cswitch_thread.c \
cswitch_process.c \
ram_latency.c \
ram_bw.c \
page_fault.c \
syscall.c \
cycle_time.c

CFLAGS = -O0 -pthread
OBJ = $(SRC:.c=.o)
EXE = $(patsubst %.c,%,$(SRC))

INCLUDE +=  /usr/src/linux-headers-4.4.0-21/include/linux

all: $(EXE) 

clean:
	rm -rf *.o $(EXE) 

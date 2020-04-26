CC = gcc
CFLAGS = -Wall -g

LD = gcc
LDFLAGS = util.h util.c include/sha256.h include/sha256.c block.h block.c blockchain.h blockchain.c  main.c


RM = rm

PROG = blockchain

all: $(PROG)

clean:
	$(RM) -f $(PROG) $(OBJS)


$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o blockchain

%.o: %.c
	$(CC) $(CFLAGS) -c $<

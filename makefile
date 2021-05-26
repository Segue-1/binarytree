CC = gcc
IDIR =./include
CFLAGS = -I$(IDIR) -g -Wall -lm

EXEC1 = main
OBJS1 = main.o

SHARE = main.o tree.o

DEPS = tree.h node.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: main

main: $(OBJS1) $(SHARE)
	gcc -o $(EXEC1) $^ $(CFLAGS)

clean:
	rm $(EXEC1) $(OBJS1) $(SHARE) output.inorder output.preorder output.postorder


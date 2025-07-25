TARGET = watcher reciever
SRC = watcher.c reciever.c
CFLAGS= # -I ../include

CC = gcc

.PHONY: all clean

all: $(TARGET)
main : watcher.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR)$(LIBS)
client : reciever.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR)$(LIBS)
clean:
	rm -f $(TARGET)

TARGET = raft_client

SRC = raft_client.c ../lib/modules.c

CC = gcc
INCLUDE=-I ../include
CFLAGS=  -g


.PHONY: all clean

all:
	$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

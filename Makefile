.PHONY: all clean pipe raft_client

all: pipe raft_client

module1:
    $(MAKE) -C pipe

module2:
    $(MAKE) -C raft_client

clean:
    $(MAKE) -C pipe clean
    $(MAKE) -C raft_client clean

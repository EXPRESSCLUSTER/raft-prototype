#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

// #include "raft.h"

#define BUFFER_LEN 128

bool check_timeout(struct timespec std, struct timespec timeout) {
  struct timespec now;
  clock_gettime(CLOCK_MONOTONIC, &now);

  time_t sec_diff = now.tv_sec - std.tv_sec;
  long nsec_diff = now.tv_nsec - std.tv_nsec;

  if (nsec_diff < 0) {
    sec_diff -= 1;
    nsec_diff += 1000000000L;
  }

  if (sec_diff > timeout.tv_sec ||
      (sec_diff == timeout.tv_sec && nsec_diff >= timeout.tv_nsec)) {
    return true; // timeout
  }

  return false; // not yet
}

void reset_timer(struct timespec *timer) {
  clock_gettime(CLOCK_MONOTONIC, timer);
}

bool pipe_appended(char *buf, int fifo_fd) {
  ssize_t r = read(fifo_fd, buf, BUFFER_LEN - 1);
  if (r > 0) {
    buf[r] = '\0';
    fflush(stdout);
    return 1;
  }
  return 0;
}
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#define FIFO_NAME "/tmp/fifo"
#define BUF_SIZE 1024

int log_appended(char *buf, int fifo_fd) {
  ssize_t r = read(fifo_fd, buf, BUF_SIZE - 1);
  if (r > 0) {
    buf[r] = '\0';
    fflush(stdout);
    return 1;
  }
  return 0;
}

int main() {
  char buf[BUF_SIZE];
  int fifo_fd = open(FIFO_NAME, O_RDONLY);
  if (fifo_fd == -1) {
    perror("open fifo");
    return 1;
  }
  while (1) {
    if (log_appended(buf, fifo_fd))
      printf("%s", buf);
  }
  close(fifo_fd);
  return 0;
}
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define FIFO_NAME "/tmp/fifo"
#define FILENAME "test"
#define INTERVAL_USEC (100 * 1000)

int main(int argc, char **argv) {
  FILE *fp;
  int fifo_fd;
  char buf[BUF_SIZE];
  long last_pos, cur_pos;

  mkfifo(FIFO_NAME, 0666);

  if (NULL == (fp = fopen(FILENAME, "r"))) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  fseek(fp, 0, SEEK_END);
  last_pos = ftell(fp);
  while (1) {
    fifo_fd = open(FIFO_NAME, O_WRONLY);
    if (fifo_fd == -1) {
      perror("open fifo");
      fclose(fp);
      exit(EXIT_FAILURE);
    }

    fseek(fp, 0, SEEK_END);
    cur_pos = ftell(fp);

    if (cur_pos > last_pos) {
      fseek(fp, last_pos, SEEK_SET);
      while (fgets(buf, sizeof(buf), fp) != NULL) {
        write(fifo_fd, buf, strlen(buf));
      }
      last_pos = ftell(fp);
    }
    usleep(INTERVAL_USEC);
    close(fifo_fd);
  }
}
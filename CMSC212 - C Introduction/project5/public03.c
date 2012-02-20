/**
 * CMSC 212, 2008 Fall, Project #5
 * Public Test #3, public03.c
 * 
 * Tests the modified main.c program.
 *
 * Replaces itself with main.x via exec(), after redirecting input from the
 * file numbers.
 *
 * Don't link with either table object file.
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void redirect_in(const char *filename);

int main() {
  redirect_in("numbers");
  execl("./main.x", "main.x", NULL);
  perror("exec error");
  return -1;
}

static void redirect_in(const char *filename) {
  int fd= open(filename, O_RDONLY);
  if (fd < 0) {
    perror("open error with input file");
    exit(-1);
  }
  if (dup2(fd, STDIN_FILENO) < 0) {
    perror("dup2 error");
    exit(-1);
  }
  close(fd);
}

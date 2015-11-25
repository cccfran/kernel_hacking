#include <stdio.h>
#include <linux/unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (!syscall(__NR_separate))
    printf("separate: Successfully separate\n");
  else
    printf("separate: Nothing to separate\n");

  return 0;
}
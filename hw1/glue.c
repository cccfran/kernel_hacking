#include <stdio.h>
#include <linux/unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc != 4) {
    printf("glue: usage: ./glue [pid_1] [pid_2] [ratio]\n");
    return 0;
  }

  pid_t pid1 = (pid_t)(strtol(argv[1], NULL, 10));
  pid_t pid2 = (pid_t)(strtol(argv[2], NULL, 10));
  int ratio = (int)(strtol(argv[3], NULL, 10));

  if (!syscall(__NR_glue, pid1, pid2, ratio))
    if (ratio == 0)
      printf("glue: Successfully freeze the old guy\n");
    else
      printf("glue: Successfully glue %lu and %lu with ratio %d\n", pid1, pid2, ratio);
  else
    printf("glue: Fail to glue\n");

  return 0;
}

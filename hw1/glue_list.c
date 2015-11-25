#include <stdio.h>
#include <linux/unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  long pids[2];
  if (!syscall(__NR_glue_list, pids)) {
    printf("glue_list: Successfully glue list\n");
    printf("\tpid tuple (%lu, %lu)\n", pids[0], pids[1]);
  }
  else
    printf("glue_list: Nothing glued\n");

  return 0;
}

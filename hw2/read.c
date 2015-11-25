#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 1024
#define NR_eopen 328
#define NR_eclose 329

int main(int argc, char** argv) {

  int fd;
  /*
  if(argc != 2){
    printf("Usage: ./read [filename]\n");
    return 1;
  }
  */
  printf("Enter key: ");
  char ekey[256];
  int elen;
  char filename[256];
  strcpy(filename, "a.txt");
  int i = 0, ch;
  while ((ch = getc(stdin)) != EOF) {
    if (ch == '\n')
      break;
    ekey[i++] = ch;
  }
  //  fgets(ekey, 256, stdin);
  elen = strlen(ekey);
  printf("%s\n", ekey);
  printf("%d\n", elen);
  pid_t pid = getpid();
  printf("pid %d\n", pid);
  
  if ((fd = syscall(NR_eopen, ekey, elen, filename, O_RDONLY, 0, pid)) == -1) {
    perror("open");
    return 2;
  } else
    printf("Successfully opened\n");

  char output[BUF_SIZE];
  memset(output, '\0', BUF_SIZE);

  read(fd, output, BUF_SIZE);

  printf("%s\n", output);

  if (syscall(NR_eclose, fd) == -1) {
    perror("close");
    return 2;
  } else
    printf("Successfully close\n");
  
  return 0;
}


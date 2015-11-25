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
    printf("Usage: ./write file\n");
    return 1;
  }
  */
  
  printf("Enter key: ");
  char ekey[256];
  int elen;
  char filename[256];
  strcpy(filename, "a.txt");
  int j = 0, c;
  while ((c = getc(stdin)) != EOF) {
    if (c == '\n')
      break;
    ekey[j++] = c;
  }
  //  fgets(ekey, 256, stdin);
  if ((elen = strlen(ekey)) == 0) {
    printf("The key is empty\n");
    return;
  }
  
  printf("%s\n", ekey);
  printf("%d\n", elen);
  pid_t pid = getpid();
  printf("pid: %d\n", pid);
  
  if ((fd = syscall(NR_eopen, ekey, elen, filename, O_WRONLY|O_CREAT|O_TRUNC, 0644, pid)) == -1) {
    perror("open");
    return 2;
  } else {
    printf("open success\n");
  }
  
  printf("Write something: ");
  char input[BUF_SIZE];
  memset(input, '\0', BUF_SIZE);
  int i = 0, ch;
  while ((ch = getc(stdin)) != EOF) {
    input[i++] = ch;
  }
  //  input[i] = '\0';

  printf("%s\n", input);
  printf("i is %d\n", i);

  int writelength;
  if ((writelength = write(fd, input, i)) != i)
    printf("WRITIG ERROR\n");
  printf("%d\n",writelength);
  if (syscall(NR_eclose, fd) == -1) {
    perror("close");
    return 2;
  } else
    printf("Successfully close\n");
  
  return 0;
}


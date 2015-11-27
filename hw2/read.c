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

int check_remain_len(int fd, int offset) {
  if (fd == -1)
    return -1;

  int end = lseek(fd, 0, SEEK_END);
  return (end-offset);
}

int main(int argc, char** argv) {
  int fd;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
  if(argc != 2){                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    printf("Usage: ./read [filename]\n");                                                                                                                                                                                                                                                                                                                                                                                                                                                  
    return 1;                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
  }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
  
  /* Input key */
  printf("Enter key: ");
  char ekey[256];
  int elen;
  char filename[256];
  strcpy(filename, argv[1]);
  int i = 0, ch;
  while ((ch = getc(stdin)) != EOF) {
    if (ch == '\n')
      break;
    ekey[i++] = ch;
  }
  elen = strlen(ekey);
  //  printf("%s\n", ekey);                                                                                                                                                                                                                                                                                                                                                                                                                                                                
  //  printf("%d\n", elen);                                                                                                                                                                                                                                                                                                                                                                                                                                                                
  pid_t pid = getpid();
  //  printf("pid %d\n", pid);                                                                                                                                                                                                                                                                                                                                                                                                                                                             

  /* open file */
  if ((fd = syscall(NR_eopen, ekey, elen, filename, O_RDONLY, 0, pid)) == -1) {
    perror("open");
    return 2;
  }// else                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
    //    printf("Successfully opened\n");                                                                                                                                                                                                                                                                                                                                                                                                                                                 

  int rmode = 0;
  int filelen = check_remain_len(fd, 0);
  //  printf("filelen: %d\n", filelen);                                                                                                                                                                                                                                                                                                                                                                                                                                                    
  char output[filelen];
  lseek(fd, 0, SEEK_SET);
  int retlen = read(fd, output, filelen);
  //  printf("%d\n", retlen);                                                                                                                                                                                                                                                                                                                                                                                                                                                              
  //  printf("%s\n", output);                                                                                                                                                                                                                                                                                                                                                                                                                                                              
  while (!rmode) {
    printf("Select reading mode: \n");
    printf("1. Normal read\n");
    printf("2. Random access\n");
    printf("Your option: ");
    scanf("%d", &rmode);
    getchar();
    if (rmode == 1) { /* normal read */
      // printf("%s\n", output);                                                                                                                                                                                                                                                                                                                                                                                                                                                           
      int j;
      for (j = 0; j < filelen; j++)
        printf("%c", output[j]);
      printf("\n");
    } else if (rmode == 2) { /* random access */
      printf("Enter offset: ");
      int offset;
      scanf("%d", &offset);
      getchar();
      int remain_len = check_remain_len(fd, offset);
      char output2[remain_len];
      int j = offset;
      for (i = 0; i < remain_len; i++) {
        output2[i] = output[j++];
        printf("%c", output2[i]);
      }
      printf("\n");
      // printf("%s\n", output2);                                                                                                                                                                                                                                                                                                                                                                                                                                                          
    } else
      rmode = 0;
  }

  /* close file */
  if (syscall(NR_eclose, fd) == -1) {
    perror("close");
    return 2;
  } //else                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
    //printf("Successfully close\n");                                                                                                                                                                                                                                                                                                                                                                                                                                                      

  return 0;
}

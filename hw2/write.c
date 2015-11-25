include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 1024
#define NR_eopen 328
#define NR_eclose 329

int check_file_len(int fd) {
  if (fd == -1) /* no open file */
    return -1;

  int set = lseek(fd, 0, SEEK_SET);
  int end = lseek(fd, 0, SEEK_END);
  return (end-set);
}

int check_remain_len(int fd, int offset) {
  if (fd == -1)
    return -1;

  int end = lseek(fd, 0, SEEK_END);
  return (end-offset);
}

int main(int argc, char** argv) {

  int fd = -1;
  /*                                                                                                                                    
  if(argc != 2){                                                                                                                        
    printf("Usage: ./write [filename]\n");                                                                                              
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

  if ((fd = syscall(NR_eopen, ekey, elen, filename, O_RDWR|O_CREAT, 0640, pid)) == -1) {
    perror("open");
    return 2;
  } else {
    printf("open success\n");
  }

  int curr_pos = lseek(fd, 0, SEEK_CUR);
  printf("Current position %d\n", curr_pos);

  const int filelen = check_file_len(fd);
  printf("file lenght is: %d\n", filelen);
  char input[filelen+BUF_SIZE];
  memset(input, '\0', filelen+BUF_SIZE);
  lseek(fd, 0, SEEK_SET);
  int retlen = read(fd, input, filelen);
  int wmode = 0;
  while (!wmode) {
    printf("Select writing mode: \n");
    printf("1. Sequential write\n");
    printf("2. Random access\n");
    printf("Your option: ");
    scanf("%d", &wmode);
    getchar();
    if (wmode == 1) {
      //    printf("Current position %d\n", curr_pos);                                                                                  
      //      if (filelen == 0)                                                                                                         
      //        break;                                                                                                                  
      printf("Original len: %d\n", retlen);
      printf("Original string: %s\n", input);
      printf("Write something: ");
      //  char input[BUF_SIZE];                                                                                                         
      //  memset(input, '\0', BUF_SIZE);                                                                                                
      int i = filelen, ch;
      while ((ch = getc(stdin)) != EOF) {
        input[i++] = ch;
        //    printf("%d: %c\n",i-1,ch);                                                                                                
      }
      //  input[i] = '\0';                                                                                                              

      printf("%s\n", input);
      printf("i is %d\n", i);

      int writelength;
      lseek(fd, 0, SEEK_SET); // re-write the whole file                                                                                
      if ((writelength = write(fd, input, i)) != i)
        printf("WRITIG ERROR\n");
      printf("%d\n",writelength);
    }

    else if (wmode == 2) {
      printf("Enter offset: ");
      int offset;
      scanf("%d", &offset);
      getchar();
      int remain_len = check_remain_len(fd, offset);
      char str[remain_len];
      for (j=offset; j<filelen; j++) {
        str[j-offset] = input[j];
      }
      printf("%s\n", str);
      printf("Write something: ");
      //  char input[BUF_SIZE];                                                                                                         
      //  memset(input, '\0', BUF_SIZE);                                                                                                
      int i = offset, ch;
      while ((ch = getc(stdin)) != EOF) {
        input[i++] = ch;
        //    printf("%d: %c\n",i-1,ch);                                                                                                
      }
      //  input[i] = '\0';                                                                                                              
      for (j = 0; j < remain_len; j++) {
        input[i++] = str[j];
      }
      printf("%s\n", input);
      printf("i is %d\n", i);

      int writelength;
      lseek(fd, 0, SEEK_SET); // re-write the whole file                                                                                
      if ((writelength = write(fd, input, i)) != i)
        printf("WRITIG ERROR\n");
      printf("%d\n",writelength);
    } else {
      printf("Input error. Retry!\n");
      wmode = 0;
    }
  }


  if (syscall(NR_eclose, fd) == -1) {
    perror("close");
    return 2;
  } else
    printf("Successfully close\n");

  return 0;
}
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

int check_len(int fd, int offset) {
  if (fd == -1)
    return -1;

  int of = lseek(fd, offset, SEEK_SET);
  int end = lseek(fd, 0, SEEK_END);

  return (end-offset);
}

int main(int argc, char** argv) {

  int fd = -1;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
  if(argc != 2){                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    printf("Usage: ./write [filename]\n");                                                                                                                                                                                                                                                                                                                                                                                                                                                 
    return 1;                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
  }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        

  /* input key */
  printf("Enter key: ");
  char ekey[256];
  int elen;
  char filename[256];
  strcpy(filename, argv[1]);
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

  //  printf("%s\n", ekey);                                                                                                                                                                                                                                                                                                                                                                                                                                                                
  //  printf("%d\n", elen);                                                                                                                                                                                                                                                                                                                                                                                                                                                                
  pid_t pid = getpid();
  //  printf("pid: %d\n", pid);                                                                                                                                                                                                                                                                                                                                                                                                                                                            

  /* eopen file */
  if ((fd = syscall(NR_eopen, ekey, elen, filename, O_RDWR|O_CREAT, 0640, pid)) == -1) {
    perror("open");
    return 2;
  } else {
    //    printf("open success\n");                                                                                                                                                                                                                                                                                                                                                                                                                                                        
  }

  /* user input */
  /*                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
  char *userinput;                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
  int inputc = 0;                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
  int iter = 1;                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
  userinput = malloc(sizeof(char)*BUF_SIZE);                                                                                                                                                                                                                                                                                                                                                                                                                                               
  while ((c = getc(stdin)) != EOF) {                                                                                                                                                                                                                                                                                                                                                                                                                                                       
    if (c == '\n')                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
      break;                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
    *(userinput+inputc) = c;                                                                                                                                                                                                                                                                                                                                                                                                                                                               
    inputc++;                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
    if (inputc == (BUF_SIZE * iter)) {                                                                                                                                                                                                                                                                                                                                                                                                                                                     
      iter++;                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
      userinput = (char *) realloc(userinput, BUF_SIZE * iter);                                                                                                                                                                                                                                                                                                                                                                                                                            
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
  }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
  printf("\t\tUsr input length: %d\n", inputc);                                                                                                                                                                                                                                                                                                                                                                                                                                            
  printf("\t\t%s\n", userinput);                                                                                                                                                                                                                                                                                                                                                                                                                                                           
  */

  const int filelen = check_len(fd, 0);
  //  printf("file lenght is: %d\n", filelen);                                                                                                                                                                                                                                                                                                                                                                                                                                             
  /*                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
  char input[filelen+BUF_SIZE];                                                                                                                                                                                                                                                                                                                                                                                                                                                            
  memset(input, '\0', filelen+BUF_SIZE);                                                                                                                                                                                                                                                                                                                                                                                                                                                   
  lseek(fd, 0, SEEK_SET);                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
  int retlen = read(fd, input, filelen);                                                                                                                                                                                                                                                                                                                                                                                                                                                   
  */
  int wmode = 0;
  while (!wmode) {
    printf("Select writing mode: \n");
    printf("1. Sequential write\n");
    printf("2. Random access\n");
    printf("Your option: ");
    scanf("%d", &wmode);
    getchar();
    if (wmode == 1) { /* Sequential write */
      /* User input */
      printf("Write something: ");
      char *userinput;
      int inputc = 0;
      int iter = 1;
      userinput = malloc(sizeof(char)*BUF_SIZE);
      while ((c = getc(stdin)) != EOF) {
        *(userinput+inputc) = c;
        inputc++;
        if (inputc == (BUF_SIZE * iter)) {
          iter++;
          userinput = (char *) realloc(userinput, BUF_SIZE * iter);
        }
      }
      //      printf("\t\tUsr input length: %d\n", inputc);                                                                                                                                                                                                                                                                                                                                                                                                                                
      //      printf("\t\t%s\n", userinput);                                                                                                                                                                                                                                                                                                                                                                                                                                               

      /* Copy user input to input array */
      int i = filelen, ch;
      char input[filelen + inputc];
      lseek(fd, 0, SEEK_SET);
      int retlen = read(fd, input, filelen);
      //      printf("Original len: %d\n", retlen);                                                                                                                                                                                                                                                                                                                                                                                                                                        
      //      printf("Original string: %s\n", input);                                                                                                                                                                                                                                                                                                                                                                                                                                      
      for (j = 0; j < inputc; j++) {
        input[i++] = *(userinput+j);
      }

      //      printf("%s\n", input);                                                                                                                                                                                                                                                                                                                                                                                                                                                       
      //      printf("i is %d\n", i);                                                                                                                                                                                                                                                                                                                                                                                                                                                      

      /* write */
      int writelength;
      lseek(fd, 0, SEEK_SET); // re-write the whole file                                                                                                                                                                                                                                                                                                                                                                                                                                   
      if ((writelength = write(fd, input, i)) != i)
        printf("WRITIG ERROR\n");
      //      printf("%d\n",writelength);                                                                                                                                                                                                                                                                                                                                                                                                                                                  
    }

    else if (wmode == 2) { /* Random access */
      printf("Enter offset (if offset exceeds file length, append after the end of the file): ");
      int offset;
      scanf("%d", &offset);
      getchar();
      if(offset > filelen) /* if offset exceeds file length, append after the end */
        offset = filelen;

      /* User input */
      printf("Write something: ");
      char *userinput;
      int inputc = 0;
      int iter = 1;
      userinput = malloc(sizeof(char)*BUF_SIZE);
      while ((c = getc(stdin)) != EOF) {
        *(userinput+inputc) = c;
        inputc++;
        if (inputc == (BUF_SIZE * iter)) {
          iter++;
          userinput = (char *) realloc(userinput, BUF_SIZE * iter);
        }
      }
      //      printf("\t\tUsr input length: %d\n", inputc);                                                                                                                                                                                                                                                                                                                                                                                                                                
      //      printf("\t\t%s\n", userinput);                                                                                                                                                                                                                                                                                                                                                                                                                                               

      /* Copy user input to input array */
      char input[filelen + inputc];
      lseek(fd, 0, SEEK_SET);
      int retlen = read(fd, input, filelen);
      //      printf("Original len: %d\n", retlen);                                                                                                                                                                                                                                                                                                                                                                                                                                        
      //      printf("Original string: %s\n", input);                                                                                                                                                                                                                                                                                                                                                                                                                                      

      /* get the string after offset */
      int remain_len = check_len(fd, offset);
      char str[remain_len];
      for (j=offset; j<filelen; j++) {
        str[j-offset] = input[j];
      }
      //      printf("%s\n", str);                                                                                                                                                                                                                                                                                                                                                                                                                                                         


      int i = offset, ch;
      for (j = 0; j < inputc; j++) {
        input[i++] = *(userinput+j);
      }
      /*                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
      while ((ch = getc(stdin)) != EOF) {                                                                                                                                                                                                                                                                                                                                                                                                                                                  
        input[i++] = ch; /* starting writing from offset                                                                                                                                                                                                                                                                                                                                                                                                                                   
      }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
      */



      /* move the string after offset backwards */
      for (j = 0; j < remain_len; j++) {
        input[i++] = str[j];
      }
      //      printf("%s\n", input);                                                                                                                                                                                                                                                                                                                                                                                                                                                       
      //      printf("i is %d\n", i);                                                                                                                                                                                                                                                                                                                                                                                                                                                      

      /* write */
      int writelength;
      lseek(fd, 0, SEEK_SET); // re-write the whole file                                                                                                                                                                                                                                                                                                                                                                                                                                   
      if ((writelength = write(fd, input, i)) != i)
        printf("WRITIG ERROR\n");
      printf("%d\n",writelength);
    } else { /* Wrong selection */
      printf("Input error. Retry!\n");
      wmode = 0;
    }
  }

  /* close the file */
  if (syscall(NR_eclose, fd) == -1) {
    perror("close");
    return 2;
  } else
    printf("\nSuccessfully close\n");

  return 0;
}
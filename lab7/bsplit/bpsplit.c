#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

void merge(char *part, char* str, int num) {
  char buf[10];
  sprintf(buf, "%d", num);
  strcat(part,"part/");
  strcat(part,str);
  strcat(part,".");
  if (num<10) strcat(part, "0");
  strcat(part,buf);
}

void copypart(char *source, char *destination, int offset, int size) {
  FILE *sfile = fopen(source, "r");
  FILE *dfile = fopen(destination, "w");
  int sizeRead = 0;
  int count = 0;
  unsigned int word = 0;
  unsigned int part = 0;
  fseek(sfile, offset, SEEK_SET);
  sizeRead = fread(&word , 1 , sizeof(word) , sfile);
  part = word;
  fwrite(&word, 1 , sizeRead, dfile);
  fwrite(&word, 1 , sizeRead, dfile);
  count = sizeRead*2;
  while (1) {
    word = 0;
    if(!((count<(size+sizeof(part)))&&(sizeRead = fread(&word , 1 , sizeof(word) , sfile)))) break;
    part ^= word;
    count += sizeRead;
    fwrite(&word, 1 , sizeRead, dfile);
  }  
    fseek(dfile , 0 , SEEK_SET);
    fwrite(&part , 1 , sizeof(part), dfile);
    fclose (dfile); 
    fclose (sfile);
}

int main(int argc, char **argv) {
  if (argc == 1) {
    printf("enter file names\n");
    return 0;
  }
  int xflag = 0;
  int opt;
  int size = 1024;
  while ((opt = getopt(argc, argv, "hxb:")) != -1) {
      switch (opt) {
      case 'h':
	printf("OPTIONS\n\t-b SIZE\tput at most SIZE bytes per output file\n\t-h\tprint a summary of options and exit\n\t-x\tprint the checksum of FILE on the standard output\n");
	exit(0);
	break;
      case 'x':
	xflag = 1;
	break;
      case 'b':
	size = atoi(optarg);
	break;
      default: 
	fprintf(stderr, "Usage: %s [-x] [-h] [-b SIZE] filename\n", argv[0]);
	exit(EXIT_FAILURE);
      }
  }
  
  if (optind >= argc) {
      fprintf(stderr, "Expected File Name after options\n");
      exit(EXIT_FAILURE);
  }
  
  
  char *filename = argv[argc-1];
  FILE *sfile = fopen(filename, "r");
  fseek(sfile, 0, SEEK_END);
  int fileSize = ftell(sfile);
  printf("file size =%d\n", fileSize);
  int nchunks = (fileSize + size - 5 ) / size;
  printf("nchunks =%d\n", nchunks);
  int chunkind=1;
  int len = strlen(filename)+7;
  pid_t pids[nchunks];
  int i;
  for (chunkind = 1; chunkind <= nchunks; chunkind++) {
      char partName[len];
      partName[0]=0;
      merge (partName, filename, chunkind);
      pids[chunkind-1] = fork();
      if (pids[chunkind-1] == -1) {
	  perror("fork");
	  exit(EXIT_FAILURE);
      }
      else if (pids[chunkind-1] == 0) {
	  copypart(filename, partName, ((chunkind-1)*(size-4)), (size-4));
	  return 0;
      }
  }
  
  
  return 0;
}
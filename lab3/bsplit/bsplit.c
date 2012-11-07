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
	printf("OPTIONS\n\t-h  print a summary of options and exit\n\t-x  print the checksum as a hexadecimal rather than decimal number.\n");
	exit(0);
	break;
      case 'x':
	xflag = 1;
	break;
      case 'b':
	size = atoi(optarg);
	break;
      default: /* '?' */
	fprintf(stderr, "Usage: %s [-x] [-h] [-b SIZE] filename\n", argv[0]);
	exit(EXIT_FAILURE);
      }
  }
  
  if (optind >= argc) {
      fprintf(stderr, "Expected File Name after options\n");
      exit(EXIT_FAILURE);
  }
  
  printf("size=%d\n",size);
  char *filename = argv[argc-1];
  printf("filename=%s\n",filename);
  int len = strlen(filename)+7;
  int sizeRead = 0;
  if (size > 0) {
      FILE *sfile = fopen(argv[argc-1], "r");
      int i=1;
      while (1) {
	char partName[len];
	partName[0]=0;
	merge (partName, filename, i);
	printf("part name=%s\n",partName);
	char aPart [size];
	if(!(sizeRead = fread(&aPart , 1 , size , sfile))) break;
	FILE *pfile = fopen(partName, "w");
	fwrite(aPart, 1 , sizeRead, pfile);
	fclose (pfile);
	i++;
      }
      fclose(sfile);
  }
  
  
  if (xflag==1) {
    FILE *file = fopen(argv[argc-1],"r");
    unsigned int word=0;
    unsigned int xsum=0;
    fread(&xsum,1 ,sizeof(xsum),file);
    while(fread(&word,1, sizeof(word), file)) {
      xsum ^= word;
      word =0;
    }
    printf("Checksum is %d\n",xsum);
    fclose(file);
  }
  
  return 0;
}
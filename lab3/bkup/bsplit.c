#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

void merge(char *part, char* str, int num) {
  char buf[10];
  sprintf(buf, "%d", num);
  //printf("buf=%s\n",buf);
  //printf("part=%s\n",part);
  strcat(part,str);
  strcat(part,".");
  strcat(part,buf);

  printf("merge=%s\n",part);
}

int main(int argc, char **argv) {
  if (argc == 1) {
    printf("enter file names\n");
    return 0;
  }
  int xflag = 0;
  int opt;
  int size = 0;
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
  /*
  int num = 12;
  char buf[10];
  sprintf(buf, "%d", num);
  char part[strlen(buf) + strlen(filename)];
  strcat(part,filename);
  strcat(part,".");
  strcat(part,buf);
  printf("filename part=%s\n",part);
  */
  int len = strlen(filename)+3;
  printf("len=%d\n",len);
  if (size > 0) {
      FILE *sfile = fopen(argv[argc-1], "r");
      int flag = 0;
      int i=1;
      while (flag == 0) {
	char partName[len];
	//printf("filename part=%s\n=",partName);
	merge (partName, filename, i);
	//printf("filename part=%s\n",partName);
	char aPart [size];
	fread(&aPart , size , 1 , sfile);
	FILE *pfile = fopen(partName, "w");
	fwrite(aPart, size, 1, pfile);
	flag = 1;
    
      }
    
    
  }
  
  
  if (xflag==1) {
    FILE *file = fopen(argv[argc-1],"r");
    unsigned int word;
    unsigned int xsum;
    fread(&xsum,sizeof(xsum),1,file);
    while(fread(&word, sizeof(word), 1, file)) {
      xsum ^= word;
    }
    printf("Checksum is %d\n",xsum);
    fclose(file);
  }
  
  return 0;
}
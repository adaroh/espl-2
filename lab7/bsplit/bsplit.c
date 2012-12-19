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
  int len = strlen(filename)+7;
  int sizeRead = 0;
  char firstPart[len];
  firstPart[0]=0;
  unsigned int word = 0;
  unsigned int xsum = 0;
  unsigned int part = 0;
  int count;
  int i=1;
  if (size > 0) {
      FILE *sfile = fopen(argv[argc-1], "r");
      while (1) {
	char partName[len];
	partName[0]=0;
	merge (partName, filename, i);
	word = 0;
	if(!(sizeRead = fread(&word , 1 , sizeof(word) , sfile))) break;
	FILE *pfile = fopen(partName, "w");
	part=word;
	if (i==1) xsum=word;
	else xsum ^= word;
	fwrite(&word, 1 , sizeof(word), pfile);
	fwrite(&word, 1 , sizeof(word), pfile);
	count = sizeRead*2;
	while (1) {
	    word = 0;
	    if(!((count<size)&&(sizeRead = fread(&word , 1 , sizeof(word) , sfile)))) break;
	    xsum ^= word;
	    part ^= word;
	    count += sizeRead;
	    fwrite(&word, 1 , sizeRead, pfile);
	}
	
	fseek(pfile , 0 , SEEK_SET);
	fwrite(&part , 1 , sizeof(part), pfile);
	fclose (pfile);
	i++;
	part = 0;
      }
      fclose(sfile);
  }

    if (xflag==1) {
      printf("Checksum is %d\n",xsum);
    }

  return 0;
}
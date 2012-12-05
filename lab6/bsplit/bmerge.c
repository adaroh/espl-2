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

void outputFileInFolder(char *output, char* str) {
  strcat(output, "part/");
  strcat(output, str);
}

int main(int argc, char **argv) {
  if (argc == 1) {
    printf("enter file names\n");
    return 0;
  }
  char *outputFilename = 0;
  unsigned int xsumExpected = 0;

  
  if (optind >= argc) {
      fprintf(stderr, "Expected File Name after options\n");
      exit(EXIT_FAILURE);
  }
  
  char *filename = argv[argc-1];
  int len = strlen(filename)+7;
  int sizeRead = 0;
  char mainName[len];
  mainName[0] = 0;
  if (!outputFilename) outputFilename = argv[argc-1];
  outputFileInFolder(mainName, outputFilename);
  FILE *sfile = fopen(mainName, "w");
  int i=1;
  int lastFile = 1;
  unsigned int part = 0;
  unsigned int partRead = 0;
  unsigned int xsum = 0;
  unsigned int word = 0;
  while (lastFile) {
    char partName[len];
    partName[0]=0;
    merge (partName, filename, i);
    FILE *pfile;
    if (!(pfile = fopen(partName, "r"))) {
      lastFile=0;
    } else {
	fread(&partRead , 1 , sizeof(partRead), pfile);
	word = 0;
	sizeRead = fread(&word, 1 , sizeof(word), pfile);
	part = word;
	if (i==1) xsum = word;
	else xsum ^= word;
	fwrite(&word, 1 , sizeRead, sfile);
	word = 0;
	while ((sizeRead = fread(&word , 1 , sizeof(word) , pfile))) {
	    fwrite(&word, 1, sizeRead, sfile); 
	    part ^= word;
	    xsum ^= word;
	    word = 0;
	}	
	fclose (pfile);
	if (part != partRead) printf("file %d corrupted\n" , i);
	i++;
	part = 0;
    }
  }
  fclose(sfile);
  
  if (xsumExpected!=0) {
      if (xsumExpected==xsum) printf("Checksum match\n");
      else printf("Checksum doesn't match:\nChecksum calculated=%d\t Checksum expected=%d\n",xsum,xsumExpected);
  }

    
  return 0;
}
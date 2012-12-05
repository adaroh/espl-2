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
  int size = 2048;
  
  char *filename = argv[argc-1];
  int len = strlen(filename)+7;
  int sizeRead = 0;
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


  return 0;
}
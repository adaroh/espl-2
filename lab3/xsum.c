#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv) {
  if (argc == 1) {
    printf("enter file names\n");
    return 0;
  }
  int xflag = 0;
  int opt;
  while ((opt = getopt(argc, argv, "hx:")) != -1) {
      switch (opt) {
      case 'h':
	printf("OPTIONS\n\t-h  print a summary of options and exit\n\t-x  print the checksum as a hexadecimal rather than decimal number.\n");
	exit(0);
	break;
      case 'x':
	xflag = 1;
	  break;
      default: /* '?' */
	fprintf(stderr, "Usage: %s [-x] [-h] filename\n", argv[0]);
	exit(EXIT_FAILURE);
      }
  }
  
  FILE *file = fopen(argv[argc-1],"r");
  unsigned int word;
  unsigned int xsum;
  fread(&xsum,sizeof(xsum),1,file);
  while(fread(&word, sizeof(word), 1, file)) {
    xsum ^= word;
  }
  if (xflag==0) {
    printf("Checksum is %d\n",xsum);
  } else {
    printf("Checksum is 0x%x\n",xsum);
  }
  fclose(file);
  
  
  return 0;
}



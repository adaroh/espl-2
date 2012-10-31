#include <stdio.h>
#include <stdlib.h>
#include "fgetname.h"
#include "namelist.h"
#include <string.h>

int main(int argc, char **argv) {
  char* words[] = { "auto","double","int","long", "break","else","long","switch", "case","enum","register","typedef", "char","extern","return","union", "const","float","short","unsigned", "continue","for","signed","void", "default","goto","sizeof","volatile", "do","if","static","while" };
  
  if (argc == 1) {
    printf("enter file names\n");
    return 0;
  }
  int fileNum, k, flag;
  char name[NAMELEN];
  namelist nl = make_namelist();
  for (fileNum = 1; fileNum < argc; fileNum++) {
    FILE *file = fopen (argv[fileNum],"r");
	while(fgetname(name, sizeof(name), file)) {
	  flag=1;
	  for (k=0; k<32; k++) {
	    if (!(strcmp(words[k],name))) {
	      flag=0;
	    }
	  }
	  if (flag==1) {
	    add_name(nl, name);
	  }
	}
    fclose(file);
  }
  
  
  //size_t structs_len = sizeof(nl) / sizeof(struct st_ex);
  qsort((nl->names), (nl->size), sizeof(struct namestat), strcmp);
  int i;
  for (i=0; i!=nl->size; i++) {
    printf ("%s %d\n", nl->names[i].name , nl->names[i].count);
  }
  
  return 0;
}
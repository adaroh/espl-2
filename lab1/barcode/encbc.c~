#include <stdio.h>
#include "bclib.h"

int main(int argc, char **argv){
	int i,j,flag;
	int index = 0;
	int barcode[BC_WIDTH][BC_NBITS] = {0};
	for (i=1; i<argc; i++) {
	    j=0;
	    flag=1;
	    while (flag==1 && i<argc) {
		if (argv[i][j] != 0)
		    bc_char2bits(argv[i][j], barcode[index]);
		else if (i!=argc-1) {
		    flag=0;
		    bc_char2bits(' ', barcode[index]);
		} else flag=0;
		j++;
		index++;
	    }  
	}
	for (i=0; i<BC_NBITS; i++) {
	    for (j=0; j<BC_WIDTH; j++) {
		if (barcode[j][i] == 0) printf(" ");
		else printf ("#");
	    }
	    printf("\n");
	}	
	
  
	return 0;
}
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int cmpstr(char *str1, char *str2) {
    while (*str1) {
	if (str1[0] != str2[0]) break;
	str1++;
	str2++;
    }
    if (str1[0]==str2[0]) return 0;
    if (str1[0]>str2[0]) return 1;
    return 2;
}

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int cmpstr(char *str1, char *str2) {
    int sum1,sum2;
    sum1=0;
    sum2=0;
    while (*str1) {
	sum1=(sum1<<3) + (sum1<<1) + (*str1);// + (*str1 - '0');
	str1++;
    }
    while (*str2) {
	sum2=(sum2<<3) + (sum2<<1) + (*str2);// + (*str2 - '0');
	str2++;
    }
    //printf("sum1=%d\nsum2=%d\n", sum1,sum2);
    if (sum1>sum2) return 1;
    else if (sum2>sum1) return 2;
    return 0;
}

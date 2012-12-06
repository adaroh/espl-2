#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
int fopenr(char *name, int flags);
int freadr(int fd, char *buf, int size);
int fcloser(int fd);
int fopenw(char *name, int flags);
int fwriter(int fd, char *buf, int size);
int innerloop(int *done, int pfile, int sfile);

/*
void merge(char *part, char* str, int num) {
  printf("str=%s\npart=%s\n",str,part);
  char buf[10];
  sprintf(buf, "%d", num);
  strcat(part,"part/");
  strcat(part,str);
  strcat(part,".");
  if (num<10) strcat(part, "0");
  strcat(part,buf);
  printf("str=%s\npart=%s\n",str,part);
}
*/
void printstr(char *str) {
  printf("str=%s\n",str);
}
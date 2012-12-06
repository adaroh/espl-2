#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
int fopenr(char *name, int flags);
int freadr(int fd, char *buf, int size);
int fcloser(int fd);
int fopenw(char *name, int flags);
int fwriter(int fd, char *buf, int size);
void innerloop(int *done, int pfile, int sfile);


void merge(char *part, char* str, int num) {
  char buf[10];
  sprintf(buf, "%d", num);
  strcat(part,"part/");
  strcat(part,str);
  strcat(part,".");
  if (num<10) strcat(part, "0");
  strcat(part,buf);
}
/*
void innerloop(int *done, int pfile, int sfile ) {
	int flag=1;
	int count=0;
	char *xsum = "1234";
	char buffer[4];
	int sizeRead;
  	while ((flag) && (*done)) {
	    sizeRead=0;
	    if (count==0) {
	      fwriter(pfile,xsum, 4);
	      count=4;
	    }
	    sizeRead = freadr(sfile , buffer, 4);
	    count += sizeRead;
	    if (sizeRead>0) {
	      fwriter(pfile,buffer, sizeRead);
	    } else {
	      (*done)=0;
	    }
	    if (count >=2048) {
	      flag =0;
	    }
	}
	fcloser(pfile);
	if (sizeRead == 0) {
	  (*done) =0;
	}
}
 */

int main2() {
  int size = 2048;
  char *filename = "flower.jpg";
  //int len = strlen(filename)+7;
  int sizeRead = 0;
  int count;
  int i=1;
  int flag = 1;
  int sfile = fopenr(filename, 0);
  char partname[100];
  int pfile;
  int done = 1;
  
  while ((done==1) && (i<3)) {
	partname[0] = 0;
	merge (partname, filename, i);
	pfile = fopenw(partname, 577);
	printf("filename=%s\npartname=%s\n",filename,partname);
	count=0;
	flag=1;
	printf("done=%d\npfile=%d\nsfile=%d\n",done,pfile,sfile);
	innerloop(&done,pfile,sfile);

	i++;
  }
  
  fcloser(sfile);
  return 0;
}
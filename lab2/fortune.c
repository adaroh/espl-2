#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  char str[128];
  int counter=0;
//  printf("%s\n", argv[1]);
  FILE *file;
  file = fopen (argv[1],"r");
  if (file == 0) perror ("Error opening the file\n");
//  printf("bla\n");
  do {
    str[0] = 0;
    fgets(str, 128, file);
    counter++;
  } while (str[0] != 0);
  counter--;
//  printf("Num of lines: %d\n", counter);
  srand ( time(NULL) );
  int randNum = (rand() %counter);
//  printf("Randomed number: %d\n", randNum);
  fclose(file);
  file = fopen (argv[1],"r");
  if (file == 0) perror ("Error opening the file\n");
  int i;
  for (i=0; i<=randNum; i++) {
        str[0] = 0;
    fgets(str, 128, file);
  }
//  printf("Randomed line:\n");
  printf("%s", str);
  return 0;
}
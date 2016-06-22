/*
this file takes in a .csv file and prints the line-of-best-fit for each column relative to the target (first) column
*/

int MAX_ELEMENT_SIZE = 1000000000; //maximum size of digits allowed in data

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <pthread.h>

char *linear_regression(int *target_data, int *other_data);

int main(int argc, char **argv) {

  //argv[1] is expected to be a 2D array - need to implement error handling
  FILE *fp;
  int colcount = 0;
  int rowcount = 1;

  fp = fopen(argv[1], "r"); //open file in argv[1]

  //check to see if file was successfully opened
  if(fp == NULL) {
    printf("Error openning file");
    exit(0);
  }

  //determine number of rows and number of columns
  int colcount_determined = 0;
  while(1) {
    char ch = getc(fp);
    if(ch == EOF) break;
    if(ch == ',' || ch == 13) { //char 13 is carrier return, the next line character in csv
      if(!colcount_determined) colcount++;
      if(ch == 13) {
	rowcount++;
	colcount_determined++;
      }
    }
  }

  rewind(fp); //move pointer back to beginning of fp

  double complete_data_set[rowcount][colcount]; //array to be filled with all data

  //fill complete_data_set with file data
  char *temp;
  int temp_pointer = 0;
  for(int i=0;i<rowcount;i++) {
    for(int j=0;j<colcount;j++) {
      while(1) {
	char ch = getc(fp);
	temp[temp_pointer] = ch;
	temp_pointer++;
	if(ch == ',' || ch == 13 || ch == EOF) {
	  complete_data_set[i][j] = strtod(temp, NULL);
	  temp_pointer = 0;
	  break;
	}
      }
    }
  }

  for(int i=0;i<rowcount;i++) {
    for(int j=0;j<colcount;j++)
      printf("%lf ", complete_data_set[i][j]);
    printf("\n");
  }

  //separate 2 dimensional array into multiple 1 dimensional arrays

  //set up individual thread for each regression to be run on

  //launch linear_regression on each thread

}

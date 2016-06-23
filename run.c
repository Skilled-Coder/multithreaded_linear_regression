/*
this file takes in a .csv file and prints the line-of-best-fit for each row relative to the target (first) row
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <pthread.h>

struct thread_args {
  int thread_id;
  double *target_row;
  double *other_row;
};

void *linear_regression(void *thread_args_array){
  struct thread_args *thread_data;
  thread_data = (struct thread_args *) thread_args_array;
  int thread_id = thread_data->thread_id;
  double *target_row = thread_data->target_row;
  double *other_row = thread_data->other_row;

  for(int i=0;i<sizeof(other_row);i++)
    printf("%lf ", other_row[i]);

  printf("\n");

  pthread_exit(NULL);
}

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

  pthread_t threads[colcount-1]; //initialize colcount-1 threads to run on
  int thread_temp;
  struct thread_args thread_args_array[colcount-1];

  //check if data was inserted correctly
  //for(int i=0;i<rowcount;i++) {
  //  for(int j=0;j<colcount;j++) {
  //    printf("%lf ", complete_data_set[i][j]);
  //  }
  //  printf("\n");
  //}

  //load target and other data into each thread_args_array then launch linear_regression
  for(int i=0;i<rowcount-1;i++) {
    thread_args_array[i].thread_id = i;
    thread_args_array[i].target_row = complete_data_set[0];//WARNING: this row is being passed into every thread, so DO NOT EDIT while in thread
    thread_args_array[i].other_row = complete_data_set[i-1];
    thread_temp = pthread_create(&threads[i], NULL, linear_regression, (void *) &thread_args_array[i]);
  }

  //launch linear_regression on each thread

}

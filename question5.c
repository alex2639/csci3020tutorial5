#define _XOPEN_SOURCE 600 // required for barriers to work
#define NUM_THREADS 10

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct{
  double grade;
}student;

double total_grade=0;
double total_bellcurve=0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *read_grades(){
  FILE *file=fopen("grades.txt","r");

}

void *save_bellcurve(void *arg){
  student *data=arg;

  pthread_mutex_lock(&mutex);
  total_grade += data->grade;
  data->grade=data->grade*1.5;
  total_bellcurve += data->grade;
  printf("%f\n", data->grade);
  FILE *file=fopen("bellcurve.txt","wa");
  fprintf(file, "%f\n", data->grade);
  pthread_mutex_unlock(&mutex);

  pthread_exit(NULL);
}

int main(void){
  pthread_t threads[NUM_THREADS];
  student grades[NUM_THREADS];
  int rc,grade;
  for(int i=0;i<NUM_THREADS;i++){
    printf("Enter grade #%d: ", i+1);
    scanf("%d", &grade);
    grades[i]=grade;

  }
  for(int i=0;i<NUM_THREADS;i++){
    bell_curve_grade *arg=malloc(sizeof *arg);
    arg->grade=grades[i];
    rc=pthread_create(&threads[i],NULL,bell_curve,arg);

    if(rc){
      exit(-1);
    }
  }
  pthread_exit(NULL);

  return 0;
}

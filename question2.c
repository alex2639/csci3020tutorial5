#define _XOPEN_SOURCE 600 // required for barriers to work
#define NUM_THREADS 5

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct{
  double grade;
}bell_curve_grade;

void *bell_curve(void *arg){
  bell_curve_grade *data=arg;

  data->grade=data->grade*1.5;
  printf("%f\n", data->grade);
  pthread_exit(NULL);
}

int main(void){
  pthread_t threads[NUM_THREADS];
  int *grades=NULL;
  grades=(int *)calloc(NUM_THREADS,sizeof(int));

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

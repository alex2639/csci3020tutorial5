#define _XOPEN_SOURCE 600 // required for barriers to work
#define NUM_THREADS 10

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct{
  int grade;
}student;

int total_grade=0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *class_total(void *arg){
  student *data=arg;

  pthread_mutex_lock(&mutex);
  //printf("%d + %d = ", total_grade,data->grade);
  total_grade += data->grade;
  //printf("%d\n", total_grade);
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);
}

int main(void){
  pthread_t threads[NUM_THREADS];
  student grades[NUM_THREADS];
  pthread_mutex_init(&mutex, NULL);

  int rc,grade;
  for(int i=0;i<NUM_THREADS;i++){
    printf("Enter grade #%d: ", i+1);
    scanf("%d", &grade);
    grades[i].grade=grade;
  }

  for(int i=0;i<NUM_THREADS;i++){
    student *arg=malloc(sizeof *arg);
    arg->grade=grades[i].grade;

    pthread_mutex_lock(&mutex);
    rc=pthread_create(&threads[i],NULL,class_total,arg);

    if(rc){
      exit(-1);
    }
    pthread_mutex_unlock(&mutex);
    pthread_join(threads[i],NULL);

  }
  printf("Sum: %d\n", total_grade);
  pthread_exit(NULL);

  return 0;
}

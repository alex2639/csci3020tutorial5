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
pthread_barrier_t barrier;
student grades[NUM_THREADS];

void *read_grades(){
  printf("Reading grades\n");
  FILE *file=fopen("grades.txt","r");
  char* line;
  int i=0;
  while(scanf(file,line)!=EOF){
    //grades[i].grade=stoi(line);
    printf("%f\n", atof(line));
    grades[i].grade=atof(line);
    //printf("%f\n", atof(line));
  }
  pthread_exit(NULL);
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
  //student grades[NUM_THREADS];
  pthread_t read_thread;
  int rc;
  //printf("Reading grades\n");
  rc=pthread_create(&read_thread,NULL,read_grades,NULL);
  //pthread_join(read_thread,NULL);
  pthread_barrier_wait(&barrier);
  printf("Reading done\n");

  for(int i=0;i<NUM_THREADS;i++){
    student *arg=malloc(sizeof *arg);
    arg->grade=grades[i].grade;
    pthread_mutex_lock(&mutex);
    rc=pthread_create(&threads[i],NULL,save_bellcurve,arg);

    if(rc){
      exit(-1);
    }
    pthread_mutex_lock(&mutex);
    pthread_join(threads[i],NULL);
  }
  double average_before=total_grade/NUM_THREADS;
  double average_after=total_bellcurve/NUM_THREADS;
  printf("Average before bellcurve: %f\n", average_before);
  printf("Average after bellcurve: %f\n", average_after);
  pthread_exit(NULL);

  return 0;
}

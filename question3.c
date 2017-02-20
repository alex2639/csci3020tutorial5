#define _XOPEN_SOURCE 600 // required for barriers to work
#define NUM_THREADS 5
#define MAX_LEN 256

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

typedef struct{
  double grade;
  char name[MAX_LEN];
  int id;
}student;

void *bell_curve(void *arg){
  student *data=arg;

  data->grade=data->grade*1.5;
  printf("Student: %s id: %d grade: %f\n", data->name, data->id,data->grade);
  pthread_exit(NULL);
}

int main(void){
  pthread_t threads[NUM_THREADS];
  student students[NUM_THREADS];

  int rc,grade,id;
  char name[MAX_LEN];
  for(int i=0;i<NUM_THREADS;i++){
    printf("Enter name of student #%d: ", i+1);
    scanf("%s",name);
    printf("Enter student id for %s: ", name);
    scanf("%d",&id);
    printf("Enter grade #%d: ", i+1);
    scanf("%d", &grade);
    students[i].grade=grade;
    strcpy(students[i].name,name);
    students[i].id=id;
  }

  for(int i=0;i<NUM_THREADS;i++){
    student *arg=malloc(sizeof *arg);
    arg->grade=students[i].grade;
    strcpy(arg->name,students[i].name);
    arg->id=students[i].id;

    rc=pthread_create(&threads[i],NULL,bell_curve,arg);

    if(rc){
      exit(-1);
    }
  }
  pthread_exit(NULL);

  return 0;
}

#define _XOPEN_SOURCE 600 // required for barriers to work
#define NUM_THREADS 2
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void *hello_world(){
  printf("Hello world\n");
  pthread_exit(NULL);
}

void *bye(){
  printf("Bye\n");
  pthread_exit(NULL);
}

int main(void)
{
  pthread_t threads[NUM_THREADS];
  int rc;
  for(int i=0;i<NUM_THREADS;i++){
    if(i%2==0){
      rc=pthread_create(&threads[i],NULL,hello_world, (void *)i);
    }else{
      rc=pthread_create(&threads[i],NULL,bye, (void *)i);
    }

    if(rc){
      exit(-1);
    }
  }
  pthread_exit(NULL);

  return 0;
}

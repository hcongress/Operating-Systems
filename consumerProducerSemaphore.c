/*
Class: CPSC 346-01 & CPSC 346-02
Team Member 1: Hunter Congress
Team Member 2: Andreqw Flagstead
GU Username of project lead: hcongress
Pgm Name: proj6.c
Pgm Desc: uses counting semaphores
Usage: ./a.out
*/
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#define PROD 0
#define CONS 1
#define MUTEX 1
#define EMPTY 100
#define FULL 0

 typedef struct
{
  int mutex;
  int empty;
  int full ;
}lock;

void producer(lock*);
void consumer(lock*);
void criticalSection(int);
void semWait(lock*, int);
void semSignal(lock*, int);


lock* semaphore;

int main(int argc, char* argv[])
{


  int schmid;

  schmid = shmget(0,1,0777 |IPC_CREAT);


  semaphore = (lock*)shmat(schmid, 0, 0);


  semaphore->mutex = MUTEX;
  semaphore->empty = EMPTY;
  semaphore->full = FULL;

  printf("Initial semaphore values: mutex = %d, empty = %d, full = %d\n", semaphore->mutex,semaphore->empty, semaphore->full);


pid_t pid;
pid = fork();

if(pid < 0)
{
  fprintf(stderr,"Child could not be created");
}
else
{
  if(pid == 0)
  {
    consumer(semaphore);
  }
  else
  {
    producer(semaphore);
    wait(NULL);
  }



}
printf("Final semaphore values: mutex = %d, empty = %d, full = %d\n", semaphore->mutex,semaphore->empty, semaphore->full);


shmctl(semaphore-> mutex,IPC_RMID,0);
shmctl(semaphore-> empty,IPC_RMID,0);
shmctl(semaphore-> full,IPC_RMID,0);
shmdt(semaphore);


//printf("Final semaphore values: mutex = %d, empty = %d, full = %d\n", semaphore->mutex,semaphore->empty, semaphore->full);

return 0;
}


void producer(lock* semaphore)
{
  int i;
  for(i = 0; i < 5; i++)
   {
     semWait(semaphore, 1);
     semWait(semaphore, 0);
     criticalSection(PROD);
     semSignal(semaphore, 0);
     semSignal(semaphore, 2);
     sleep(i);
     //printf("Initial semaphore values: mutex = %d, empty = %d, full = %d\n", semaphore->mutex,semaphore->empty, semaphore->full);
      //experiment with putting delays after this line

   }



}


void consumer(lock* semaphore)
{
  int i;
  for (i = 0; i <5; i++)
   {
       semWait(semaphore, 2);
       semWait(semaphore, 0);
       criticalSection(CONS);
       semSignal(semaphore, 0);
       semSignal(semaphore, 1);
       sleep(i+2);
      //  printf("Initial semaphore values: mutex = %d, empty = %d, full = %d\n", semaphore->mutex,semaphore->empty, semaphore->full);
        //experiment with putting delays after this line
   }

}

void criticalSection(int who)
{

  if (who == PROD)
    printf("Producer making an item\n");
 else
    printf("Consumer consuming an item\n");
 }

void semWait(lock* semaphore, int value)
{
    while(semaphore->mutex <= 0);
    if(value == 0)
    {
      semaphore-> mutex--;
      //printf("mutex = %d \n", semaphore->mutex);
    }
    else if(value == 1)
      semaphore-> empty--;
    else if(value== 2)
     semaphore-> full--;//decrement value for mutex and empty?
}

void semSignal(lock* semaphore, int value)
{
  if(value == 0)
  {
    semaphore-> mutex++;
    //printf("mutex = %d \n", semaphore->mutex);
  }
  else if(value == 1)
    semaphore-> empty++;
  else if(value== 2)
   semaphore-> full++;
}

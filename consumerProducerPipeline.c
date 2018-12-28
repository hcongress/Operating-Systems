/*
Class: CPSC 346-01 & CPSC 346-02
Team Member 1: Hunter Congress
Team Member 2: Andreqw Flagstead
GU Username of project lead: hcongress
Pgm Name: proj7.c
Pgm Desc: uses pipes to read and write numbers and checks the if it prime.
Usage: ./a.out 10
*/
#include <wait.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

int is_prime(int);

void* writeFunction(void*);
void* r1(void*);


int MAXNUMS = 100;
struct params
{
 int* num;
 int* fileDest;
 int numbersToGenerate;
 int threadId;
};

typedef struct params param;

 
int main(int argc, char* argv[])
{
  int generate = atoi(argv[1]);
  srand(time(0));
  pthread_t writer,reader1, reader2, reader3;
  
  param param[4];

  int status;

  int fileDest[2];
  int input[MAXNUMS];
  pipe(fileDest);
  int i = 0;

 for (i; i< 4; i++)
  {
  	param[i].fileDest = fileDest;
  	param[i].numbersToGenerate = generate;
  	param[i].num = input;
  	param[i].threadId = i;
  }




  
  status = pthread_create(&writer, NULL, writeFunction, (void*)&param[0]);
  pthread_join(writer, NULL);
  if (status != 0)
  {
	  printf("Thread error\n");
	  exit(-1);
  }
  
  status = pthread_create(&reader1, NULL, r1, (void*)&param[1]);
  //pthread_join(reader1, NULL);
  if (status != 0)
  {
	  printf("Thread error\n");
	  exit(-1);
  }
  
  status = pthread_create(&reader2, NULL, r1, (void*)&param[2]);
   //pthread_join(reader2, NULL);
  if (status != 0)
  {
	  printf("Thread error\n");
	  exit(-1);
  }
 
  status = pthread_create(&reader3, NULL, r1, (void*)&param[3]);
  //pthread_join(reader3, NULL);
  if (status != 0)
  {
	  printf("Thread error\n");
	  exit(-1);
  }
 

  pthread_join(reader1, NULL);
  pthread_join(reader2, NULL);
  pthread_join(reader3, NULL);
  //close(p-> fileDest[0]);
  return 0;
}

int is_prime(int num)
{
 int i = 2;
 while (i < num)
 {
  if (num % i == 0)
     return 0;
  ++i;
 }
 return 1;
}

void* writeFunction(void* parameters)
{	
	param* p = (param*)parameters;
    
	int numberGen = p->numbersToGenerate;
	char conversion [30];
	int i = 0;
	
	for (i;i<numberGen;i++)
	{
		p->num[i] = rand();
        sprintf(conversion,"%d", p->num[i]);
        //printf("%s \n", conversion);
		write(p->fileDest[1], conversion, sizeof(conversion));
		printf("Generated integer: %d \n", p->num[i]);
		sleep(1);
	}
	close(p-> fileDest[1]);
	return NULL;
}

void* r1(void* parameters)
{

	//sleep(2);
	char buffer[30];

	param* p = (param*)parameters;
	int j = p->numbersToGenerate;
	int i = 0;
	int size = 30;
	
	while(read(p->fileDest[0], &buffer, size) > 0)
	{
		//strcpy(buffer,"");
        
		int bufferInt = atoi(buffer);
		//printf("%d check\n",bufferInt);
		int check = is_prime(bufferInt);
		//printf("is prime done");
		if (check == 1)
			if(p->threadId == 1)
			{
			 printf("Reader thread 1 detects a prime number: %d\n", bufferInt);
			}
			else if(p->threadId == 2)
			{
              printf("Reader thread 2 detects a prime number: %d\n", bufferInt);
			}
			else if(p->threadId == 3)
			{
              printf("Reader thread 3 detects a prime number: %d\n", bufferInt);
			}

		//sleep(2);
	}
	
	return NULL;
}




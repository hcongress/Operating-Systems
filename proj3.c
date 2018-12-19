/*
Class: CPSC 346-01 & CPSC 346-02
Team Member 1: Hunter Congress
Team Member 2: N/A 
GU Username of project lead: Hcongress
Pgm Name: proj3.c 
Pgm Desc: exploraiton of the proc file system 
Usage: 1) standard:  ./a.out -s 
Usage: 2) history:  ./a.out -h 
Usage: 3) load:  ./a.out -l 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void standard();
void history();
void load();

int main(int argc, char* argv[])
{


 if (argc != 2)
  {
   fprintf(stderr, "Error: Options required\n"); 
   fprintf(stderr, "usage: ./a.out -s|-h|-l\n\n"); 
   exit(EXIT_FAILURE);
  }
  
 if (!strcmp(argv[1],"-s"))
  standard();
 if (!strcmp(argv[1],"-h"))
  history();
 if (!strcmp(argv[1],"-l"))
  load();
}
/*
pre: none
post: displays CPU vendor_id, model name, and OS version
*/
void standard()
{
 char ch;
 FILE* ifp;
 char str[80];

 /*
 I've deliberately used two different mechanisms for writing to the console.  
 Use whichever suits you.
 strstr locates a substring
 */

 ifp = fopen("/proc/cpuinfo","r");
 while (fgets(str,80,ifp) != NULL)
  if (strstr(str,"vendor_id") || strstr(str,"model name"))
   puts(str); 
 fclose (ifp);

 ifp = fopen("/proc/version","r");
 while ((ch = getc(ifp)) != EOF)
  putchar(ch);
 fclose (ifp);
}

/*
pre: none
post: displays time since the last reboot (DD:HH:MM:SS), time when the system 
      was last booted, number of processes that have been created since the
      last reboot.  
      Hint: strftime could be useful
*/
void history()
{

  time_t rawtime;
  struct tm *info;
   char ch;
   FILE* ifp;
   char str[80];

info = localtime( &rawtime);
	
ifp = fopen("/proc/uptime","r");
while (fgets(str,80,ifp) != NULL)
{

//calculates the days, minutes, hours, and seconds
int time = atoi(str);
int days, hours, minutes, seconds;
days = time/ (3600 * 24);
time = time % (3600 * 24);
hours = time /3600;
time %= 3600;
minutes = time/60;
time %= 60;
seconds = time;

struct tm myTime= {
						.tm_mday = days,
						.tm_hour= hours,
						.tm_min= minutes,
						.tm_sec= seconds
};
  strftime(str, 80,"%D:%H:%M:%S ", &myTime);
  puts(str);
}


//outputs the processes
ifp = fopen("/proc/stat","r");
 while (fgets(str,80,ifp) != NULL)
  if (strstr(str,"processes"))
   puts(str); 
 fclose (ifp);
}

/*
pre: none
post: displays total memory, available memory, load average (avg. number of processes over the last minute) 
*/
void load()
{
 char ch;
 FILE* ifp;
 char str[80];

//gets all the memory info
 ifp = fopen("/proc/meminfo","r");
 while (fgets(str,80,ifp) != NULL)
  if (strstr(str,"MemTotal:") || strstr(str,"MemAvailable:"))
   puts(str); 
 fclose (ifp);

//gets the load average
ifp = fopen("/proc/loadavg","r");
 while ((ch = getc(ifp)) != EOF)
  putchar(ch);
 fclose (ifp);
}

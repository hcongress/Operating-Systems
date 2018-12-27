# Operating Systems

## project 2
a command prompt that counts the number of words in the line.

usage: ./a.out once compiled


## project 3
messing with the /proc file system.  reading the lines from certain areas and out puting them onto the screen.

Usage: 1) standard:  ./a.out -s 
Usage: 2) history:  ./a.out -h 
Usage: 3) load:  ./a.out -l 

## project 6

the producer/consumer problem with linux semaphores.  This use semaphores for shared memory with locking semaphores

Usage: ./a.out

## project 7
similar to project 6 with the producer/consumer porblem but with pipelines.One end of the pipe is the write end.  The other end is the read end.  Multiple reader threads may attempt to read from the read end.  They will block if the pipe is empty.   

Usage: ./a.out 10(the number of times the system should run)

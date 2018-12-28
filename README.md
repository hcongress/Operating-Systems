# Operating Systems

## Word Counter
This is a command prompt that counts the number of words in the line.

usage: ./a.out once compiled


## Terminal Status
This was messing with the /proc file system.  This reads the lines from certain areas and outputs them onto the screen.

Usage: 1) standard:  ./a.out -s 
Usage: 2) history:  ./a.out -h 
Usage: 3) load:  ./a.out -l 

## Consumer / Producer Problem with Semaphores

This program is a take on the producer/consumer problem with Linux semaphores.  This uses forked processes and semaphores for shared memory with locking semaphores

Usage: ./a.out

## Consumer / Producer Peroblem with Pipelines
This project is similar to "Consumer/Producer with Semaphores" project but with pipelines. One end of the pipe is the write end.  The other end is the read end.  Multiple reader threads may attempt to read from the read end.  They will block if the pipe is empty.   

Usage: ./a.out 10(the number of times the system should run)

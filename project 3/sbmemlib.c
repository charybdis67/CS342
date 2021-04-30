#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include "sbmemlib.h"
#include <limits.h>
#include <semaphore.h>


struct Mystruct{
	pid_t pid;
	void *pointer;
};

// Define semaphore(s)
sem_t mutex1;
sem_t mutex2;
// Define your stuctures and variables. 
/* the size (in bytes) of shared memory object */
int size;
int shm_fd;
int processCounter = 0;
void* ptr;
const char* name = "OS";
// Define your data list. 
struct Mystruct sp[10];

int sbmem_init(int segmentsize)
{
	/* power check */
	int remainder = (segmentsize)%2;
	if(remainder != 0)
	{
		return -1;
	}

	int counter = segmentsize;
	while((counter)%2 == 0)
	{
		counter = (counter)/2;
		if(counter == 1)
		{
			continue;
		}
		
	}
	if(counter == 0| counter !=  1 )
	{
		return -1;
	}
	
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, segmentsize);
	size = segmentsize;
	ptr = mmap(0, size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	
	
	return (0); 
}

int sbmem_remove()
{
	shm_unlink(name);
	return (0); 
}

int sbmem_open()
{
	sem_wait(&mutex2);
	if(processCounter > 9){
		sem_post(&mutex2);
		return (-1); 
	}
	else{
		processCounter++;
		sem_post(&mutex2);
		return (0); 
	}

}


void *sbmem_alloc (int size)
{
	



	return (NULL);
}


void sbmem_free (void *p)
{

 
}

int sbmem_close()
{
    
    return (0); 
}


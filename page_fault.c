// Page fault
// Call mmap(), make sure address is page size aligned.
// Access entire file after mapping to main memory - File size = Page size in memory.
// Generate a file with size = 4096 bytes
  
#include "cycles.h"
#include <fcntl.h>
#include <sys/mman.h>

#define NUM_TESTS 1
#define CREATE 0
#define RUN 1

cycles_t start_time = 0;
cycles_t end_time = 0;
cycles_t difference = 0;
cycles_t total = 0;

int main(int argc, char **argv)
{
	//Find system page size.
	long page_size = sysconf(_SC_PAGESIZE);
    //printf("Page size is %ld\n", page_size);

#if 0
	FILE *file;
	file = fopen("./fault.txt", "w+");
	for(int i=0; i<4096; ++i)
	{
		fprintf(file, "a");
	}	
	
	fclose(file);
#endif

	//Map fault.txt to RAM. Then read the entire file; OS will bring in the file to memory only when it is read.
	off_t len;
	char *p;
	int fd;

	fd = open("./fault.txt", O_RDONLY);
	len = 4096;

	p = mmap(0, len, PROT_READ, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED)
	{
		perror("mmap error");
		return 1;
	}
	
	close(fd);

	char c = '\0';

	start_time = begin_cycles();
	c = p[4000];
	end_time = end_cycles();
	difference = end_time - start_time;

	//printf("Cycles taken to read a page from disk to main memory is %lld\n", (total-TSC_OVERHEAD*4096) );
	//printf("Cycles to read each byte from disk is %lld\n", (total-TSC_OVERHEAD*4096)/4096);
	printf("%llu\n", difference - TSC_OVERHEAD);
	
	if (munmap (p, 4096) == -1)
	{
		perror("munmap error");
		return 1;
	}

	return 0;
}


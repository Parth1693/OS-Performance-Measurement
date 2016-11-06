// System call overhead
// syscall used to measure overhead is gettimeofday(). 
// Since the result can be cached from multiple runs, the program is
// rerun multiple times from the python script.

#include <time.h>
#include <sys/time.h>
#include "cycles.h"

#define NUM_TESTS 1

cycles_t start_time = 0;
cycles_t end_time = 0;
cycles_t difference = 0;
cycles_t total = 0;

int main(int argc, char **argv)
{  
	int i;	  
	char buffer[40];
	struct timeval time;
	int ret;
	
	ret = nice(-20);

	for(i=0; i<NUM_TESTS; i++)
	{
		start_time = begin_cycles();
		gettimeofday(&time, NULL);
		end_time = end_cycles();
		difference = end_time - start_time;
		total += difference;
	}

	//strftime(buffer, 40, "Current date/time: %m-%d-%Y/%T", localtime(&time.tv_sec));
	//printf("%s\n",buffer);
	//printf("Average number of clock cycles = %llu\n", (difference- LOOP_OVERHEAD - TSC_OVERHEAD)/NUM_TESTS);
	//printf("%llu\n", (total-TSC_OVERHEAD*NUM_TESTS)/NUM_TESTS);

	printf("%llu\n",total/NUM_TESTS);
	
	return 0;

}

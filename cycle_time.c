//Determine the clock cycle time
//of the clock driving the TSC.
//Since we are using constant TSC, the TSC clock period
//is independent of the CPU clock frequency.

#include "cycles.h"

#define NUM_TESTS 10

cycles_t start_time = 0;
cycles_t end_time = 0;
cycles_t difference = 0;

int main(int argc, char ** argv)
{
	int i;
	cycles_t total = 0;
	int secs = 5;
	float cycle_time;
	int ret;

	ret = nice(-25);

	for(i = 0; i<NUM_TESTS; i++) 
	{
		start_time = begin_cycles();
		sleep(secs);
		end_time = end_cycles();
		difference = end_time - start_time;
		total += difference;
	}

	printf("Number of cycles in %d sec is %lld\n", secs, total);
	cycle_time = ((float)secs * (float)NUM_TESTS)/((float)total);
	printf("Cycle time of CPU is %f ns\n", cycle_time * 1000000000);

	return 0;
}

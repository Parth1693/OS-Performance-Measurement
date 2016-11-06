// Measure the RAM bandwidth by reading and writing an array 
// which occupies the entire L3 cache
#include "cycles.h"

//L3 cache size on the machine is 3MB.
#define ARR_SIZE (3072 * 1024/4)
#define NUM_TESTS 1

cycles_t start_time = 0;
cycles_t end_time = 0;
cycles_t difference = 0;
cycles_t total = 0;

int main(int argc, char *argv[])
{
	int *arr, arr_size;
	int *dest;
	int i,test,num;
	int operation;

	if(argc != 3)
	{
		printf("Invalid arguments\n");
		exit(1);
	}

	arr_size = atoi(argv[1]);
	operation = atoi(argv[2]);  //0 is read ........ 1 is write

	arr = (int*)malloc(arr_size*sizeof(int));
	dest = (int*)malloc(arr_size*sizeof(int));

	if(operation==1)
	{
		//Writing the array
		start_time = begin_cycles();
		memset(arr, 123456, arr_size);
		end_time = end_cycles();
		difference = end_time - start_time;
		
		printf("%llu\n", difference/NUM_TESTS);
		//printf("Cycles to write each byte is %lld\n", difference/(NUM_TESTS*ARR_SIZE*4));
	}
	else
	{
		//Reading the array		
		start_time = begin_cycles();
		memcpy(dest, arr, arr_size);
		end_time = end_cycles();
		difference = end_time - start_time;

		printf("%llu\n", difference/NUM_TESTS);
		//printf("Cycles to read each byte is %lld\n", difference/(NUM_TESTS*ARR_SIZE*4));
	}

	free(arr);

	return 0;

}


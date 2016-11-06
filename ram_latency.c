#include "cycles.h"

#define ARR_SIZE (65*1024)
#define STRIDE 256

#define NUM_TESTS 1

cycles_t start_time = 0;
cycles_t end_time = 0;
cycles_t difference = 0;
cycles_t total = 0;

int main(int argc, char *argv[])
{
	int arr_size,stride,i,test,num_strides;
	int *arr;
	cycles_t *stride_arr;
	cycles_t avg_strided = 0;
	int tot_random_val = 100;
	cycles_t total_random = 0;
	int random_access;

	if(argc != 5)
	{
		printf("Invalid usage\n");
		exit(1);
	}

	arr_size = atoi(argv[1]);
	stride = atoi(argv[2]);	
	random_access =atoi(argv[3]);
	tot_random_val = atoi(argv[4]);

	arr = (int*)malloc(arr_size*sizeof(int));
	

if(random_access == 0) //For strided access
{
	stride_arr = (cycles_t *)calloc(num_strides, sizeof(cycles_t));
	num_strides = arr_size/stride;
	for(test=0;test<NUM_TESTS;test++)
	{
		for(i=0;i<num_strides;i++)
		{
			int val = 0;
			start_time = begin_cycles();
			val = arr[i*stride];
			end_time = end_cycles();
			difference = end_time - start_time;
			stride_arr[i] += difference;
			if(test==0 && i==0)
			{
				//printf("First value for access is %llu cycles\n",difference-TSC_OVERHEAD);
				printf("%llu\n",difference);
			}
		}
	}
		
	for(i=0;i<num_strides;i++)
	{
		avg_strided += stride_arr[i];
	}
	avg_strided = avg_strided/num_strides;

	//printf("Average value for access of array with %d stride is %llu cycles\n", stride, avg_strided/NUM_TESTS );
	//printf("%llu\n",avg_strided/NUM_TESTS);
	free(stride_arr);
}	
else
{
	//For random access
	for(test=0;test<NUM_TESTS;test++)
	{
		for(i=0;i<tot_random_val;i++)
		{
			int index = rand() % arr_size;
			int val = 0;
			start_time = begin_cycles();
			val = arr[index];
			end_time = end_cycles();
			difference = end_time - start_time;
			total_random += difference;
			//if(test==0 && i==0)
			//{
				//printf("First value for access is %llu cycles\n",difference);
			//}
		}
	}
	//printf("Average value for access of array with %d array size is %llu cycles\n", arr_size, total_random/(NUM_TESTS*tot_random_val) );
	printf("%llu\n", total_random/(NUM_TESTS*tot_random_val));
}
	free(arr);
	
	
	return 0;

}

//Measure overhead of reading time using RDTSC instruction.

#include "cycles.h"

#define NUM_TESTS 10000

int main(int argc, char **argv)
{
  int i, j, value, res1, res2;
  cycles_t start, end;
  long long tsccost, tot, a;
  int val=0;
  int ret;
  tot = 0; 

  //ret = nice(-20);   

//RDTSC measurement overhead computation
#if 1
  // TSC overhead	
  for(i=0; i<NUM_TESTS; i++)
  {    
     start = begin_cycles();
     end = end_cycles();

     tsccost = (end - start);

     if (tsccost<0)
     {
        printf("# ERROR!!!   ");
        printf("rdtsc took %lld clock cycles\n", tsccost);
        return 1;
     }
  
     tot = tot + tsccost;
  }

  tsccost = tot/NUM_TESTS;
  //printf("rdtsc takes on average: %lld clock cycles\n", tsccost);  
  printf("%llu\n", tsccost); 
#endif


//For loop overhead computation
#if 0
  tot = 0;
  start = end = 0;

   for(j=0; j<NUM_TESTS;j++)
   {
		// for loop overhead
		start = begin_cycles();
		for(i=0; i<NUM_TESTS; ++i)
		{	
		}
		end = end_cycles();
		tsccost = (int)(end - start);		   

		if (tsccost<0)
		{
			printf("# ERROR!!!   ");
			printf("rdtsc took %lld clock cycles\n", tsccost);
			return 1;
		}

		tot = tot + tsccost;
    }

	tsccost = (tot-(TSC_OVERHEAD*NUM_TESTS))/NUM_TESTS;
	printf("%llu\n",tsccost);
	//printf("for loop takes on average: %lld clock cycles\n", tsccost);
#endif
  return EXIT_SUCCESS;

}


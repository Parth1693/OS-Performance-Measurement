//Measure the overhead to create and run a kernel thread

#include <pthread.h>
#include "cycles.h"

#define NUM_TESTS 10000

cycles_t start_time = 0;
cycles_t end_time = 0;
cycles_t difference = 0;
cycles_t total = 0;

pthread_t trun;
pthread_mutex_t mutex;

void* runFunc(void *arg)
{
	#if 0
		unsigned long i = 0;
		pthread_t id = pthread_self();

		if(pthread_equal(id,tcreate[0]))
		{
		    printf("\n First thread processing\n");
		}
		else
		{
		    printf("\n Second thread processing\n");
		}

		for(i=0; i<(0xFFFFFFFF);i++);
	#endif		
    return NULL;
}

int main(void)
{
    int i = 0;
    int err;
    int count = 0;

    // Kernel thread creation overhead
    for(i = 0; i<NUM_TESTS; i++)
    {
        start_time = begin_cycles();
        err = pthread_create(&(trun), NULL, &runFunc, NULL);
		pthread_join(trun, NULL);
        end_time = end_cycles();
    	
        //if (err != 0)
            //printf("\ncan't create thread :[%s]", strerror(err));
        //else
            //printf("\n Thread created successfully\n");	
        difference =  end_time - start_time;
        total += difference;
    }

	//printf("Thread creation overhead is %llu\n", (difference-LOOP_OVERHEAD-TSC_OVERHEAD)/NUM_TESTS);
    printf("%llu\n", (total-TSC_OVERHEAD*NUM_TESTS)/NUM_TESTS);
	//sleep(1);
    	
    return 0;

}


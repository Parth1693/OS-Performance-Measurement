// Process creation overhead measurement

#include "cycles.h" 
#include <sys/wait.h>

#define NUM_TESTS 10000

cycles_t start_time = 0;
cycles_t end_time = 0;
cycles_t difference = 0;
cycles_t total = 0;

int main(int argc, char **argv)
{
    int counter = 0;
    int status, i;
	
	for(i = 0; i<NUM_TESTS; i++)
	{
		start_time = end_time = 0;
		start_time = begin_cycles();
		pid_t pid = fork();

		// Child process
		if (pid == 0)
		{
			#if 0		
		  	 int i;
		     for (i = 0; i< =5; ++i)
		   	 {
		        printf("child process: counter=%d\n", ++counter);
		   	 }
			#endif
			exit(0);
		}
		else if (pid > 0)
		{
		    // parent process
			waitpid(pid, &status, 0);	        
			end_time = end_cycles();
			difference = (end_time - start_time);
			total += difference;
			
			#if 0		
			int j;
		    for (j = 0; j<5; ++j)
		    {
		        printf("parent process: counter=%d\n", ++counter);
		    }
			#endif
		}
		else
		{
		    // fork failed
		    printf("fork() failed!\n");
		    return 1;
		}
	}

	//printf("Overhead of process creation is %llu\n", (total-(TSC_OVERHEAD*NUM_TESTS))/NUM_TESTS );
    printf("%llu\n", (total-TSC_OVERHEAD*NUM_TESTS)/NUM_TESTS);
    return 0;

}


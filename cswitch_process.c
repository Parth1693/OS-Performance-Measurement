#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <linux/futex.h>
#include <sched.h>
#include "cycles.h"

#define NUM_TESTS 10000

int main(void) 
{
  int i = 0;
  cycles_t start, end, delta, total=0;
  int  nswitches;

  const int shm_id = shmget(IPC_PRIVATE, sizeof (int), IPC_CREAT | 0666);
  const pid_t other = fork();
  
  int* futex = shmat(shm_id, NULL, 0);
  *futex = 0xA;
  
  if (other == 0)  //child thread
  {
    for (i = 0; i < NUM_TESTS; i++) 
    {
      sched_yield();
      while (syscall(SYS_futex, futex, FUTEX_WAIT, 0xA, NULL, NULL, 42)) 
      {
        // retry
        sched_yield();
      }
      *futex = 0xB;
      while (!syscall(SYS_futex, futex, FUTEX_WAKE, 1, NULL, NULL, 42)) 
      {
        // retry
        sched_yield();
      }
    }
    return 0;
  }

     //From here parent
  for (i = 0; i < NUM_TESTS; i++) 
  {
    start = begin_cycles(); 
    *futex = 0xA;
    while (!syscall(SYS_futex, futex, FUTEX_WAKE, 1, NULL, NULL, 42)) 
    {
      // retry
      sched_yield();
    }
    sched_yield();
    while (syscall(SYS_futex, futex, FUTEX_WAIT, 0xB, NULL, NULL, 42)) 
    {
      // retry
      sched_yield();
    }
    end = end_cycles();
    delta = end - start;
    total += delta;
  }
  
  nswitches = NUM_TESTS << 2;
  
  	//printf("Process context switch overhead is %llu cycles\n", (delta - TSC_OVERHEAD - LOOP_OVERHEAD) / nswitches );
 	printf("%llu\n", (total-TSC_OVERHEAD*NUM_TESTS) / nswitches);
	//printf("%llu\n",total/nswitches);
  	wait(futex);
 
	return 0;

}



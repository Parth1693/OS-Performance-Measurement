#include <pthread.h>
#include <sched.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <linux/futex.h>
#include "cycles.h"

#define NUM_TESTS 10000

static void* thread(void* restrict ftx) 
{
  int i;
  int* futex = (int*) ftx;
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
  return NULL;
}

int main(void) 
{
  
  cycles_t start,end,delta,total=0;
  int nswitches, i;
  
  //const int shm_id = shmget(IPC_PRIVATE, sizeof (int), IPC_CREAT | 0666);
  //int* futex = shmat(shm_id, NULL, 0);
  
  int *futex = (int *)malloc(sizeof(int));
  pthread_t thd;

  if (pthread_create(&thd, NULL, thread, futex)) 
  {
    return 1;
  }

  *futex = 0xA;

  
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
    delta = end-start;
    total += delta;
  }

  nswitches = NUM_TESTS << 2;
  //printf("Thread context switch overhead is %llu cycles\n", (delta - TSC_OVERHEAD - LOOP_OVERHEAD) / nswitches );
  //printf("%llu\n",total/nswitches);
  printf("%llu\n", (total-TSC_OVERHEAD*NUM_TESTS) / nswitches);
  
  wait(futex);
  
  return 0;

}


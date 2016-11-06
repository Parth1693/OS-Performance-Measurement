#include <time.h>
#include <linux/sched.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>	
#include <sys/syscall.h>

//#include <linux/preempt.h>

typedef unsigned long long cycles_t;

#define TSC_OVERHEAD 52			//Overhead of using RDTSC instruction to read time stamp.
#define LOOP_OVERHEAD 76300		//Overhead of using 'for' loop to obtain repetitive measurements.

static inline cycles_t begin_cycles()
{
	unsigned int cycles_high0, cycles_low0;
    	asm volatile ("cpuid\n\t"
		  "rdtsc\n\t"
		  "mov %%edx, %0\n\t"
		  "mov %%eax, %1\n\t"
		  : "=r" (cycles_high0), "=r" (cycles_low0)
		  :: "%rax", "%rbx", "%rcx", "%rdx");

	return ( ((cycles_t)cycles_high0 << 32) | (cycles_t)cycles_low0);
}


static inline cycles_t end_cycles()
{
	unsigned int cycles_high1, cycles_low1;

 	asm volatile ("rdtscp\n\t"
		  "mov %%edx, %0\n\t"
		  "mov %%eax, %1\n\t"
		  "cpuid\n\t"
		  : "=r" (cycles_high1), "=r" (cycles_low1)
		  :: "%rax", "%rbx", "%rcx", "%rdx");

	return ( ((cycles_t)cycles_high1 << 32) | (cycles_t)cycles_low1);

}


#include "cycles.h"

#define NUM_TESTS 1

cycles_t start_time = 0;
cycles_t end_time = 0;
cycles_t difference = 0;
cycles_t total = 0;

void func0(void)
{

}

void func1(int a)
{

}

void func2(int a,int b)
{

}

void func3(int a, int b, int c)
{

}

void func4(int a, int b, int c, int d)
{

}

void func5(int a, int b, int c, int d, int e)
{

}

void func6(int a, int b, int c, int d, int e, int f)
{

}

void func7(int a, int b, int c, int d, int e, int f, int g)
{

}

void func8(int a, int b, int c, int d, int e, int f, int g, int h)
{

}

int main(int argc, char *argv[])
{
	int i;
	int ret;
	int which;
	if(argc != 2)
	{
		printf("Invalid usage\n");
		exit(1);
	}
	which = atoi(argv[1]);

	ret = nice(-20);

  	for(i=0; i<NUM_TESTS; i++)
  	{
  		switch(which)
  		{
  			case 0:
  				start_time = begin_cycles();
  				func0();
  				end_time = end_cycles();
  				break;
  			case 1:
  				start_time = begin_cycles();
  				func1(1);
  				end_time = end_cycles();
  				break;
  			case 2:
  				start_time = begin_cycles();
  				func2(1,2);
  				end_time = end_cycles();
  				break;
  			case 3:
  				start_time = begin_cycles();
  				func3(1,2,3);
  				end_time = end_cycles();
  				break;
  			case 4:
  				start_time = begin_cycles();
  				func4(1,2,3,4);
  				end_time = end_cycles();
  				break;
  			case 5:
  				start_time = begin_cycles();
  				func5(1,2,3,4,5);
  				end_time = end_cycles();
  				break;
  			case 6:
  				start_time = begin_cycles();
  				func6(1,2,3,4,5,6);
  				end_time = end_cycles();
  				break;
  			case 7:
  				start_time = begin_cycles();
  				func7(1,2,3,4,5,6,7);
  				end_time = end_cycles();
  				break;
  			case 8:
  				start_time = begin_cycles();
  				func8(1,2,3,4,5,6,7,8);
  				end_time = end_cycles();
  				break;
  			default:
  				break;  			  			  			

  		}

	  	//start_time = begin_cycles();
		//Call functions with variable number of arguments - Uncomment one function at a time.
		//func0();	
		//func1(1); 
		//func2(1, 2);
		//func3(1, 2, 3);
		//func4(1, 2, 3, 4);
		//func5(1, 2, 3, 4, 5);
		//func6(1, 2, 3, 4, 5, 6);
		//func7(1, 2, 3, 4, 5, 6, 7);
		//func8(1, 2, 3, 4, 5, 6, 7, 8);
		//end_time = end_cycles();
  		
  		difference = end_time - start_time;
  		total += difference;
  	}

	//printf("Average number of clock cycles = %lld\n", (difference-LOOP_OVERHEAD-TSC_OVERHEAD)/(NUM_TESTS) );
	printf("%llu\n", total/NUM_TESTS);
	return 0;

}


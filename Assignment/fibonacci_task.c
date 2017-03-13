#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

int fib(int n){
	int less, more;
	if(n<2)
	{
		printf("n is %d \n",n);
		return n;
	}
	else{
	omp_set_nested(1);	
	omp_set_dynamic(0);
	#pragma omp parallel shared(n) \
	num_threads(3)
	{
		#pragma omp single
		{
		#pragma omp task
		{
		printf("section one, n is %d um_threads %d, thread id %d \n",n, omp_get_num_threads(), omp_get_thread_num() );
		less = fib(n-1);
		}
		#pragma omp task
		{
		printf("section two, n is %d  num_threads %d, thread id %d \n",n, omp_get_num_threads(), omp_get_thread_num());
		more = fib(n-2);
		}
		}
		printf("loop  \n");
	}
		return less + more;
	}
}

int main(int argc, char* argv[]){
	int result;
	int number;
	number = strtol(argv[1], NULL, 10);
	printf("Doing sequential fibonacci: \n");
	result = fib(number);
	printf("Result is %d \n",result);
	return 0;
}

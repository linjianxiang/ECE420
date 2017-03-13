#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int fib(int n){
	if(n<2)
		return n;
	else{
		return fib(n-1) + fib(n-2);
	}
}

int main(int argc, char *argv[]){
	int number;
	number = strtol(argv[1],NULL,10);
	int result;
	printf("Doing sequential fibonacci: \n");
	result = fib(number);
	printf("Result is %d \n",result);
	return 0;
}

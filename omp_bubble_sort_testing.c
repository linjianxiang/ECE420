#include <stdio.h>
#include <omp.h>
int main(void){
int list_length;
int n = 20;
int* b;
int a[20] ={5,29,4,51,9,0,3,1,3,10,15,0,4,91,9,4,9,1,3,0};
int i;
//int thread_count = 2;
int thread_count = 2;
int tmp = 0;
# pragma omp parallel for num_threads(thread_count) \
default(none) private(i, tmp)\
 shared(n,a)// reduction(+:a) 
for (list_length = n; list_length >=2; list_length --)
	for (i = 0; i<list_length -1 ; i++)
		if(a[i] >a[i+1]){
			tmp = a[i];
			a[i] = a[i+1];
			a[i+1] = tmp;
		}
for (i =0; i< n; i++){
	printf("%d \n ",a[i]);
}
}


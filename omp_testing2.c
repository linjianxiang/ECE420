#include <stdio.h>
#include <omp.h>
int main(void){
double sum = 0.0;
int thread_count = 4;
int n = 20;
int k;
double factor;
# pragma omp parallel for num_threads(thread_count) \
default(none) reduction(+:sum) private(k, factor) \
 shared(n)
for (k = 0; k < n; k++) {
printf("the %d thread, k is %d \n",omp_get_thread_num(),k);
if (k % 2 == 0)
	factor = 1.0;
else
	factor = -1.0;
printf("the sum before is %f \n",sum);
sum += factor/(2*k+1);
printf("the factor is %f, the sum is %f \n",factor,sum);
}
printf("the sum is %f \n",sum);
}

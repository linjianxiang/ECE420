#include <stdio.h>
#include <omp.h>
#define FIRSTPRIVATE

int main (void)
{
int i = 10;
#ifndef FIRSTPRIVATE
#pragma omp parallel num_threads(i)  private(i)
{
printf("thread %d: i = %d\n", omp_get_thread_num(), i);
i = 1000 + omp_get_thread_num();
}
#else
#pragma omp parallel num_threads(5) reduction(+:i)// firstprivate(i)
{
printf("thread %d: i = %d\n", omp_get_thread_num(), i);
i = 1000 + omp_get_thread_num();
}
#endif
printf("i = %d\n", i);
return 0;
}











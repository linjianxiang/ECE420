#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
void* thread_function(void * arg)
{

// int * b = (int *) malloc(sizeof(int));
// *b = 10;
// printf("the *b is %d \n",*b);
// printf("the b is %x \n",b);
// pthread_exit((void*)b);



 int number = 1;
 int * b;
 b = &number;
 printf("the *b is %d \n",*b);
 printf("the b is %x \n",b);
 printf("the &number is %x \n",&number);
 pthread_exit((void*)b);


}
int main()
{
 pthread_t thread_id;
 int *status;

 pthread_create(&thread_id, NULL, &thread_function, NULL);

 pthread_join(thread_id, (void**)&status);

 printf("The worker thread has returned the status %d\n", *status);
 pthread_exit(NULL);
}


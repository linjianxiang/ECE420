#include <pthread.h>
#include <stdio.h>
#define BSIZE 3
#define NUMITEMS 6
typedef struct {
 char buf[BSIZE];
 int occupied;
 int nextin, nextout;
 pthread_mutex_t mutex;
 pthread_cond_t more;
 pthread_cond_t less;
} buffer_t;
buffer_t buffer;
void * producer(void *);
void * consumer(void *);
#define NUM_THREADS 2
pthread_t tid[NUM_THREADS]; /* array of thread IDs */
int main()
{
 int i;
 pthread_cond_init(&(buffer.more), NULL);
 pthread_cond_init(&(buffer.less), NULL);
/*buffer initialize*/
 buffer.occupied = 0;
 buffer.nextin = 0;
 buffer.nextout = 0;

 pthread_create(&tid[1], NULL, consumer, NULL);
 pthread_create(&tid[0], NULL, producer, NULL);
 for ( i = 0; i < NUM_THREADS; i++)
 pthread_join(tid[i], NULL);

 printf("\nmain() reporting that all %d threads have terminated\n", i);
 return 0;

} /* main */
void * producer(void * parm)
{
 char item[NUMITEMS]="HELLO.";
 int i;

 printf("producer started.\n");

 for(i=0;i<NUMITEMS;i++)
 { /* produce an item, one character from item[] */

 if (item[i] == '\0') break; /* Quit if at end of string. */

 printf("producer mutex lock \n");
 pthread_mutex_lock(&(buffer.mutex));

 if (buffer.occupied >= BSIZE) printf("producer waiting.\n");
 while (buffer.occupied >= BSIZE){
	printf("In producer, buffer.occupied >= BSIZE, occupied is %d \n", buffer.occupied);
	pthread_cond_wait(&(buffer.less), &(buffer.mutex) );
}

 printf("producer executing.\n");
 buffer.buf[buffer.nextin] = item[i];
 buffer.nextin++;
 buffer.nextin %= BSIZE;
 buffer.occupied++;



 pthread_cond_signal(&(buffer.more));
 pthread_mutex_unlock(&(buffer.mutex));
 }
 printf("producer exiting.\n");
 pthread_exit(0);
}
void * consumer(void * parm)
{
 char item;
 int i;
 printf("consumer started.\n");
 for(i=0;i<NUMITEMS;i++){

	
 	while( buffer.occupied == 0){
		printf("waiting for producer produce, occupied = 0 \n");
		pthread_cond_wait(&(buffer.more),&(buffer.mutex));
		printf("producer produces, condition released \n");
	}
	if(buffer.occupied >= BSIZE){
		printf("buffer.occupied >= bsizw \n");
		item = buffer.buf[buffer.nextout];
		buffer.nextout++;
		buffer.nextout %= BSIZE;
		buffer.occupied--;
	}
	else{
		pthread_cond_signal(&(buffer.less));
		printf("buffer.occupied < BSIZW \n");
   		pthread_mutex_lock(&(buffer.mutex));
		printf("cusumer mutex released \n");
		item = buffer.buf[buffer.nextout];
		buffer.nextout++;
		buffer.nextout %= BSIZE;
		buffer.occupied--;
		pthread_mutex_unlock(&(buffer.mutex));
	}
	printf("item is %c \n",item);
 }
 printf("consumer exiting.\n");
 pthread_exit(0);
}

#include  <stdio.h>
#include <stdlib.h>



int main(){
int a = 10;
int* b = 100;
char *s = (char *)("56002500");
int i = strtol(s, NULL, 16);
printf("i is %d \n",i);


//printf("a is %d \n b is %d",a,b);
//printf("a is %f \n b is %f", &a, &b);



getchar();
return 0;
}
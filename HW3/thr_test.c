#include <stdio.h>
#include <pthread.h>

void *foo(void *input){
	//pthread_exit(NULL);
}

int main(){
	int i=0,t=1;
	pthread_t thr;
	while(t){
		if(pthread_create(&thr,NULL,foo,(void *)NULL)!=0) return 2;
		//pthread_join(thr,NULL);
		i++;
		printf("i=%d\n",i);
	}
	return 0;
}

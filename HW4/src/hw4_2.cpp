#include <cstdio>
#include <pthread.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int count = 0;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER, mutex2 = PTHREAD_MUTEX_INITIALIZER;

void *estimate_pi(void *input_info)
{
    int *input = (int *)input_info;
    pthread_mutex_unlock(&mutex1);

    double x = 0, y = 0;

    for(int i = 0; i < *input; i++)
    {
        // (double)rand() / RAND_MAX可產生[0, 1]的小數
        x = (double)rand() / RAND_MAX * 2 + (-1);
        y = (double)rand() / RAND_MAX * 2 + (-1);

        if(x * x + y * y <= 1)
        {
            pthread_mutex_lock(&mutex2);
            count++;
            pthread_mutex_unlock(&mutex2);
        }
    }
    
    pthread_exit(NULL);
} 

int main (int argc, const char * argv[]) 
{
    int thread_num = 0, point_num = 0;
	scanf("%d %d ", &thread_num, &point_num);

    srand(time(NULL));

    //每個thread分配一些point去算
    pthread_t thread[thread_num];
    int input_to_func[thread_num];

    for(int i = 0; i < thread_num ; i++)
    {
        if(i == thread_num - 1) input_to_func[i] = point_num / thread_num + point_num % thread_num; //最後一個要多負責處理那些除不盡的point數
        else input_to_func[i] = point_num / thread_num;

        pthread_mutex_lock(&mutex1);
        pthread_create(&thread[i % thread_num], NULL, estimate_pi, (void *)&input_to_func[i]);
    }

    for(int i = 0; i < thread_num ; i++) pthread_join(thread[i], NULL);

	printf("get: %d\nPi: %lf\n", count, ((double)count / (double)point_num * 4));

    return 0;
}
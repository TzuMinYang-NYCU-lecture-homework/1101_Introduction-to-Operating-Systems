#include <string>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

struct partition
{
    int beg_pos = 0, end_pos = 0;
};

string series = "";
int count[3] = {0};
partition sub_array[3];

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER, mutex2 = PTHREAD_MUTEX_INITIALIZER;
sem_t sem0[2],sem1_2[2];

void *count_012(void *input_info)
{
    int *input = (int *)input_info;
    pthread_mutex_unlock(&mutex1);

    for(int i = sub_array[*input].beg_pos; i <= sub_array[*input].end_pos; i++)
    {
        pthread_mutex_lock(&mutex2);
        count[series.at(i) - '0']++;
        pthread_mutex_unlock(&mutex2);
    }

    if(*input != 0) // 1 2做完通知0，然後等前一個人輸出完
    {
        sem_post(&sem0[*input - 1]);
        sem_wait(&sem1_2[*input - 1]);
    }
        
    else // 0要等別人做完
    {
        sem_wait(&sem0[0]);
        sem_wait(&sem0[1]);
    }
    
    printf("%d: %d\n", *input, count[*input]);

    if(*input < 2) // 通知下一個人，2沒有下一個不用通知
        sem_post(&sem1_2[*input - 1 + 1]);
    
    pthread_exit(NULL);
} 

int main (int argc, const char * argv[]) 
{
    sem_init(&sem0[0], 0, 0);
    sem_init(&sem0[1], 0, 0);
    sem_init(&sem1_2[0], 0, 0);
    sem_init(&sem1_2[1], 0, 0);

    int thread_num = 3, series_len = 0;
	cin >> series_len >> series;

    //切出每個partition的起始與結束
    for(int i = 0; i < thread_num; i++)
    {
        sub_array[i].beg_pos = series_len / thread_num * i;
        sub_array[i].end_pos = series_len / thread_num * (i + 1) - 1;
    }
    sub_array[thread_num - 1].end_pos = series_len - 1; //不能整除的話, 上面for給最後一個的end會有問題, end的位置到最後就好

    //對每個partition做計算012
    pthread_t thread[thread_num];
    int input_to_func[thread_num];

    for(int i = 0; i < thread_num ; i++)
    {
        input_to_func[i] = i;
        pthread_mutex_lock(&mutex1);
        pthread_create(&thread[i % thread_num], NULL, count_012, (void *)&input_to_func[i]);
    }

    for(int i = 0; i < thread_num ; i++) pthread_join(thread[i], NULL);

	//for(int i = 0; i < 3; i++) printf("%d: %d\n", i, count[i]);

    return 0;
}
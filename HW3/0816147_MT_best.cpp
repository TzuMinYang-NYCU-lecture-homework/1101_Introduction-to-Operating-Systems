#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <pthread.h>
#include <sys/types.h>

using namespace std;
#define MAXNUM 100009
#define PARTITION_NUM 8
#define THREAD_NUM 4

struct partition
{
    int beg_pos = 0, end_pos = 0;
};

int count = -1, num[MAXNUM] = {0};
vector<partition> sub_array(PARTITION_NUM * 2 - 1);

pthread_mutex_t mutex1, mutex2;

void *bubble_sort(void *input_tinfo)
{
    int *input = (int *)input_tinfo, beg = input[0], end = input[1], temp;
    //printf("bubble1: %d %d\n", input[0], input[1]);
    //printf("bubble1: %d %d\n", beg, end);
    //for(int i = beg; i < beg + 20; i++) printf("%d ", num[i]);
    //printf("\n");
    pthread_mutex_unlock(&mutex1);

    for(int i = 0; i < end - beg + 1; i++)
    {
        for(int j = beg; j < end - i; j++)
        {
            if(num[j] > num[j + 1])
            {
                temp = num[j];
                num[j] = num[j + 1];
                num[j + 1] = temp;
            }
        }
    }
    //printf("bubble2: %d %d\n", input[0], input[1]);
    //pthread_mutex_unlock(&mutex);
    //return NULL;  
    pthread_exit(NULL);
} 

void *merge(void *input_tinfo)
{
    int *input = (int *)input_tinfo;
    int ori_idx = input[0], left_idx = 0, right_idx = 0, left_size = input[1] - input[0] + 1, right_size = input[3] - input[2] + 1;
    int left[left_size], right[right_size];

    pthread_mutex_unlock(&mutex1);

    for(int i = input[0], j = 0; i <= input[1]; i++, j++) left[j] = num[i];
    for(int i = input[2], j = 0; i <= input[3]; i++, j++) right[j] = num[i];

    while(ori_idx <= input[3] && left_idx < left_size && right_idx < right_size)
    {
        if(left[left_idx] <= right[right_idx]) num[ori_idx++] = left[left_idx++];
        else num[ori_idx++] = right[right_idx++];
    }

    while(left_idx < left_size) num[ori_idx++] = left[left_idx++];
    while(right_idx < right_size) num[ori_idx++] = right[right_idx++];

    //return NULL;    
    pthread_exit(NULL);
}

int main (int argc, const char * argv[]) 
{
	/* Use STDIN (e.g. scanf, cin) to take the input */
	while(scanf("%d", &num[++count]) != EOF);

	/* Do the sorting */

    for(int i = 0; i < PARTITION_NUM; i++)
    {
        sub_array[i].beg_pos = count / PARTITION_NUM * i;
        sub_array[i].end_pos = count / PARTITION_NUM * (i + 1) - 1;
    }
    sub_array[PARTITION_NUM - 1].end_pos = count - 1; //不能整除的話, 上面for給最後一個的end會有問題, end的位置到count就好

    int old_sub = 0, new_sub = PARTITION_NUM;
    while(old_sub < new_sub - 1)
    {
        sub_array[new_sub].beg_pos = sub_array[old_sub++].beg_pos;
        sub_array[new_sub++].end_pos = sub_array[old_sub++].end_pos;
    }
    /*
        012345678901234
    old xxooxxooxxooxx
    new         xoxoxox
    */

    pthread_mutex_init(&mutex1, 0);
    pthread_mutex_init(&mutex2, 0);

    int input_to_func[4];
    pthread_t thread_num[THREAD_NUM];
    for(int i = 0; i < PARTITION_NUM ; i++)
    {
        pthread_mutex_lock(&mutex1);

        input_to_func[0] = sub_array[i].beg_pos;
        input_to_func[1] = sub_array[i].end_pos;

        //printf("to bubble: %d %d\n", input_to_func[0], input_to_func[1]);
        pthread_create(&thread_num[i % THREAD_NUM], NULL, bubble_sort, (void *)input_to_func);
        //bubble_sort((void *)input_to_func);

        if(THREAD_NUM == 1 || (i != 0 && i % THREAD_NUM == 0))
            for(int j = 0; j < THREAD_NUM ; j++) 
                pthread_join(thread_num[j], NULL);
    }

    for(int i = 0; i < PARTITION_NUM % THREAD_NUM ; i++) 
        pthread_join(thread_num[i], NULL);

    //printf("%d %d ", count, PARTITION_NUM);
    //for(int i = 0; i < count; i++) printf("%d ", num[i]);


    int merge_num = PARTITION_NUM / 2, sub_array_idx = 0;
    while(merge_num >= 1)
    {
        for(int i = 0; i < merge_num ; i++)
        {
            pthread_mutex_lock(&mutex1);

            input_to_func[0] = sub_array[sub_array_idx].beg_pos;
            input_to_func[1] = sub_array[sub_array_idx].end_pos;
            input_to_func[2] = sub_array[sub_array_idx + 1].beg_pos;
            input_to_func[3] = sub_array[sub_array_idx + 1].end_pos;
            pthread_create(&thread_num[i % THREAD_NUM], NULL, merge, (void *)input_to_func);

            if(THREAD_NUM == 1 || (i != 0 && i % THREAD_NUM == 0))
                for(int j = 0; j < THREAD_NUM ; j++) 
                    pthread_join(thread_num[j], NULL);

            sub_array_idx += 2;
        }

        for(int i = 0; i < merge_num % THREAD_NUM ; i++) 
            pthread_join(thread_num[i], NULL);

        merge_num /= 2;
    }
    

	/* Use STDOUT (e.g. printf, cout) to output the sorted array */
	for(int i = 0; i < count; i++) printf("%d ", num[i]);

    return 0;
}

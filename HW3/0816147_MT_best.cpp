#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

using namespace std;
#define MAXNUM 1000009
#define PARTITION_NUM 8
#define THREAD_NUM 4

struct partition
{
    int beg_pos = 0, end_pos = 0;
};

struct input_info
{
    int beg1 = 0, end1 = 0, beg2 = 0, end2 = 0;
};

int count = -1, num[MAXNUM] = {0};
partition sub_array[PARTITION_NUM * 2 - 1];

/* function definitions */
void *bubble_sort(void*);
void *merge(void*);

int main (int argc, const char * argv[]) 
{
	/* Use STDIN (e.g. scanf, cin) to take the input */
	while(scanf("%d", &num[++count]) != EOF);

	/* Do the sorting */

    //切出每個partition的起始與結束
    for(int i = 0; i < PARTITION_NUM; i++)
    {
        sub_array[i].beg_pos = count / PARTITION_NUM * i;
        sub_array[i].end_pos = count / PARTITION_NUM * (i + 1) - 1;
    }
    sub_array[PARTITION_NUM - 1].end_pos = count - 1; //不能整除的話, 上面for給最後一個的end會有問題, end的位置到count就好

    //每次合併後的起始與結束, 接在第一次partition的後面
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



    //對每個partition做bubble sort
    input_info input_to_func[THREAD_NUM];
    pthread_t thread_num[THREAD_NUM];
    int used_thread = 0;

    for(int i = 0; i < PARTITION_NUM ; i++)
    {
        input_to_func[used_thread] = {sub_array[i].beg_pos, sub_array[i].end_pos, 0, 0};
        pthread_create(&thread_num[i % THREAD_NUM], NULL, bubble_sort, (void *)&input_to_func[used_thread++]);

        if(used_thread >= THREAD_NUM)
        {
            for(int j = 0; j < THREAD_NUM ; j++) 
                pthread_join(thread_num[j], NULL);
            used_thread = 0;
        }
    }

    if(used_thread > 0)
    {
        for(int i = 0; i < used_thread ; i++) 
            pthread_join(thread_num[i], NULL);
        used_thread = 0;
    }

    //把每個partition合併
    int merge_num = PARTITION_NUM / 2, sub_array_idx = 0;
    used_thread = 0;
    while(merge_num >= 1)
    {
        for(int i = 0; i < merge_num ; i++)
        {
            input_to_func[used_thread] = {sub_array[sub_array_idx].beg_pos, sub_array[sub_array_idx].end_pos, sub_array[sub_array_idx + 1].beg_pos, sub_array[sub_array_idx + 1].end_pos};
            pthread_create(&thread_num[i % THREAD_NUM], NULL, merge, (void *)&input_to_func[used_thread++]);

            if(used_thread >= THREAD_NUM)
            {
                for(int j = 0; j < THREAD_NUM ; j++) 
                    pthread_join(thread_num[j], NULL);
                used_thread = 0;
            }

            sub_array_idx += 2;
        }

        if(used_thread > 0)
        {
            for(int i = 0; i < used_thread ; i++) 
                pthread_join(thread_num[i], NULL);
            used_thread = 0;
        }

        merge_num /= 2;
    }
    

	/* Use STDOUT (e.g. printf, cout) to output the sorted array */
	for(int i = 0; i < count; i++) printf("%d ", num[i]);

    return 0;
}


void *bubble_sort(void *input_tinfo)
{
    input_info *input = (input_info *)input_tinfo;
    int temp;

    for(int i = 0; i < input -> end1 - input -> beg1 + 1; i++)
    {
        for(int j = input -> beg1; j < input -> end1 - i; j++)
        {
            if(num[j] > num[j + 1])
            {
                temp = num[j];
                num[j] = num[j + 1];
                num[j + 1] = temp;
            }
        }
    }
    
    pthread_exit(NULL);
} 

void *merge(void *input_tinfo)
{
    input_info *input = (input_info *)input_tinfo;
    int ori_idx = input -> beg1, left_idx = 0, right_idx = 0, left_size = input -> end1 - input -> beg1 + 1, right_size = input -> end2 - input -> beg2 + 1;
    int left[left_size], right[right_size];

    for(int i = input -> beg1, j = 0; i <= input -> end1; i++, j++) left[j] = num[i];
    for(int i = input -> beg2, j = 0; i <= input -> end2; i++, j++) right[j] = num[i];

    while(ori_idx <= input -> end2 && left_idx < left_size && right_idx < right_size)
    {
        if(left[left_idx] <= right[right_idx]) num[ori_idx++] = left[left_idx++];
        else num[ori_idx++] = right[right_idx++];
    }

    while(left_idx < left_size) num[ori_idx++] = left[left_idx++];
    while(right_idx < right_size) num[ori_idx++] = right[right_idx++];

    //return NULL;    
    pthread_exit(NULL);
}
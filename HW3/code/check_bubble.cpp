#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;
#define MAXNUM 10009
#define PARTITION_NUM 8
#define THREAD_NUM 2

struct partition
{
    int beg_pos = 0, end_pos = 0;
};

vector<partition> sub_array(PARTITION_NUM * 2 - 1);

int main()
{
    int count, parti;
    vector<int> num(count);
    scanf("%d %d", &count, &parti);

    for(int i = 0; i < PARTITION_NUM; i++)
    {
        sub_array[i].beg_pos = count / PARTITION_NUM * i;
        sub_array[i].end_pos = count / PARTITION_NUM * (i + 1) - 1;
    }
    sub_array[PARTITION_NUM - 1].end_pos = count - 1; //不能整除的話, 上面for給最後一個的end會有問題, end的位置到count就好

    for(int i = 0; i < count; i++) scanf("%d ", &num[i]);

    int cur_sub = 0;
    for(int i = 0; i < count; i++)
    {
        if(i == sub_array[cur_sub].end_pos)
        {
            for(int j = sub_array[cur_sub].beg_pos; j < sub_array[cur_sub].end_pos; j++)
                if(num[j] > num[j + 1]) 
                {
                    printf("cur_sub:%d   j:%d  num: %d %d\n", cur_sub, j, num[j], num[j + 1]);
                    return 0;
                }
                    
            cur_sub++;
        }
    }

    return 0;
}
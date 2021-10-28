#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct process_state
{
    int process_num = 0, arrive_time = 0, cpu_burst = 0, used_cpu_burst = 0, waiting_time = 0, turnaround_time = 0;
};

bool cmp(process_state A, process_state B)  //以remaining time來排
{
    //if((A.cpu_burst - A.used_cpu_burst) == (B.cpu_burst- B.used_cpu_burst)) return A.arrive_time < B.arrive_time;
    return (A.cpu_burst - A.used_cpu_burst) < (B.cpu_burst- B.used_cpu_burst); 
}

class CPU_schedule
{
public:

    void input_data()
    {
        int tmp_arr = 0, tmp_cpu = 0;

        cin >> total_process;
        processes.resize(total_process);

        for(int i = 0; i < total_process; i++)
        {
            cin >> tmp_arr;
            processes[i].arrive_time = tmp_arr;
            processes[i].process_num = i;
        }

        for(int i = 0; i < total_process; i++)
        {
            cin >> tmp_cpu;
            processes[i].cpu_burst = tmp_cpu;
            total_burst += tmp_cpu;
        }

        cin >> time_quantum;
    }

    void RR_and_SRTF()
    {
        queue<process_state> rr_waiting_process;
        vector<process_state> srtf_waiting_process;
        int cur_pro = 0, arr_pro_num = 1, cur_time_quat = 0, pro_from_level = 1;   
        // arr_pro_num = 1: 第一個直接被排程了,不用跟後面其他的一起
        // pro_from_level = 1 or 2代表現在process來自哪個level

        for(int cur_time = 0; cur_time <= total_burst; cur_time++)
        {
            //有新的process進來,不會有2個以上process同時進來
            if(cur_time == processes[arr_pro_num].arrive_time) rr_waiting_process.push(processes[arr_pro_num++]);   

            if(processes[cur_pro].used_cpu_burst == processes[cur_pro].cpu_burst)   //process已做完,要換下一個
            {
                //計算一些東西
                processes[cur_pro].turnaround_time = cur_time - processes[cur_pro].arrive_time;
                processes[cur_pro].waiting_time = processes[cur_pro].turnaround_time - processes[cur_pro].cpu_burst;
                
                if(rr_waiting_process.size() != 0)  //若level 1有process,level 1的先
                {
                    cur_pro = rr_waiting_process.front().process_num;
                    rr_waiting_process.pop();
                    pro_from_level = 1;
                }

                else    //換level 2的
                {
                    if(srtf_waiting_process.size() > 0)     //避免vector沒東西卻被acess
                    {
                        stable_sort(srtf_waiting_process.begin(), srtf_waiting_process.end(), cmp);     //以剩餘time排序, stable避免順序亂掉
                        cur_pro = srtf_waiting_process[0].process_num;
                        pop_first_element(srtf_waiting_process);
                        pro_from_level = 2;
                    }
                }
                
                cur_time_quat = 0;
            }

            if(pro_from_level == 1)     //來自level 1的process還沒做完
            {
                if(cur_time_quat == time_quantum)   //可做的時間到了還沒做完
                {
                    srtf_waiting_process.push_back(processes[cur_pro]);     //去level 2

                    if(rr_waiting_process.size() != 0)  //若level 1有process,level 1的先
                    {
                        cur_pro = rr_waiting_process.front().process_num;
                        rr_waiting_process.pop();
                        pro_from_level = 1;
                    }

                    else    //換level 2的
                    {
                        if(srtf_waiting_process.size() > 0)     //避免vector沒東西卻被acess
                        {
                            stable_sort(srtf_waiting_process.begin(), srtf_waiting_process.end(), cmp);     //以剩餘time排序, stable避免順序亂掉
                            cur_pro = srtf_waiting_process[0].process_num;
                            pop_first_element(srtf_waiting_process);
                            pro_from_level = 2;
                        }
                    }
                    
                    cur_time_quat = 0;
                }

                //可做的時間還沒到就繼續做
            }

            else     //來自level 2的process還沒做完
            {
                if(rr_waiting_process.size() != 0)  //若level 1有東西了就會被level 1的搶走
                {
                    srtf_waiting_process.push_back(processes[cur_pro]);     //把現在這個level 2的放回去

                    cur_pro = rr_waiting_process.front().process_num;
                    rr_waiting_process.pop();
                    pro_from_level = 1;
                }
                
                //不然就繼續做
            }

            if(cur_time < total_burst)  // 避免最後一個process的used_cpu_burst被多+1,雖然沒差
            {
                processes[cur_pro].used_cpu_burst++;
                cur_time_quat++;
            }
        }
    }

    void pop_first_element(vector<process_state> &vec)
    {
        for(int i = 0; i < vec.size() - 1; i++) vec[i] = vec[i + 1];
        vec.pop_back();
    }

    void output_data()
    {
        for(int i = 0; i < total_process; i++)
        {
            cout << processes[i].waiting_time << " " << processes[i].turnaround_time << "\n";
            total_waiting += processes[i].waiting_time;
            total_trunaround += processes[i].turnaround_time;
        }
        cout << total_waiting << "\n" << total_trunaround;
    }

private:

    int total_process = 0, total_burst = 0, total_waiting = 0, total_trunaround = 0, time_quantum = 0;
    vector<process_state> processes;

};

int main()
{
    CPU_schedule my_cpu;
    my_cpu.input_data();
    my_cpu.RR_and_SRTF();
    my_cpu.output_data();

    return 0;
}
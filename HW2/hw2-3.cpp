#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct process_state
{
    int process_num = 0, arrive_time = 0, cpu_burst = 0, used_cpu_burst = 0, waiting_time = 0, turnaround_time = 0;
};

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

    void RR()
    {
        queue<process_state> waiting_process;
        int cur_pro = 0, arr_pro_num = 1, cur_time_quat = 0;
        // arr_pro_num = 1: 第一個直接被排程了,不用跟後面其他的一起

        for(int cur_time = 0; cur_time <= total_burst; cur_time++)
        {
            //有新的process進來,不會有2個以上process同時進來
            if(cur_time == processes[arr_pro_num].arrive_time) waiting_process.push(processes[arr_pro_num++]);

            if(processes[cur_pro].used_cpu_burst == processes[cur_pro].cpu_burst)   //process已做完,要換下一個
            {
                //計算一些東西
                processes[cur_pro].turnaround_time = cur_time - processes[cur_pro].arrive_time;
                processes[cur_pro].waiting_time = processes[cur_pro].turnaround_time - processes[cur_pro].cpu_burst;
                
                //輪到queue中第一個
                cur_pro = waiting_process.front().process_num;
                waiting_process.pop();
                cur_time_quat = 0;
            }

            else if(cur_time_quat == time_quantum)   //可做的時間到了還沒做完
            {
                waiting_process.push(processes[cur_pro]);   //進去queue裡面排隊

                //輪到queue中第一個
                cur_pro = waiting_process.front().process_num;
                waiting_process.pop();
                cur_time_quat = 0;
            }

            if(cur_time < total_burst)   // 避免最後一個process的used_cpu_burst被多+1,雖然沒差
            {
                processes[cur_pro].used_cpu_burst++;
                cur_time_quat++;
            }
        }
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
    my_cpu.RR();
    my_cpu.output_data();

    return 0;
}
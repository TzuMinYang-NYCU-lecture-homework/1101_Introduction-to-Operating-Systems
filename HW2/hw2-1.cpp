#include <iostream>
#include <vector>
using namespace std;

struct process_state
{
    int arrive_time = 0, cpu_burst = 0, used_cpu_burst = 0, waiting_time = 0, turnaround_time = 0;
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
        }

        for(int i = 0; i < total_process; i++)
        {
            cin >> tmp_cpu;
            processes[i].cpu_burst = tmp_cpu;
            total_burst += tmp_cpu;
        }
    }

    void FCFS()
    {
        int cur_pro = 0;

        for(int cur_time = 0; cur_time <= total_burst; cur_time++)
        {
            if(processes[cur_pro].used_cpu_burst == processes[cur_pro].cpu_burst)   //process已做完,要換下一個
            {
                //計算一些東西
                processes[cur_pro].turnaround_time = cur_time - processes[cur_pro].arrive_time;
                processes[cur_pro].waiting_time = processes[cur_pro].turnaround_time - processes[cur_pro].cpu_burst;

                //直接換下一個process就好
                cur_pro++;
            }

            if(cur_time < total_burst)  // 避免最後一個process的used_cpu_burst被多+1,雖然沒差
                processes[cur_pro].used_cpu_burst++;
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

    int total_process = 0, total_burst = 0, total_waiting = 0, total_trunaround = 0;
    vector<process_state> processes;

};

int main()
{
    CPU_schedule my_cpu;
    my_cpu.input_data();
    my_cpu.FCFS();
    my_cpu.output_data();

    return 0;
}
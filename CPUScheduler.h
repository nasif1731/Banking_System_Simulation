#ifndef CPUSCHEDULER_H
#define CPUSCHEDULER_H

#include "ProcessManager.h"
#include <queue>
#include <vector>

class CPUScheduler {
public:
    CPUScheduler(int time_slice = 10);
    ~CPUScheduler();

    void addProcess(int transaction_id, int burst_time); 
    void runScheduler();
    void runProcess(int transaction_id);
    double calculateAverageWaitTime() const;
    double calculateCPUUtilization() const;
    void printGanttChart() const;

private:
    int time_slice; 
    int exec_time;
    std::queue<int> process_queue; 
    ProcessManager process_manager;
    int total_time = 0;  
    std::unordered_map<int, int> burst_times;  
    std::unordered_map<int, int> wait_times;   
};

#endif

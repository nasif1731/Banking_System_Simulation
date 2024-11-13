#ifndef CPUSCHEDULER_H
#define CPUSCHEDULER_H

#include "ProcessManager.h"
#include <queue>
#include <vector>

class CPUScheduler {
public:
    CPUScheduler(int time_slice);
    ~CPUScheduler();

    void addProcess(int transaction_id);
    void runScheduler();
    void runProcess(int transaction_id);
    double calculateAverageWaitTime() const;
    double calculateCPUUtilization() const;

private:
    int time_slice; 
    std::queue<int> process_queue; 
    ProcessManager process_manager;

    struct ProcessMetrics {
        int transaction_id;
        int start_time;
        int end_time;
    };

    std::vector<ProcessMetrics> metrics; 
};

#endif 

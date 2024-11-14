#include "CPUScheduler.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>


CPUScheduler::CPUScheduler(int time_slice) : time_slice(time_slice) {

}

CPUScheduler::~CPUScheduler() {}

void CPUScheduler::addProcess(int transaction_id, int burst_time) {
    process_queue.push(transaction_id);
    burst_times[transaction_id] = burst_time;
    wait_times[transaction_id] = 0; // Initialize wait time
}

void CPUScheduler::runScheduler() {
    int current_time = 0;

    while (!process_queue.empty()) {
        int transaction_id = process_queue.front();
        process_queue.pop();
        ProcessStatus status = process_manager.getProcessStatus(transaction_id);

        if (status == ProcessStatus::ACTIVE && burst_times[transaction_id] > 0) {
            int exec_time = std::min(time_slice, burst_times[transaction_id]);
            burst_times[transaction_id] -= exec_time;
            current_time += exec_time;
            total_time += exec_time;

            std::cout << "Running process " << transaction_id << " for " << exec_time << " ms" << std::endl;

            if (burst_times[transaction_id] > 0) {
                process_queue.push(transaction_id); // Re-add to queue if process needs more time
            } else {
                process_manager.terminateProcess(transaction_id); // Terminate completed process
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(exec_time)); // Simulate CPU time slice
        }

        // Update wait times for remaining processes in queue
        std::queue<int> temp_queue = process_queue;
        while (!temp_queue.empty()) {
            int waiting_id = temp_queue.front();
            temp_queue.pop();
            wait_times[waiting_id] += exec_time; // Increase wait time for each waiting process
        }
    }

    printGanttChart();
    std::cout << "Average Wait Time: " << calculateAverageWaitTime() << " ms" << std::endl;
    std::cout << "CPU Utilization: " << calculateCPUUtilization() * 100 << " %" << std::endl;
}

void CPUScheduler::runProcess(int transaction_id) {
    std::cout << "Running process " << transaction_id << " for " << time_slice << " ms" << std::endl;
    // Simulate process execution logic here
}

double CPUScheduler::calculateAverageWaitTime() const {
    int total_wait_time = 0;
    for (const auto& entry : wait_times) {
        total_wait_time += entry.second;
    }
    return static_cast<double>(total_wait_time) / wait_times.size();
}

double CPUScheduler::calculateCPUUtilization() const {
    return static_cast<double>(total_time) / (total_time + calculateAverageWaitTime());
}

void CPUScheduler::printGanttChart() const {
    std::cout << "\nGantt Chart:\n";

    // Print transaction IDs in the order they were processed
    std::queue<int> temp_queue = process_queue;
    while (!temp_queue.empty()) {
        int transaction_id = temp_queue.front();
        temp_queue.pop();
        std::cout << "| Process " << transaction_id << " ";
    }
    std::cout << "|\n";

    // Print the timeline
    int time_counter = 0;
    for (auto& burst : burst_times) {
        std::cout << time_counter << " ms ";
        time_counter += burst.second;
    }
    std::cout << time_counter << " ms\n";
}

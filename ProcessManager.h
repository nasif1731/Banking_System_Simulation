#pragma once
#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <string>
#include <unordered_map>

// Enum for process status
enum class ProcessStatus {
    ACTIVE,
    COMPLETED,
    TERMINATED
};

// Struct to represent a process
struct Process {
    int transaction_id;
    int account_id;
    std::string transaction_type;
    ProcessStatus status;
};

class ProcessManager {
public:
    ProcessManager();
    ~ProcessManager();

    int createProcess(int transaction_id, int account_id, const std::string& transaction_type);
    void terminateProcess(int transaction_id);
    ProcessStatus getProcessStatus(int transaction_id);

private:
    std::unordered_map<int, Process> process_table; 
};

#endif

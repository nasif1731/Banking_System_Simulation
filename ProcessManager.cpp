#include "ProcessManager.h"
#include <iostream>

ProcessManager::ProcessManager() {}

ProcessManager::~ProcessManager() {
    process_table.clear(); 
}

int ProcessManager::createProcess(int transaction_id, int account_id, const std::string& transaction_type) {
    Process new_process = { transaction_id, account_id, transaction_type, ProcessStatus::ACTIVE };
    process_table[transaction_id] = new_process;
    std::cout << "Process created for transaction " << transaction_id << std::endl;
    return transaction_id;
}

void ProcessManager::terminateProcess(int transaction_id) {
    if (process_table.find(transaction_id) != process_table.end()) {
        process_table[transaction_id].status = ProcessStatus::TERMINATED;
        std::cout << "Process " << transaction_id << " terminated." << std::endl;
    }
}

ProcessStatus ProcessManager::getProcessStatus(int transaction_id) {
    if (process_table.find(transaction_id) != process_table.end()) {
        return process_table[transaction_id].status;
    }
    return ProcessStatus::TERMINATED; 
}

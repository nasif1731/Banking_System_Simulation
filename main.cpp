// main.cpp

#include <iostream>
#include "CPUScheduler.h"
#include "ProcessManager.h"
#include "BankingSystem.h"

int main() {
    // Testing CPUScheduler class
    std::cout << "Testing CPUScheduler class:" << std::endl;
    // Create a CPUScheduler object with a time slice of 50 milliseconds
    CPUScheduler cpuScheduler(50);

    // Add processes to the scheduler
    cpuScheduler.addProcess(1, 100); // Process ID 1 with burst time of 100 ms
    cpuScheduler.addProcess(2, 200); // Process ID 2 with burst time of 200 ms
    cpuScheduler.addProcess(3, 300); // Process ID 3 with burst time of 300 ms

    // Run the scheduler to process the tasks
    cpuScheduler.runScheduler();

    std::cout << "CPUScheduler finished running the processes." << std::endl;

    // Testing ProcessManager class
    std::cout << "\nTesting ProcessManager class:" << std::endl;
    ProcessManager processManager;

    // Create processes with specific burst times
    int transaction_id_1 = 1;
    int account_id_1 = 101;  // Sample account ID for transaction 1
    std::string transaction_type_1 = "Deposit";

    int transaction_id_2 = 2;
    int account_id_2 = 102;  // Sample account ID for transaction 2
    std::string transaction_type_2 = "Withdraw";

    processManager.createProcess(transaction_id_1, account_id_1, transaction_type_1); 
    processManager.createProcess(transaction_id_2, account_id_2, transaction_type_2);


    // Check and print process status
    ProcessStatus status1 = processManager.getProcessStatus(transaction_id_1);
    ProcessStatus status2 = processManager.getProcessStatus(transaction_id_2);

    std::cout << "Process 1 status: " << (status1 == ProcessStatus::ACTIVE ? "ACTIVE" : "INACTIVE") << std::endl;
    std::cout << "Process 2 status: " << (status2 == ProcessStatus::ACTIVE ? "ACTIVE" : "INACTIVE") << std::endl;

    // Terminate processes
    processManager.terminateProcess(transaction_id_1); // Terminate Process 1
    processManager.terminateProcess(transaction_id_2); // Terminate Process 2

    std::cout << "Process 1 and 2 have been terminated." << std::endl;

    // Testing BankingSystem class
    std::cout << "\nTesting BankingSystem class:" << std::endl;
    BankingSystem bankingSystem;

    // Create transaction processes
    int pid1 = bankingSystem.createTransactionProcess(transaction_id_1, "Deposit", 500.0);
    int pid2 = bankingSystem.createTransactionProcess(transaction_id_2, "Withdraw", 300.0);

    std::cout << "Created Transaction Processes:" << std::endl;
    std::cout << "Process ID 1 (Deposit): " << pid1 << std::endl;
    std::cout << "Process ID 2 (Withdraw): " << pid2 << std::endl;

    // Add transaction processes to the CPU scheduler
    cpuScheduler.addProcess(pid1, 50); // Deposit transaction process with burst time of 50 ms
    cpuScheduler.addProcess(pid2, 70); // Withdraw transaction process with burst time of 70 ms

    // Run the CPU scheduler again to simulate the transaction processes
    cpuScheduler.runScheduler();

    std::cout << "CPU Scheduler finished running the banking transaction processes." << std::endl;

    // Additional testing: Fetch and print process status for banking transactions
    ProcessStatus transactionStatus1 = processManager.getProcessStatus(pid1);
    ProcessStatus transactionStatus2 = processManager.getProcessStatus(pid2);

    std::cout << "Transaction Process 1 (Deposit) status: " << (transactionStatus1 == ProcessStatus::ACTIVE ? "ACTIVE" : "INACTIVE") << std::endl;
    std::cout << "Transaction Process 2 (Withdraw) status: " << (transactionStatus2 == ProcessStatus::ACTIVE ? "ACTIVE" : "INACTIVE") << std::endl;

    // Final CPU Utilization and Wait Time Calculations
    std::cout << "\nFinal Calculations:" << std::endl;
    std::cout << "Average Wait Time: " << cpuScheduler.calculateAverageWaitTime() << " ms" << std::endl;
    std::cout << "CPU Utilization: " << cpuScheduler.calculateCPUUtilization() * 100 << " %" << std::endl;

    return 0;
}

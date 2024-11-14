#ifndef BANKINGSYSTEM_H
#define BANKINGSYSTEM_H

#include <vector>
#include <pthread.h>
#include <string>
#include "Account.h"
#include "ProcessManager.h"
#include "CPUScheduler.h"

using namespace std;

class BankingSystem {
private:
    vector<Account> accounts;
    pthread_mutex_t account_mutex;
    int currentAccountId = 1;
    ProcessManager processManager;
    CPUScheduler cpuScheduler;
public:
    BankingSystem();
    ~BankingSystem();
    
    int create_account(int customer_id, double initial_balance);
    void deposit(int account_id, double amount);
    bool withdraw(int account_id, double amount);
    double check_balance(int account_id);
    int calculateBurstTime(double amount);

    // Process management and CPU scheduling methods
    int createTransactionProcess(int account_id, const string& transaction_type, double amount = 0);
    void runScheduledTransactions();
    ProcessManager& getProcessManager() {
        return processManager;
    }
};

#endif

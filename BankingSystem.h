#ifndef BANKINGSYSTEM_H
#define BANKINGSYSTEM_H

#include <vector>
#include <pthread.h>
#include "Account.h"

using namespace std;

class BankingSystem {
private:
    vector<Account> accounts;
    pthread_mutex_t account_mutex;
    int currentAccountId = 1;

public:
    BankingSystem();
    ~BankingSystem();
    
    int create_account(int customer_id, double initial_balance);
    void deposit(int account_id, double amount);
    bool withdraw(int account_id, double amount);
    double check_balance(int account_id);
};

#endif

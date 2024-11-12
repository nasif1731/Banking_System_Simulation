#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <pthread.h>

class Account {
private:
    int account_id;
    double balance;
    int customer_id;
    pthread_mutex_t account_mutex;  

public:
    Account(int id, double initialBalance, int customerId);
    ~Account();  
    void deposit(double amount);
    bool withdraw(double amount);
    double getBalance();
};

#endif

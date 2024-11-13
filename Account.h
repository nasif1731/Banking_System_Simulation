#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <thread>
#include <mutex>

class Account {
private:
    int account_id;
    double balance;
    int customer_id;
    std::mutex account_mutex;  

public:
    Account(int id, double initialBalance, int customerId);
    ~Account();  
    void deposit(double amount);
    bool withdraw(double amount);
    double getBalance();
};

#endif

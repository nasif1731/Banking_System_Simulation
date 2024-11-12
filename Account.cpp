#include "Account.h"

Account::Account(int id, double initialBalance, int customerId)
    : account_id(id), balance(initialBalance), customer_id(customerId) {
    pthread_mutex_init(&account_mutex, NULL);
}

//Mutex Locks while Depositing Amount
void Account::deposit(double amount) {
    pthread_mutex_lock(&account_mutex);
    balance += amount;
    pthread_mutex_unlock(&account_mutex);
}

//Mutex Locks while Withdrawing Amount
bool Account::withdraw(double amount) {
    pthread_mutex_lock(&account_mutex);
    bool success = false;
    if (amount <= balance) {
        balance -= amount;
        success = true;
    }
    pthread_mutex_unlock(&account_mutex);
    return success;
}

//Mutex Locks while getting Account Balance
double Account::getBalance() {
    pthread_mutex_lock(&account_mutex);
    double current_balance = balance;
    pthread_mutex_unlock(&account_mutex);
    return current_balance;
}

Account::~Account() {
    pthread_mutex_destroy(&account_mutex);
}
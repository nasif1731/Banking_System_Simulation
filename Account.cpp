#include "Account.h"
#include <mutex>  

Account::Account(int id, double initialBalance, int customerId)
    : account_id(id), balance(initialBalance), customer_id(customerId) {
   
}

// Mutex locks are applied while depositing an amount
void Account::deposit(double amount) {
    std::lock_guard<std::mutex> lock(account_mutex); 
    balance += amount;
}

// Mutex locks are applied while withdrawing an amount
bool Account::withdraw(double amount) {
    std::lock_guard<std::mutex> lock(account_mutex);  
    if (amount <= balance) {
        balance -= amount;
        return true;
    }
    return false;
}

// Mutex locks are applied while getting the account balance
double Account::getBalance() {
    std::lock_guard<std::mutex> lock(account_mutex); 
    return balance;
}

// Destructor: No need to explicitly destroy std::mutex
Account::~Account() {
    
}

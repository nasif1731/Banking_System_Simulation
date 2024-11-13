#include "BankingSystem.h"
#include <iostream>
#include <mutex> 



int BankingSystem::create_account(int customer_id, double initial_balance) {
    std::lock_guard<std::mutex> lock(account_mutex); 
    int account_id = currentAccountId++;
    accounts.emplace_back(account_id, initial_balance, customer_id);
    std::cout << "Account Created.\nAccount ID: " << account_id << std::endl;
    
    return account_id;
}

void BankingSystem::deposit(int account_id, double amount) {
    std::lock_guard<std::mutex> lock(account_mutex);
    if (account_id > 0 && account_id <= accounts.size()) {
        accounts[account_id - 1].deposit(amount);
        std::cout << "Deposited " << amount << " to account " << account_id << std::endl;
    } else {
        std::cerr << "Account ID " << account_id << " not found." << std::endl;
    }
    
}

bool BankingSystem::withdraw(int account_id, double amount) {
    std::lock_guard<std::mutex> lock(account_mutex); 
    bool success = false;
    if (account_id > 0 && account_id <= accounts.size()) {
        success = accounts[account_id - 1].withdraw(amount);
        if (success) {
            std::cout << "Withdrew " << amount << " from account " << account_id << std::endl;
        } else {
            std::cerr << "Insufficient funds in account " << account_id << std::endl;
        }
    } else {
        std::cerr << "Account ID " << account_id << " not found." << std::endl;
    }
    return success;
}

double BankingSystem::check_balance(int account_id) {
    std::lock_guard<std::mutex> lock(account_mutex); 
    double balance = -1.0;
    if (account_id > 0 && account_id <= accounts.size()) {
        balance = accounts[account_id - 1].getBalance();
        std::cout << "Balance of account " << account_id << ": " << balance << std::endl;
    } else {
        std::cerr << "Account ID " << account_id << " not found." << std::endl;
    }
    return balance;
}



int BankingSystem::createTransactionProcess(int account_id, const std::string& transaction_type, double amount) {
    static int transaction_id = 1;
    int id = transaction_id++;

    
    int pid = processManager.createProcess(id, account_id, transaction_type);
    cpuScheduler.addProcess(pid);

    
    if (transaction_type == "deposit") {
        deposit(account_id, amount);
    } else if (transaction_type == "withdraw") {
        withdraw(account_id, amount);
    }

    return pid;
}

void BankingSystem::runScheduledTransactions() {
    cpuScheduler.runScheduler();
}

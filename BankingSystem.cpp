#include "BankingSystem.h"
#include <iostream>

BankingSystem::BankingSystem() {
    pthread_mutex_init(&account_mutex, nullptr);
}

int BankingSystem::create_account(int customer_id, double initial_balance) {
    pthread_mutex_lock(&account_mutex);
    int account_id = currentAccountId++;
    accounts.emplace_back(account_id, initial_balance, customer_id);
    cout << "Account Created.\nAccount ID: " << account_id << endl;
    pthread_mutex_unlock(&account_mutex);
    return account_id;
}

void BankingSystem::deposit(int account_id, double amount) {
    pthread_mutex_lock(&account_mutex);
    if (account_id > 0 && account_id <= accounts.size()) {
        accounts[account_id - 1].deposit(amount);
        cout << "Deposited " << amount << " to account " << account_id << endl;
    } else {
        cerr << "Account ID " << account_id << " not found." << endl;
    }
    pthread_mutex_unlock(&account_mutex);
}

bool BankingSystem::withdraw(int account_id, double amount) {
    pthread_mutex_lock(&account_mutex);
    bool success = false;
    if (account_id > 0 && account_id <= accounts.size()) {
        success = accounts[account_id - 1].withdraw(amount);
        if (success) {
            cout << "Withdrew " << amount << " from account " << account_id << endl;
        } else {
            cerr << "Insufficient funds in account " << account_id << endl;
        }
    } else {
        cerr << "Account ID " << account_id << " not found." << endl;
    }
    pthread_mutex_unlock(&account_mutex);
    return success;
}

double BankingSystem::check_balance(int account_id) {
    pthread_mutex_lock(&account_mutex);
    double balance = -1.0;
    if (account_id > 0 && account_id <= accounts.size()) {
        balance = accounts[account_id - 1].getBalance();
        cout << "Balance of account " << account_id << ": " << balance << endl;
    } else {
        cerr << "Account ID " << account_id << " not found." << endl;
    }
    pthread_mutex_unlock(&account_mutex);
    return balance;
}

BankingSystem::~BankingSystem() {
    pthread_mutex_destroy(&account_mutex);
}
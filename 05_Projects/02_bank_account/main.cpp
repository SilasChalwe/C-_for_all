// ============================================================
// Project: Bank Account Management System
// Author: Silas Chalwe
// Compile: g++ -std=c++17 -Wall -o bank main.cpp && ./bank
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

class Account {
    static int nextId;
    int         id;
    std::string owner;
    double      balance;
    std::vector<std::string> transactions;

public:
    Account(const std::string& name, double initial)
        : id(nextId++), owner(name), balance(initial) {
        transactions.push_back("Account opened with $" + std::to_string(initial));
    }

    void deposit(double amount) {
        if (amount <= 0) throw std::invalid_argument("Deposit must be positive");
        balance += amount;
        transactions.push_back("Deposit  +$" + std::to_string(amount));
    }

    void withdraw(double amount) {
        if (amount <= 0)    throw std::invalid_argument("Amount must be positive");
        if (amount > balance) throw std::runtime_error("Insufficient funds");
        balance -= amount;
        transactions.push_back("Withdraw -$" + std::to_string(amount));
    }

    int         getId()      const { return id; }
    std::string getOwner()   const { return owner; }
    double      getBalance() const { return balance; }

    void printStatement() const {
        std::cout << "\n=== Statement for " << owner << " (ID:" << id << ") ===\n";
        for (const auto& t : transactions) std::cout << "  " << t << "\n";
        std::cout << "  Current balance: $" << std::fixed << std::setprecision(2) << balance << "\n";
    }

    void display() const {
        std::cout << std::left << std::setw(5)  << id
                  << std::setw(15) << owner
                  << "$" << std::fixed << std::setprecision(2) << balance << "\n";
    }
};
int Account::nextId = 1001;

class Bank {
    std::map<int, Account> accounts;

public:
    int createAccount(const std::string& name, double initial) {
        Account acc(name, initial);
        int id = acc.getId();
        accounts.emplace(id, acc);
        return id;
    }

    Account& getAccount(int id) {
        auto it = accounts.find(id);
        if (it == accounts.end()) throw std::runtime_error("Account not found: " + std::to_string(id));
        return it->second;
    }

    void transfer(int fromId, int toId, double amount) {
        getAccount(fromId).withdraw(amount);
        getAccount(toId).deposit(amount);
    }

    void displayAll() const {
        std::cout << "\n=== All Accounts ===\n";
        std::cout << std::left << std::setw(5) << "ID" << std::setw(15) << "Owner" << "Balance\n";
        std::cout << std::string(30, '-') << "\n";
        for (const auto& [id, acc] : accounts) acc.display();
    }
};

void menu() {
    Bank bank;

    // Pre-create some accounts
    int a1 = bank.createAccount("Alice", 1000.0);
    int a2 = bank.createAccount("Bob",    500.0);
    std::cout << "Sample accounts created: Alice(ID:" << a1 << ") Bob(ID:" << a2 << ")\n";

    int choice;
    do {
        std::cout << "\n=== Bank Management System ===\n"
                  << "1. Create account\n"
                  << "2. Deposit\n"
                  << "3. Withdraw\n"
                  << "4. Transfer\n"
                  << "5. View statement\n"
                  << "6. View all accounts\n"
                  << "0. Exit\n"
                  << "Choice: ";
        std::cin >> choice;

        try {
            if (choice == 1) {
                std::string name; double init;
                std::cout << "Name: "; std::cin >> name;
                std::cout << "Initial deposit: "; std::cin >> init;
                int id = bank.createAccount(name, init);
                std::cout << "Account created. ID=" << id << "\n";
            } else if (choice == 2) {
                int id; double amt;
                std::cout << "Account ID: "; std::cin >> id;
                std::cout << "Amount: ";     std::cin >> amt;
                bank.getAccount(id).deposit(amt);
                std::cout << "Deposited $" << amt << "\n";
            } else if (choice == 3) {
                int id; double amt;
                std::cout << "Account ID: "; std::cin >> id;
                std::cout << "Amount: ";     std::cin >> amt;
                bank.getAccount(id).withdraw(amt);
                std::cout << "Withdrew $" << amt << "\n";
            } else if (choice == 4) {
                int from, to; double amt;
                std::cout << "From ID: "; std::cin >> from;
                std::cout << "To ID:   "; std::cin >> to;
                std::cout << "Amount:  "; std::cin >> amt;
                bank.transfer(from, to, amt);
                std::cout << "Transfer complete.\n";
            } else if (choice == 5) {
                int id; std::cout << "Account ID: "; std::cin >> id;
                bank.getAccount(id).printStatement();
            } else if (choice == 6) {
                bank.displayAll();
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    } while (choice != 0);
}

int main() {
    std::cout << "==============================\n";
    std::cout << "  C++ Bank Management System  \n";
    std::cout << "  Created by Silas Chalwe     \n";
    std::cout << "==============================\n";
    menu();
    std::cout << "Thank you for banking with us!\n";
    return 0;
}

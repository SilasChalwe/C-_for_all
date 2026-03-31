// ============================================================
// 08_classes_basics.cpp
// Topic: Classes, objects, constructors, destructors, access specifiers
// Author: Silas Chalwe
// ============================================================
//
// A class is a blueprint for creating objects.
// Access specifiers control visibility:
//   public    — accessible from anywhere
//   private   — accessible only within the class
//   protected — accessible within the class and subclasses
// ============================================================

#include <iostream>
#include <string>

class BankAccount {
private:
    // Private data members: hidden from outside code
    std::string ownerName;
    double      balance;
    int         accountNumber;
    static int  nextAccountNumber; // shared across all instances

public:
    // ---- Constructor: called automatically when an object is created ----
    BankAccount(const std::string& name, double initialBalance)
        : ownerName(name), balance(initialBalance),
          accountNumber(nextAccountNumber++) {
        std::cout << "[Account created] " << ownerName
                  << "  #" << accountNumber << std::endl;
    }

    // ---- Destructor: called automatically when the object goes out of scope ----
    ~BankAccount() {
        std::cout << "[Account closed]  " << ownerName
                  << "  #" << accountNumber << std::endl;
    }

    // ---- Public member functions (the interface) ----
    void deposit(double amount) {
        if (amount <= 0) {
            std::cout << "Error: Deposit amount must be positive." << std::endl;
            return;
        }
        balance += amount;
        std::cout << "Deposited $" << amount
                  << " → balance: $" << balance << std::endl;
    }

    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance) {
            std::cout << "Error: Invalid withdrawal amount." << std::endl;
            return false;
        }
        balance -= amount;
        std::cout << "Withdrew $" << amount
                  << " → balance: $" << balance << std::endl;
        return true;
    }

    // ---- Getters (const member functions: cannot modify the object) ----
    double      getBalance()      const { return balance; }
    std::string getOwnerName()    const { return ownerName; }
    int         getAccountNumber()const { return accountNumber; }

    // ---- Display summary ----
    void display() const {
        std::cout << "Account #" << accountNumber
                  << " | Owner: "   << ownerName
                  << " | Balance: $" << balance << std::endl;
    }
};

// Define the static member outside the class
int BankAccount::nextAccountNumber = 1001;

// ============================================================
int main() {
    // Create objects (calls constructor)
    BankAccount acc1("Alice", 1000.0);
    BankAccount acc2("Bob",    500.0);

    acc1.display();
    acc2.display();

    // Use member functions
    acc1.deposit(250.0);
    acc1.withdraw(100.0);
    acc2.withdraw(600.0); // should fail

    std::cout << "\nFinal balances:" << std::endl;
    std::cout << "Alice: $" << acc1.getBalance() << std::endl;
    std::cout << "Bob:   $" << acc2.getBalance() << std::endl;

    // Destructors called automatically at end of scope

    return 0;
}

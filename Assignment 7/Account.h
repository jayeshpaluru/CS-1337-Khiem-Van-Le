#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

// Given Structures
struct Date {
    int month;
    int day;
    int year;
};

struct Person {
    std::string name;
    Date DOB;
    std::string address;
};

// Account class with member variables and functions listed
class Account {
private:
    int accountNumber;
    int numOwners;
    Person* ownerPtr;
    double balance;
    static int accountCounter;

public:
    Account(int numberOwners, double amount);
    ~Account();

    int withdraw(double amount);
    int deposit(double amount);
    void setOwner(int ind, Person p);
    Person getOwner(int ind) const;
    int getAccountNumber() const;
    double getBalance() const;
    int getNumOwners() const;
    void addOwner(Person p);
    int delOwner(Person p);
};

#endif

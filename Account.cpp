#include "Account.h"

int Account::accountCounter = 1000;

// Constructor
Account::Account(int numberOwners, double amount) {
  accountNumber = accountCounter;
  numOwners = numberOwners;
  ownerPtr = new Person[numOwners];
  balance = amount;
  accountCounter++;
}

// Destructor
Account::~Account() {
  delete[] ownerPtr;
}

// Withdraw function
int Account::withdraw(double amount) {
  if (amount <= 0) {
    return 2;
  } else if (amount > balance) {
    return 1;
  } else {
    balance -= amount;
    return 0;
  }
}

// Deposit function
int Account::deposit(double amount) {
  if (amount > 0) {
    balance += amount;
    return 0;
  } else {
    return 1;
  }
}

// Set owner function
void Account::setOwner(int ind, Person p) {
  if (ind >= 0 && ind < numOwners) {
    ownerPtr[ind] = p;
  }
}

// Get owner function
Person Account::getOwner(int ind) const {
  if (ind >= 0 && ind < numOwners) {
    return ownerPtr[ind];
  }
  return Person(); // Default Person object in case of invalid index
}

// Get account number function
int Account::getAccountNumber() const {
  return accountNumber;
}

// Get balance function
double Account::getBalance() const {
  return balance;
}

// Get number of owners function
int Account::getNumOwners() const {
  return numOwners;
}

// Add owner function
void Account::addOwner(Person p) {
  // Create new array of owners with increased size
  Person * newOwnerPtr = new Person[numOwners + 1];
  // Copy existing owners to the new array
  for (int i = 0; i < numOwners; ++i) {
    newOwnerPtr[i] = ownerPtr[i];
  }
  // Add the new owner to the last position in the new array
  newOwnerPtr[numOwners] = p;
  // Delete old array and update the ownerPtr to point to the new array
  delete[] ownerPtr;
  ownerPtr = newOwnerPtr;
  // Increment the number of owners
  numOwners++;
}

// Delete owner function
int Account::delOwner(Person p) {
    // Cannot delete if only one owner left
    if (numOwners <= 1) {
      return 2;
    }
    // Find the index of the owner to be deleted
    int ownerIndex = -1;
    for (int i = 0; i < numOwners; ++i) {
      if (ownerPtr[i].name == p.name) {
        ownerIndex = i;
        break;
      }
    }
    // Owner not found
    if (ownerIndex == -1) {
      return 1;
    }
    // Create new array of owners with reduced size
    Person * newOwnerPtr = new Person[numOwners - 1];
    // Copy existing owners to the new array, skipping the owner to be deleted
    int newIndex = 0;
    for (int i = 0; i < numOwners; ++i) {
      if (i != ownerIndex) {
        newOwnerPtr[newIndex++] = ownerPtr[i];
      }
    }
    // Delete old array and update the ownerPtr to point to the new array
    delete[] ownerPtr;
    ownerPtr = newOwnerPtr;
    // Decrement the number of owners
    numOwners--;
    return 0;
}
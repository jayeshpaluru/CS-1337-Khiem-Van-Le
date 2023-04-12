#include <iostream>
#include <iomanip>
#include "Account.h"

using namespace std;
// Maximum number of accounts
const int MAX_NUM_ACCOUNTS = 4;
// Array of pointers to Account objects
Account * accountArray[MAX_NUM_ACCOUNTS] = {
  nullptr
};

// Helper function to find the index of an account by account number
int findAccountIndex(int accountNumber) {
  for (int i = 0; i < MAX_NUM_ACCOUNTS; ++i) {
    if (accountNumber == -1 && accountArray[i] == nullptr) {
      return i;
    } else if (accountArray[i] && accountArray[i] -> getAccountNumber() == accountNumber) {
      return i;
    }
  }
  return -1; // Account not found
}

// Helper function to prompt for Person input
Person promptPersonInput() {
  Person p;
  cout << "Enter owner's name: ";
  cin >> p.name;
  cout << "Enter owner's DOB, month, day then year: ";
  cin >> p.DOB.month >> p.DOB.day >> p.DOB.year;
  cin.ignore(); // Ignore newline character
  cout << "Enter owner's address: ";
  getline(cin, p.address);
  return p;
}

// Helper function to display the menu
void displayMenu() {
  cout << "Menu" << endl << "----" << endl << 
  "1->Create account 2->Deposit   3->Withdraw     4->Display " << endl <<
  "5->Delete owner   6->Add owner 7->Delete accnt 8->Quit    " << endl;
}

int main() {
  // Menu loop and functionality
  int choice;
  do {
    displayMenu();
    cin >> choice;

    int accountNumber, index, numOwners;
    double amount;
    Person p;
    switch (choice) {
    case 1: // Create account
      cout << "Enter number of owners: ";
      cin >> numOwners;
      cout << "Enter amount: ";
      cin >> amount;
      cin.ignore(); // Ignore newline character

      // Check if the maximum number of accounts has been reached
      index = findAccountIndex(-1); // Find first empty slot
      if (index == -1) {
        cout << "Maximum number of accounts reached." << endl;
        break;
      }

      // Create a new account
      accountArray[index] = new Account(numOwners, amount);

      // Prompt for owner information
      for (int i = 0; i < numOwners; ++i) {
        cout << "Enter owner's name: ";
        getline(cin, p.name); // Get name
        cout << "Enter owner's DOB, month, day then year: "; // Get DOB
        cin >> p.DOB.month >> p.DOB.day >> p.DOB.year; 
        cin.ignore(); // Ignore newline character
        cout << "Enter owner's address: ";
        getline(cin, p.address); // Get address
        accountArray[index] -> setOwner(i, p);
      }

      cout << "Account #" << accountArray[index] -> getAccountNumber() << " created" << endl;
      break;

    case 2: // Deposit to account
      cout << "Enter account number: ";
      cin >> accountNumber;

      index = findAccountIndex(accountNumber);
      if (index == -1) {
        cout << "No such account" << endl;
      } else {
        cout << "Enter amount: ";
        cin >> amount;
        int result = accountArray[index] -> deposit(amount);
        if (result == 0) {
          cout << "New balance is $" << fixed << setprecision(2) << accountArray[index] -> getBalance() << endl;
        } else {
          cout << "Amount cannot be negative, deposit not executed" << endl;
        }
      }
      break;
    case 3: // Withdraw from account
      cout << "Enter account number: ";
      cin >> accountNumber;

      index = findAccountIndex(accountNumber);
      if (index == -1) {
        cout << "No such account" << endl;
      } else {
        cout << "Enter amount: ";
        cin >> amount;
        int result = accountArray[index] -> withdraw(amount);
        if (result == 0) {
          cout << "New balance is $" << fixed << setprecision(2) << accountArray[index] -> getBalance() << endl;
        } else if (result == 1) {
          cout << "Insufficient balance, withdrawal not executed" << endl;
        } else {
          cout << "Amount cannot be negative, withdrawal not executed" << endl;
        }
      }
      break;

    case 4: // Display information for all accounts
      for (int i = 0; i < MAX_NUM_ACCOUNTS; ++i) {
        if (accountArray[i]) {
          cout << "Account Number: " << accountArray[i] -> getAccountNumber() << endl;
          cout << "--------------" << endl;
          for (int j = 0; j < accountArray[i] -> getNumOwners(); ++j) {
            Person owner = accountArray[i] -> getOwner(j);
            cout << "*Name: " << owner.name << ", DOB: " << owner.DOB.month << '/' << owner.DOB.day << '/' << owner.DOB.year << endl;
            cout << "Address: " << owner.address << endl;
          }
          cout << "*Balance: $" << fixed << setprecision(2) << accountArray[i] -> getBalance() << " " << endl;
        }
      }
      break;

    case 5: // Delete owner
      cout << "Enter the account number: ";
      cin >> accountNumber;

      index = findAccountIndex(accountNumber);
      if (index == -1) {
        cout << "No such account" << endl;
      } else {
        cout << "Enter information for owner to delete:" << endl;
        p = promptPersonInput();
        int result = accountArray[index] -> delOwner(p);
        if (result == 0) {
          cout << "Owner deleted successfully." << endl;
        } else if (result == 1) {
          cout << "Person not found among the owners." << endl;
        } else {
          cout << "Delete cannot be performed because there is only one owner left." << endl;
        }
      }
      break;

    case 6: // Add owner 
      cout << "Enter the account number: ";
      cin >> accountNumber;

      index = findAccountIndex(accountNumber);
      if (index == -1) {
        cout << "No such account" << endl;
      } else {
        cout << "Enter information for owner to add:" << endl;
        p = promptPersonInput();
        accountArray[index] -> addOwner(p);
        cout << "Owner added successfully." << endl;
      }
      break;

    case 7: // Delete account 
      cout << "Enter the account number: ";
      cin >> accountNumber;

      index = findAccountIndex(accountNumber);
      if (index == -1) {
        cout << "No such account" << endl;
      } else {
        // Delete the account
        delete accountArray[index];
        accountArray[index] = nullptr;
        cout << "Account deleted successfully" << endl;
      }
      break;

    case 8: // Quit
      // Release the dynamically allocated Account objects
      for (int i = 0; i < MAX_NUM_ACCOUNTS; ++i) {
        if (accountArray[i]) {
          delete accountArray[i];
          accountArray[i] = nullptr;
        }
      }
      break;

    default:
      cout << "Invalid choice. Please try again." << endl;
      break;
    }
  } while (choice != 8);

  return 0;
}
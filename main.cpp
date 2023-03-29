// Author: Jayesh Paluru
// Compiler: GNU GCC
// Date: 3/23/2023
// Purpose of the program: Create a program that manages bank accounts

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <sstream>
#include <cstring>

using namespace std;
// Given Structures
struct Person {
  string name;
  string address;
};

struct Account {
  int accountNumber;
  Person ownerInfo;
  double balance;
};
// Max attempts for user input
const int MAX_ATTEMPTS = 5;

// Function prototypes
bool dataInputandValidation(string & input);
void populateAccount(Account accounts[], int & numAccounts, int maxAccounts);
void displayAccount(Account accounts[], int & numAccounts, int maxAccounts);
void printAccount(const Account & account);
bool containsDigitAndChar(const string & str);

int main() {
  int maxAccounts;
  int tries = 0;
  // Get max number of accounts
  cout << "Enter max number of accounts: ";
  while (tries < MAX_ATTEMPTS) {
    string input;
    getline(cin, input); // Use getline for user input
    // Check if input is valid
    if (cin.fail() || !isdigit(input[0]) || containsDigitAndChar(input)) {
      cin.clear();
      tries++;
      if (tries < MAX_ATTEMPTS) {
        cout << "Invalid value, please reenter: ";
      }
    } else {
      maxAccounts = stoi(input);
      break;
    }
  }

  if (tries == MAX_ATTEMPTS) {
    cout << "Too many unsuccessful attempts, exiting";
    return 0;
  }
  cout << endl;
  Account * accounts = new Account[maxAccounts];
  int numAccounts = 0;
  int choice;
  // Menu
  do {
    int attempts = 0;
    cout << "Menu:" << endl;
    cout << "1->Enter data for specific account, ";
    cout << "2->Display data for specific account" << endl;
    cout << "3->Display data for all accounts  , ";
    cout << "4->Quit:" << endl;
    string input;
    // Get menu choice
    while (attempts < MAX_ATTEMPTS) {
      getline(cin, input); // Use getline for user input
      if (cin.fail() || !isdigit(input[0]) || containsDigitAndChar(input)) {
        attempts++;
        if (attempts != MAX_ATTEMPTS) {
          cout << "Invalid choice, please reenter: ";
        } else {
          cout << "Too many unsuccessful attempts, exiting";
          exit(0);
        }
      } else {
        stringstream ss(input);
        ss >> choice;
        if (choice < 1 || choice > 4) {
          attempts++;
          if (attempts != MAX_ATTEMPTS) {
            cout << "Invalid choice, please reenter: ";
          } else {
            cout << "Too many unsuccessful attempts, exiting";
            exit(0);
          }
        } else {
          break;
        }
      }
    }
    // Execute menu choice
    switch (choice) {
    case 1:
      populateAccount(accounts, numAccounts, maxAccounts);
      break;
    case 2:
      displayAccount(accounts, numAccounts, maxAccounts);
      break;
    case 3:
      for (int i = 0; i < numAccounts; i++) {
        printAccount(accounts[i]);
      }
      cout << endl;
      break;
    case 4:
      return 0;
    }
  } while (choice != 4);
}

// Data validation for account number and balance
bool dataInputandValidation(string & input) {
  cout << "Enter account number: ";
  cin.ignore();
  int numAttempts = 0;
  while (numAttempts < MAX_ATTEMPTS) {
    getline(cin, input);
    if (cin.fail() || !isdigit(input[0]) || containsDigitAndChar(input)) {
      numAttempts++;
      if (numAttempts != MAX_ATTEMPTS) {
        cout << "Invalid value, please reenter: ";
      }
    } else {
      return true;
    }
  }
  return false;
}

// Function to populate an account
void populateAccount(Account accounts[], int& numAccounts, const int maxAccounts) {
  if (numAccounts == maxAccounts) {
    cout << "Cannot execute, array is full" << endl << endl;
    return;
  }

  Account newAccount;
  bool validInput = false;
  string input;
  int attempts = 0;
  // Get account number and validate input
  cout << "Enter account number: ";
  while (attempts < 5) {
    getline(cin, input);
    stringstream ss(input);
    int accountNumber;
    if (ss >> accountNumber && ss.eof() && accountNumber > 0) {
      // Check for duplicate account number (extra credit)
      bool isDuplicate = false;
      for (int i = 0; i < numAccounts; ++i) {
        if (accounts[i].accountNumber == accountNumber) {
          isDuplicate = true;
          break;
        }
      }
      if (!isDuplicate) {
        newAccount.accountNumber = accountNumber;
        validInput = true;
        break;
      } else {
        cout << "Duplicate account number";
        exit(0);
      }
    }
    attempts++;
    if (attempts < 5) {
      cout << "Invalid value, please reenter: ";
    }
  }

  if (validInput) {
    cout << "Enter balance: ";
    // Get balance and validate input
    attempts = 0;
    while (attempts < 5) {
      getline(cin, input);
      stringstream ss(input);
      double balance;
      if (ss >> balance && ss.eof()) {
        string::size_type dotPos = input.find('.');
        if (dotPos == string::npos || input.size() - dotPos <= 3) {
          newAccount.balance = balance;
          break;
        }
      }
      attempts++;
      if (attempts < 5) {
        cout << "Invalid value, please reenter: ";
      }
    }

    if (attempts == 5) {
      cout << "Too many unsuccessful attempts, exiting";
      exit(0);
    }

    // Get owner name and address
    cout << "Enter owner's name: ";
    getline(cin, newAccount.ownerInfo.name);
    cout << "Enter owner's address: ";
    getline(cin, newAccount.ownerInfo.address);
    cout << endl;
    accounts[numAccounts] = newAccount;
    numAccounts++;
  } else {
    cout << "Too many unsuccessful attempts, exiting" << endl;
    exit(0);
  }
}


// Function to print an account
void printAccount(const Account & account) {
  cout << "Account #: " << account.accountNumber << endl;
  cout << "Owner's name: " << account.ownerInfo.name << endl;
  cout << "Owner's address: " << account.ownerInfo.address << endl;
  cout << "Balance: " << account.balance << endl;
}
// Function to display an account
void displayAccount(Account accounts[], int & numAccounts,
  const int maxAccounts) {
  string input;
  int accountNumber;
  bool found = false;
  bool validInput = dataInputandValidation(input);
  if (validInput) {
    //storing account number
    stringstream ss1(input);
    ss1 >> accountNumber;
    for (int i = 0; i < numAccounts; i++) {
      if (accounts[i].accountNumber == accountNumber) {
        printAccount(accounts[i]);
        found = true;
        break;
      }
    }
    if (!found) {
      cout << "Account not found"<< endl << endl;
    }
  } else {
    cout << "Too many unsuccessful attempts, exiting";
    exit(0);
  }

}
// Check if an input contains a digit, character, decimal point, space, asterisk, or pound
bool containsDigitAndChar(const string & str) {
  bool hasDigit = false;
  bool hasChar = false;
  bool hasDecimalPoint = false;
  bool hasSpace = false;
  bool hasAsterisk = false;
  bool hasPound = false;
  for (char c: str) {
    if (isdigit(c)) {
      hasDigit = true;
    } else if (isalpha(c)) {
      hasChar = true;
    } else if (c == '*') {
      hasAsterisk = true;
    } else if (c == '.') {
      hasDecimalPoint = true;
    } else if (c == ' ') {
      hasSpace = true;
    } else if (c == '#') {
        hasPound = true;
    }
    if (hasDigit && (hasChar || hasDecimalPoint || hasSpace || hasAsterisk || hasPound)) {
      return true;
    }
  }
  return false;
}
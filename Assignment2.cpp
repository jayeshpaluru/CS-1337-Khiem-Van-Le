// Author: Jayesh Paluru
// Compiler: GNU GCC
// Date: 2/15/2023
// Purpose of the program: Create a grocery database
#include <iostream>

#include <fstream>

#include <string>

#include <iomanip>

using namespace std;

bool readInventory(const string &fileName, int numRecords, string *pluArray,
                   double *priceArray, string *productNameArray,
                   int *salesTypeArray, int *inventoryArray) {
  ifstream inFile(fileName);
  if (!inFile) {
    return false;
  }

  for (int i = 0; i < numRecords; i++) {
    inFile >> pluArray[i] >> productNameArray[i] >> salesTypeArray[i] >>
        priceArray[i] >> inventoryArray[i];
  }

  inFile.close();
  return true;
}

double checkout(int numRecords, string *pluArray, double *priceArray,
                int *inventoryArray) {
  double total = 0.0;
  string plu;
  double quantity;

  while (true) {
    cout << "Enter PLU, 0 if done: ";
    cin >> plu;

    if (plu == "0") {
      break;
    }

    int i;
    for (i = 0; i < numRecords; i++) {
      if (plu == pluArray[i]) {
        break;
      }
    }
    cout << "Enter quantity: ";
    while (true) {
      cin >> quantity;

      if (quantity <= 0) {
        cout << "Quantity must be positive, reenter: ";
      } else {
        break;
      }
    }
    if (i == numRecords) {
      cout << "PLU not found" << endl;
      continue;
    }
    if (quantity > inventoryArray[i]) {
      quantity = inventoryArray[i];
    }
    total += quantity * priceArray[i];
    inventoryArray[i] -= quantity;
  }

  return total;
}

int main() {
  string filename;
  int numRecords;
  string *plu;
  string *productName;
  int *salesType;
  double *price;
  int *inventory;
  double totalPurchase = 0.0;
  int choice;

  // Prompt the user for the file name
  cout << "Enter the file name: ";
  cin >> filename;

  // Read the file to determine the number of records in the file
  ifstream inputFile(filename);
  if (inputFile.is_open()) {
    string line;
    numRecords = 0;
    while (getline(inputFile, line)) {
      if (line.empty()) {
        inputFile.clear();
      } else {
        numRecords++;
      }
    }
    inputFile.close();
    cout << "There are " << numRecords << " records in the file" << endl
         << endl;
  } else {
    cout << "Error: unable to open file" << endl;
    return 1;
  }

  // Dynamically allocate the parallel arrays to hold the product data items
  plu = new string[numRecords];
  productName = new string[numRecords];
  salesType = new int[numRecords];
  price = new double[numRecords];
  inventory = new int[numRecords];
  // Call readInventory to populate the arrays
  if (readInventory(filename, numRecords, plu, price, productName, salesType,
                    inventory)) {
    cout << "Inventory read from file" << endl;
    cout << "------------------------" << endl;
    for (int i = 0; i < numRecords; i++) {
      if (i < numRecords - 1) {
        cout << "PLU: " << plu[i] << ", " << left << setw(17) << productName[i]
             << ", "
             << "type: " << salesType[i] << ", "
             << "unit price: " << right << setw(5) << price[i] << ", "
             << "inventory: " << inventory[i] << endl;
      } else {
        cout << "PLU: " << plu[i] << ", " << left << setw(17) << productName[i]
             << ", "
             << "type: " << salesType[i] << ", "
             << "unit price: " << right << setw(5) << price[i] << ", "
             << "inventory: " << inventory[i];
      }
    }
    // Display menu and get user's choice
    while (true) {
      cout << endl;
      cout << "1 - Checkout" << endl;
      cout << "2 - Print current inventory" << endl;
      cout << "3 - Quit" << endl;
      cin >> choice;

      // Ask the user to reenter as long as the choice is invalid
      while (choice < 1 || choice > 3) {
        cout << "Invalid choice, reenter: " << endl;
        cin >> choice;
      }

      // Call the appropriate function based on user's choice
      switch (choice) {
      case 1:
        totalPurchase += checkout(numRecords, plu, price, inventory);
        cout << "Total is: $" << totalPurchase << endl;
        totalPurchase = 0.0;
        break;
      case 2:
        cout << endl;
        cout << "Current inventory" << endl;
        cout << "-----------------" << endl;
        for (int i = 0; i < numRecords; i++) {
          if (i < numRecords - 1) {
            cout << "PLU: " << plu[i] << ", " << left << setw(17)
                 << productName[i] << ", "
                 << "type: " << salesType[i] << ", "
                 << "unit price: " << right << setw(5) << price[i] << ", "
                 << "inventory: " << inventory[i] << endl;
          } else {
            cout << "PLU: " << plu[i] << ", " << left << setw(17)
                 << productName[i] << ", "
                 << "type: " << salesType[i] << ", "
                 << "unit price: " << right << setw(5) << price[i] << ", "
                 << "inventory: " << inventory[i];
          }
        }
        break;
      case 3:
        cout << "Updated inventory" << endl;
        cout << "-----------------" << endl;
        for (int i = 0; i < numRecords; i++) {
          if (i < numRecords - 1) {
            cout << "PLU: " << plu[i] << ", " << left << setw(17)
                 << productName[i] << ", "
                 << "type: " << salesType[i] << ", "
                 << "unit price: " << right << setw(5) << price[i] << ", "
                 << "inventory: " << inventory[i] << endl;
          } else {
            cout << "PLU: " << plu[i] << ", " << left << setw(17)
                 << productName[i] << ", "
                 << "type: " << salesType[i] << ", "
                 << "unit price: " << right << setw(5) << price[i] << ", "
                 << "inventory: " << inventory[i] << endl;
          }
        }
        // Release memory
        cout << "Exiting\n";
        delete[] plu;
        delete[] productName;
        delete[] salesType;
        delete[] price;
        delete[] inventory;
        return 0;
      }
    }
  } else {
    // Release memory
    delete[] plu;
    delete[] productName;
    delete[] salesType;
    delete[] price;
    delete[] inventory;

    return 0;
  }
}

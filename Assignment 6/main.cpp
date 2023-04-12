#include "Product.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

//function prototypes
int numRecords(string filename);
void readInventory(string filename, Product * products, int numRecords);
void display(Product * products, int num_records);

int main() {
  int num_records;
  string filename, plu;
  Product * products;
  int choice, amount;
  bool found = false;
  // Get the file name
  cout << "Enter the file name: ";
  cin >> filename;
  // Get number of records in the file
  num_records = numRecords(filename);
  if (num_records == -1) {
    return 1;
  }
  // Display number of records
  cout << "There are " << num_records << " records in the file" << endl;
  // Dynamic allocation of products
  products = new Product[num_records];
  readInventory(filename, products, num_records);
  cout << endl << "Content of object array" << endl << "-----------------------" << endl;
  display(products, num_records);
  // Menu loop
  do {
    cout << endl << "Menu" << endl << "----" << endl;
    cout << "1->Add to inventory           , 2->Subtract from inventory" << endl;
    cout << "3->Print info for all products, 4->Exit" << endl;
    cin >> choice;
    switch (choice) {
    // Add to inventory
    case 1:
      found = false;
      cout << "Enter the PLU: ";
      cin >> plu;
      for (int i = 0; i < num_records; i++) {
        if (plu == products[i].getPLU()) {
          cout << "Enter amount to add: ";
          cin >> amount;
          found = true;
          if (amount <= 0) {
            cout << "Amount must be > 0" << endl;
          } else {
            products[i].setInventory(products[i].getInventory() + amount);
          }
          break;
        }
      }
      if (!found) {
        cout << "PLU not found" << endl;
        break;
      }
      break;
    // Subtract from inventory
    case 2:
      found = false;
      cout << "Enter the PLU: ";
      cin >> plu;
      for (int i = 0; i < num_records; i++) {
        if (plu == products[i].getPLU()) {
          cout << "Enter amount to subtract: ";
          cin >> amount;
          found = true;
          if (amount <= 0) {
            cout << "Amount must be > 0" << endl;
          } else {
            if (products[i].getInventory() >= amount) {
              products[i].setInventory(products[i].getInventory() - amount);
            } else {
              products[i].setInventory(0);
            }
          }
          break;
        }
      }
      if (!found) {
        cout << "PLU not found" << endl;
      }
      break;
    // Display current inventory
    case 3:
      cout << "Current inventory" << endl << "-----------------" << endl;
      display(products, num_records);
      break;
    // Exit
    case 4:
      break;
    default:
      cout << "Invalid choice" << endl;
    }
  } while (choice != 4);
  return 0;
}

// Find number of records in the file
int numRecords(string filename) {
  ifstream infile(filename.c_str());
  if (infile.fail()) {
    cout << "Unable to open file : " << filename;
    return -1;
  } else {
    int numRec = 0;
    string fileLine;
    while (getline(infile, fileLine)) {
      numRec++;
    }
    infile.close();
    return numRec;
  }
}

// Read inventory
void readInventory(string filename, Product * products, int numRecords) {
  ifstream infile(filename.c_str());
  string plu, name;
  int type, inventory;
  double price;
  for (int itr = 0; itr < numRecords; itr++) {
    infile >> plu >> name >> type >> price >> inventory;
    products[itr].setProductAttributes(plu, name, type, price, inventory);
  }
  infile.close();
}

// Display the inventory
void display(Product * products, int num_records) {
  for (int i = 0; i < num_records; i++) {
    cout << left << "PLU: " << products[i].getPLU() << ", ";
    cout << setw(17) << products[i].getName() << ", ";
    cout << "type: " << products[i].getType() << ", ";
    cout << right << "unit price: " << setw(5) << products[i].getPrice() << ", ";
    cout << "inventory: " << products[i].getInventory() << endl;
  }
}

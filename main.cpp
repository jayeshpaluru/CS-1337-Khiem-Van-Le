// Author: Jayesh Paluru
// Compiler: GNU GCC
// Date: 2/27/2023
// Purpose of the program: Perform input validation on grocery records

#include <iostream>
#include <cstring> // Wanted to use library functions like isalpha, isdigit, isalphanum, etc.
#include <fstream>
#include <string>

using namespace std;

string PLU;
bool rowOK = false; // Check if token is valid

// Check if PLU is 4 characters and alphanumeric

bool isvalidPLU(const std::string & text) {
  // Check if PLU is 4 characters  
  if (text.size() != 4) {
    return false;
  }
  // Check if PLU is alphanumeric
  for (char c: text) {
    if (!isalnum(c)) {
      return false;
    }
  }
  return true;
}

// Check if product name is valid
bool isvalidName(string text) {
  if (isalpha(text[0])) // Check if the first letter of each product name is a letter
    return true;
  else
    return false;
}

// Check if product is per unit (0) or per pound (1)
bool isValidType(string text) {
  char temp[10];
  strcpy(temp, text.c_str()); // Copy into temp string
  if (strlen(temp) == 1) { // Check if there is a sales type
    if (temp[0] = 1 || temp[0] == 0) // Check if sales type is valid
      return true;
    else
      return false;
  } else {
    return false;
  }
}

// Check if price has a decimal point and up to decimal places
bool isValidPrice(const std::string & price) {
  if (price.empty()) { // Check if there is a price
    return false;
  }
  bool dotSeen = false; // Boolean to see if there is a decimal point
  int decimalPlaces = 0; // Initialize variable to count # of decimal places
  for (char c: price) {
    if (!isdigit(c) && c != '.' && c != ' ' && c != '\t') { // Check if price is valid
      return false;
    }
    if (c == '.') {
      if (dotSeen) {
        return false;
      }
      dotSeen = true;
    } else if (dotSeen) { // Check to see if price has more than two decimal places
      decimalPlaces++;
      if (decimalPlaces > 2) {
        return false;
      }
    }
  }
  return true;
}

// Check if inventory is valid
bool isValidInventory(string text) {
  char temp[10]; // Make a temporary C-String
  strcpy(temp, text.c_str()); // Copy into temp C-String
  for (int i = 0; i < strlen(temp) + 1 - 1;) { // Check if inventory is valid
    if (isdigit(temp[i]))
      i++;
    else
      return false;
  }
  return true;
}

// Helper function for tokenize to check if first character is a delimiter
bool is_delimiter(char c) {
  const string delimiters = " \t\n\r\f\v";
  return delimiters.find(c) != -1; // Checks if character is delimiter
}

// Create tokens
string tokenize(string & s) {
  string token;
  while (!s.empty() && is_delimiter(s[0])) {
    s.erase(0, 1);
  }
  for (char c: s) {
    if (is_delimiter(c)) {
      break;
    }
    token += c;
  }
  s.erase(0, token.size());
  return token;
}

// Main function
int main() {
  // Retrieve data from file  
  ifstream inFile;
  string fileName;
  int lineNumber = 0;

  cout << "Enter input file:";
  cin >> fileName;

  inFile.open(fileName);

  if (!inFile) {
    cout << "Error: cannot open file " << fileName << endl;
    return 1;
  }

  // Underline the input file name
  cout << endl << "Checking " << fileName << endl;
  cout << string(9 + fileName.length(), '-') << endl << endl;
  while (true) {
    string line, token, tokens[10];
    int k = 0;
    getline(inFile, line);

    if (inFile.eof()) {
      break;
    }

    // Make tokens 
    while (!line.empty()) {
      token = tokenize(line);
      if (token.empty()) break;
      tokens[k] = token;
      k++;
    }

    // Check for valid PLU
    if (isvalidPLU(tokens[0])) {
      cout << "Token #1 is " << tokens[0] << ", PLU is valid" << endl;
      rowOK = true;
    } else {
      cout << "Token #1 is " << tokens[0] << ", PLU is invalid" << endl;
      rowOK = false;
      break;
    }
    // Check for valid product name
    if (isvalidName(tokens[1])) {
      cout << "Token #2 is " << tokens[1] << ", Product name is valid" << endl;
      rowOK = true;
    } else {
      cout << "Token #2 is " << tokens[1] << ", Product name is invalid" <<
        endl;
      rowOK = false;
      break;
    }
    // Check for valid sales type
    if (isValidType(tokens[2])) {
      cout << "Token #3 is " << tokens[2] << ", Sales type is valid" << endl;
      rowOK = true;
    } else {
      cout << "Token #3 is " << tokens[2] << ", Sales type is invalid" << endl;
      rowOK = false;
      break;
    }
    // Check for valid unit price
    if (isValidPrice(tokens[3])) {
      cout << "Token #4 is " << tokens[3] << ", Price is valid" << endl;
      rowOK = true;
    } else {
      cout << "Token #4 is " << tokens[3] << ", Price is invalid" << endl;
      rowOK = false;
      break;
    }
    // Check for valid inventory and if there are more at least 5 tokens
    if (k >= 5) {
      if (isValidInventory(tokens[4])) {
        cout << "Token #5 is " << tokens[4] << ", Inventory is valid" << endl;
        rowOK = true;
      } else {
        cout << "Token #5 is " << tokens[4] << ", Inventory is invalid" << endl;
        rowOK = false;
        break;
      }
    }

    // Check if there are too many tokens
    if (k > 5) {
      cout << "Token #6 is " << tokens[5] << ", Too many items in record" << endl;
      rowOK = false;
      break;
    }

    // Check if there are too many tokens
    if (k < 5) {
      cout << "Inventory is invalid, record has missing items" << endl;
      rowOK = false;
      break;
    }

    cout << endl;

    // Check if the complete record is valid
    if (isvalidPLU(tokens[0]) && isvalidName(tokens[1]) &&
      isValidType(tokens[2]) && isValidPrice(tokens[3]) &&
      isValidInventory(tokens[4]))
      rowOK = true;
    else
      rowOK = false;
  }
  // Check if text file has valid content
  if (rowOK)
    // Prints if text file has valid content
    cout << "######## " << fileName << " has valid content ########" << endl;
  else
    // Prints if text file has invalid content
    cout << endl << "######## " << fileName << " has invalid content ########" << endl;
}
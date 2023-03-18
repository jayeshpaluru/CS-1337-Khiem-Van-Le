// Author: Jayesh Paluru
// Compiler: GNU GCC
// Date: 3/09/2023
// Purpose of the program: Create a student maintenance record

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

using namespace std;
struct Student {
  int netID;
  string major;
  double GPA;
};

int linearSearchID(Student arr[], int numElems, int val, int &nIter) {
  nIter = 0;
  for (int i = 0; i < numElems; i++) {
    nIter++;
    if (arr[i].netID == val) {
      return i;
    }
  }
  return -1;
}


int binarySearchID(Student arr[], int numElems, int value, int &nIter) {
  nIter = 0;
  int l = 0, r = numElems - 1;
  while (l <= r) {
    nIter++;
    int mid = l + (r - l) / 2;
    if (arr[mid].netID == value) {
      return mid;
    } else if (arr[mid].netID < value) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return -1;
}

void modifiedSortGPA(Student array1[], int size) {
  struct Student temp;
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < (size - 1 - i); j++) {
      if (array1[j].GPA > array1[j + 1].GPA) {
        temp = array1[j];
        array1[j] = array1[j + 1];
        array1[j + 1] = temp;
      }
    }
  }
}
void modifiedSortID(Student array1[], int size) {
  struct Student temp;
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < (size - 1 - i); j++) {
      if (array1[j].netID > array1[j + 1].netID) {
        temp = array1[j];
        array1[j] = array1[j + 1];
        array1[j + 1] = temp;
      }
    }
  }
}
void print(Student a[], int size) {
  cout << "index\tnetID\tmajor\tGPA\tindex\tnetID\tmajor\tGPA" << endl;
  for (int i = 0; i < size; i += 2) {
    if (i + 1 < size) {
      cout << i << "\t" << a[i].netID << "\t" << a[i].major << "\t" << fixed << setprecision(2) << a[i].GPA << fixed << setprecision(2) << "\t" << i + 1 << "\t" << a[i + 1].netID << "\t" << a[i + 1].major << "\t" << a[i + 1].GPA << fixed << setprecision(2) << endl;
    } else {
      cout << i << "\t" << a[i].netID << "\t" << a[i].major << "\t" << a[i].GPA << fixed << setprecision(2) << endl;
    }
  }
}
int main() {
  const int NUM_ELMTS = 18;
  int numElems = 0;
  Student studArray[NUM_ELMTS];
  Student studArraysortedbyGPA[NUM_ELMTS];
  Student studArraysortedbyId[NUM_ELMTS];
  string fileName;

  cout << "Enter file name: ";
  cin >> fileName;
  ifstream fin(fileName.c_str());

  string line;
  string word;
while (getline(fin, line)) {
    if (line == "") {
        continue;
    }

    string temp = "";
    int word_count = 0;
    double netID, GPA;
    string major = "";
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ' ') {
            if (word_count == 0) {
                netID = atoi(temp.c_str());
            } else if (word_count == 1) {
                major = temp;
            } else {
                GPA = atof(temp.c_str());
                }
            temp = "";
            word_count++;
            } else {
                temp += line[i];
            }
        }
        GPA = atof(temp.c_str());

        studArray[numElems].netID = netID;
        studArray[numElems].major = major;
        studArray[numElems].GPA = GPA;
        studArraysortedbyGPA[numElems] = studArray[numElems];
        studArraysortedbyId[numElems] = studArray[numElems];
        numElems++;
    }
    fin.close();
  modifiedSortID(studArraysortedbyId, numElems);
  modifiedSortGPA(studArraysortedbyGPA, numElems);
  cout << "Original array:" << endl;
  cout << "---------------" << endl;
  print(studArray, numElems);
  cout << "Array sorted by GPA:" << endl;
  cout << "--------------------" << endl;
  print(studArraysortedbyGPA, numElems);
  cout << "Array sorted by netID:" << endl;
  cout << "----------------------" << endl;
  print(studArraysortedbyId, numElems);
  
  while (true) {
    cout << "***************" << endl;
    cout << "Menu of choices" << endl;
    cout << "***************" << endl;
    cout << "1 - List top n students" << endl;
    cout << "2 - Search on a netID" << endl;
    cout << "3 - Quit" << endl;
    
    int choice = 0;
    cin >> choice;

    if (choice == 1) {
      int n;
      cout << "Enter n:";
      cin >> n;
      cout << "\nTop " << min(n, numElems) << " students are:\n" << endl;
      for (int i = 0; i < n && i < numElems; i++) {
        cout << "netID: " << studArraysortedbyGPA[numElems - i - 1].netID << " ,major: " << studArraysortedbyGPA[numElems - i - 1].major << " ,GPA: " << studArraysortedbyGPA[numElems - i - 1].GPA << fixed << setprecision(2) << endl;
      }
    } else if (choice == 2) {
      int val, nIter = 0, nIter1 = 0;
      cout << "Enter netID:";
      cin >> val;
      int linearIndex = linearSearchID(studArray, numElems, val, nIter);
      int binaryIndex = binarySearchID(studArraysortedbyId, numElems, val, nIter1);
      cout << "\nResult of linear search:" << endl;
      cout << "------------------------" << endl;
      if (linearIndex == -1) {
        cout << "Student not found" << endl;
      } else {
        cout << "Student found at index " << linearIndex << ", " << " major is " << studArray[linearIndex].major << ", " << " GPA is " << studArray[linearIndex].GPA << endl;
      }
      cout << "It took " << nIter << " iterations" << endl;
      cout << "\nResult of binary search:" << endl;
      cout << "------------------------" << endl;
      if (binaryIndex == -1) {
        cout << "Student not found" << endl;
      } else {
        cout << "Student found at index " << binaryIndex << ", " << " major is " << studArraysortedbyId[binaryIndex].major << ", " << " GPA is " << studArraysortedbyId[binaryIndex].GPA << endl;
      }
      cout << "It took " << nIter1 << " iterations" << endl;
    } else if (choice == 3) {
      cout << "Exiting" << endl;
      break;
    } else {
      cout << "Enter correct option" << endl;
    }
  }
}

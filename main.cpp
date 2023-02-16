// Author: Jayesh Paluru
// Compiler: GNU GCC
// Date: 2/08/2023
// Purpose of the program: Create a student maintenance record
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

const int NUM_ELMTS = 18;

// netID, major and GPA are parallel arrays
int netID[NUM_ELMTS]; // Original netID array
string major[NUM_ELMTS]; // Original major array
double GPA[NUM_ELMTS]; // Original GPA array

// sortedGPAbyGPA is sorted by GPA, and sortedNetIDbyGPA and sortedMajorbyGPA are parallel arrays
double sortedGPAbyGPA[NUM_ELMTS]; // GPA array, sorted by GPA
int sortedNetIDbyGPA[NUM_ELMTS];
string sortedMajorbyGPA[NUM_ELMTS];

// sortedNetIDbyID is sorted by netID, and sortedMajorbyID and sortedGPAbyID are parallel arrays
int sortedNetIDbyID[NUM_ELMTS]; // netID array,sorted by netID
string sortedMajorbyID[NUM_ELMTS];
double sortedGPAbyID[NUM_ELMTS];

int linearSearchID(int arr[], int numElems, int value, int &nIter)
{
    nIter = 0;
    for (int i = 0; i < numElems; i++)
    {
        nIter++;
        if (arr[i] == value)
        {
            return i;
        }
    }
    return -1;
}

int binarySearchID(int arr[], int numElems, int value, int &nIter)
{
    nIter = 0;
    int low = 0, high = numElems - 1;
    while (low <= high)
    {
        nIter++;
        int mid = (low + high) / 2;
        if (arr[mid] == value)
        {
            return mid;
        }
        else if (arr[mid] < value)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}

void modifiedSortGPA(double array1[], int array2[], string array3[], int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 2; j++) {
      if (array1[j] > array1[j + 1]) {
        swap(array1[j], array1[j + 1]);
        swap(array2[j], array2[j + 1]);
        swap(array3[j], array3[j + 1]);
      }
    }
  }
}

void modifiedSortID(int array2[], double array1[], string array3[], int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 2; j++) {
      if (array2[j] > array2[j + 1]) {
        swap(array2[j], array2[j + 1]);
        swap(array1[j], array1[j + 1]);
        swap(array3[j], array3[j + 1]);
      }
    }
  }
}


void displayArrays() {
  int size = 0;
  for (int i: netID) {
    if (i == 0) {
      break;
    }
    size++;
  }
  cout << "Original arrays:" << endl;
  cout << "----------------" << endl;
  cout << setw(7) << "index" << setw(7) << "netID" << setw(8) << "major" << setw(6) << "GPA" << setw(7) << "index" << setw(7) << "netID" << setw(8) << "major" << setw(6) << "GPA" << endl;
  for (int i = 0; i < size; i++) {
    cout << setw(7) << i << setw(7) << netID[i] << setw(8) << major[i] << setw(6)<< fixed << setprecision(2) << GPA[i];
    if (i % 2 != 0 && i != 0) {
      cout << endl;
    }
  }

  cout << endl << "Arrays sorted by GPA:" << endl;
  cout << "---------------------" << endl;
    cout << setw(7) << "index" << setw(7) << "netID" << setw(8) << "major" << setw(6) << "GPA" << setw(7) << "index" << setw(7) << "netID" << setw(8) << "major" << setw(6) << "GPA" << endl;
  for (int i = 0; i < size; i++) {
    cout << fixed << setprecision(2);
    cout << setw(7) << i << setw(7) << sortedNetIDbyGPA[i] << setw(8) << sortedMajorbyGPA[i] << setw(6) << sortedGPAbyGPA[i]<< fixed << setprecision(2);
    if (i % 2 != 0 && i != 0) {
      cout << endl;
    }
  }

  cout << endl << "Arrays sorted by netID:" << endl;
  cout << "-----------------------" << endl;
    cout << setw(7) << "index" << setw(7) << "netID" << setw(8) << "major" << setw(6) << "GPA" << setw(7) << "index" << setw(7) << "netID" << setw(8) << "major" << setw(6) << "GPA" << endl;
  for (int i = 0; i < size; i++) {
    cout << setw(7) << i << setw(7) << sortedNetIDbyID[i] << setw(8) << sortedMajorbyID[i] << setw(6) << sortedGPAbyID[i]<< fixed << setprecision(2);
    if (i % 2 != 0 && i != 0) {
      cout << endl;
      }
  }
  
}

void displayTopNStudents(int n, int netID[], string major[], double GPA[]) {
  int maxIndex = 0;
  for (int i = 0; i < n; i++) {
    maxIndex = i;
    for (int j = i + 1; j < 10; j++) {
      if (GPA[j] > GPA[maxIndex]) {
        maxIndex = j;
      }
    }
    int tempNetID = netID[i];
    netID[i] = netID[maxIndex];
    netID[maxIndex] = tempNetID;

    string tempMajor = major[i];
    major[i] = major[maxIndex];
    major[maxIndex] = tempMajor;

    float tempGPA = GPA[i];
    GPA[i] = GPA[maxIndex];
    GPA[maxIndex] = tempGPA;
  }
  for (int i = 0; i < n; i++) {
    cout << "netID: " << netID[i] << ", major: " << major[i] << ", GPA: " << (GPA[i]*100)/100 << fixed << setprecision(2) << endl;
  }
}

int main() {
  int size = 0; // Number of students
  // Prompt the user for file name
  cout << "Enter file name: ";
  string fileName;
  cin >> fileName;

  // Open the file and read the data
  ifstream file(fileName);
  if (file.is_open()) {
    // Read the data into arrays
    while (!file.eof() && size < NUM_ELMTS) {
      file >> netID[size] >> major[size] >> GPA[size];
      size++;
    }

    // Copy arrays
    for (int i = 0; i < size; i++) {
      sortedNetIDbyGPA[i] = netID[i];
      sortedGPAbyGPA[i] = GPA[i];
      sortedMajorbyGPA[i] = major[i];
      sortedNetIDbyID[i] = netID[i];
      sortedGPAbyID[i] = GPA[i];
      sortedMajorbyID[i] = major[i];
    }

    // Sort arrays
    modifiedSortGPA(sortedGPAbyGPA, sortedNetIDbyGPA, sortedMajorbyGPA, size);
    modifiedSortID(sortedNetIDbyID, sortedGPAbyID, sortedMajorbyID, size);

    // Close the file
    file.close();
  } else {
    cout << "Could not open file\nExiting\n";
    return 0;
  }

  displayArrays();
  cout << endl;

  // Display the menu and perform actions
  int choice = 0;
  while (choice != 3) {
    cout << "***************" << endl;
    cout << "Menu of choices" << endl;
    cout << "***************" << endl;
    cout << "1 - List top n students" << endl;
    cout << "2 - Search on a netID" << endl;
    cout << "3 - Quit" << endl;

    cin >> choice;

    if (choice == 1) {
      int n;
      cout << "Enter n: ";
      cin >> n;
      cout << "Top " << n - 2 << " students are:" << endl << endl;

      displayTopNStudents(n - 2, sortedNetIDbyGPA, sortedMajorbyGPA, sortedGPAbyGPA);
    } else if (choice == 2) {
      int searchID;
      int linearIterations = 0, binaryIterations = 0;
      int size = 0;
        for (int i: netID) {
          if (i == 0) {
            break;
          }
          size++;
        }
      cout << "Enter netID: ";
      cin >> searchID;
      int linearIndex = linearSearchID(sortedNetIDbyID, size, searchID, linearIterations);
      int binaryIndex = binarySearchID(sortedNetIDbyID, size, searchID, binaryIterations);
      if (linearIndex == -1) {
        cout << "Result of linear search:" << endl;
        cout << "------------------------" << endl;
        cout << "Student not found" << endl;
        cout << "It took " << linearIterations << " iterations" << endl;
      } else {
        cout << "Result of linear search:" << endl;
        cout << "------------------------" << endl;
        cout << "Student found at index " << linearIndex << ", GPA is " << sortedGPAbyID[linearIndex] << fixed << setprecision(2) << endl;
        cout << "It took " << linearIterations << " iterations" << endl << endl;
      }
      if (binaryIndex == -1) {
        cout << "Result of binary search:" << endl;
        cout << "------------------------" << endl;
        cout << "Student not found" << endl;
        cout << "It took " << binaryIterations << " iterations" << endl;
      } else {
        cout << "Result of binary search:" << endl;
        cout << "------------------------" << endl;
        cout << "Student found at index " << binaryIndex << ", GPA is " << sortedGPAbyID[binaryIndex] << fixed << setprecision(2) << endl;
        cout << "It took " << binaryIterations << " iterations" << endl << endl;
      }
    }
  }
  cout << "Exiting" << endl;
  return 0;
  }


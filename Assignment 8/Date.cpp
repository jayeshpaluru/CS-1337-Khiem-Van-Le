#include "Date.h"
#include <iostream>
#include <iomanip>

using namespace std;
const int daysInMonth[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

// Helper function to determine if a year is a leap year
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Helper function to determine the number of elapsed hours since 1/1/1
int elapsedHours(int month, int day, int year, int hour) {
    int n = (365 * (year - 1) + daysInMonth[month - 1] + day - 1) * 24 + hour;
    if (month > 2 && isLeapYear(year)) {
        n += 24;
    }
    return n;
}

// Copy constructor
void Date::set(int month_, int day_, int year_, int hour_) {
    month = month_;
    day = day_;
    year = year_;
    hour = hour_;
}

// Overloaded equality operator
bool Date::operator==(const Date& rhs) {
    return month == rhs.month && day == rhs.day && year == rhs.year && hour == rhs.hour;
}

// Overloaded less than operator
bool Date::operator<(const Date& rhs) {
    return elapsedHours(month, day, year, hour) < elapsedHours(rhs.month, rhs.day, rhs.year, rhs.hour);
}

// Overloaded less than or equal to operator
bool Date::operator<=(const Date& rhs) {
    return *this == rhs || *this < rhs;
}

// Overloaded subtraction operator
int Date::operator-(const Date& rhs) {
    return elapsedHours(month, day, year, hour) - elapsedHours(rhs.month, rhs.day, rhs.year, rhs.hour);
}

// Print function
void Date::print() {
    static const char* monthNames[] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    cout << monthNames[month] << " " << day << ", " << year << ", " << hour << ":00";
}

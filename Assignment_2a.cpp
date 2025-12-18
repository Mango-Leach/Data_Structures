#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    string year;
    string division;
    string name;
    int rollNo;

    Student() {
        year = "";
        division = "";
        name = "";
        rollNo = 0;
    }

    Student(string y, string d, string n, int r) {
        year = y;
        division = d;
        name = n;
        rollNo = r;
    }

    void display() const {
        cout << "Details: " << year << " "
             << division << " "
             << name << " (Roll No: "
             << rollNo << ")" << endl;
    }
};

int searchStudent(Student students[], int n,
                  string year, string div, string name, int rollNo) {
    for (int i = 0; i < n; i++) {
        if (students[i].year == year &&
            students[i].division == div &&
            students[i].name == name &&
            students[i].rollNo == rollNo) {
            return i; 
        }
    }
    return -1; 
}

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    Student* students = new Student[n]; // dynamic array

    // Input student details
    for (int i = 0; i < n; i++) {
        cout << "\nEnter details of student " << i + 1 << ":\n";
        cout << "Year: ";
        cin >> students[i].year;
        cout << "Division: ";
        cin >> students[i].division;
        cout << "Name: ";
        cin >> students[i].name;
        cout << "Roll No: ";
        cin >> students[i].rollNo;
    }

    // Input search criteria
    string searchYear, searchDiv, searchName;
    int searchRoll;
    cout << "\nEnter student details to search:\n";
    cout << "Year: ";
    cin >> searchYear;
    cout << "Division: ";
    cin >> searchDiv;
    cout << "Name: ";
    cin >> searchName;
    cout << "Roll No: ";
    cin >> searchRoll;

    int index = searchStudent(students, n, searchYear, searchDiv, searchName, searchRoll);

    if (index != -1) {
        cout << "\nStudent found!\n";
        students[index].display();
    } else {
        cout << "\nStudent not found.\n";
    }

    delete[] students; // free dynamic memory
    return 0;
}

#include <iostream>
#include <string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    float marks;
    bool isEmpty;
    
    Student() : rollNo(-1), name(""), marks(0.0), isEmpty(true) {}
};

class HashTable {
private:
    int size;
    Student* table;

public:
    HashTable(int s);
    int hashFunction(int rollNo);
    void insert(int rollNo, string name, float marks);
    bool search(int rollNo);
    void display();
    void displayStudent(int rollNo);
};

// Constructor
HashTable::HashTable(int s) {
    size = s;
    table = new Student[size];
}

// Hash Function
int HashTable::hashFunction(int rollNo) {
    return rollNo % size;
}

// Insert Operation (Linear Probing)
void HashTable::insert(int rollNo, string name, float marks) {
    int index = hashFunction(rollNo);
    int startIndex = index;

    while (!table[index].isEmpty) {
        if (table[index].rollNo == rollNo) {
            cout << "Roll number " << rollNo << " already exists!\n";
            return;
        }
        index = (index + 1) % size;
        
        if (index == startIndex) {
            cout << "Hash table is full!\n";
            return;
        }
    }

    table[index].rollNo = rollNo;
    table[index].name = name;
    table[index].marks = marks;
    table[index].isEmpty = false;
    cout << "Inserted student (Roll No: " << rollNo << ") at index " << index << endl;
}

// Search Operation (Linear Probing)
bool HashTable::search(int rollNo) {
    int index = hashFunction(rollNo);
    int startIndex = index;

    while (!table[index].isEmpty) {
        if (table[index].rollNo == rollNo)
            return true;

        index = (index + 1) % size;

        if (index == startIndex)
            return false;
    }
    return false;
}

// Display Table
void HashTable::display() {
    cout << "\n========== Hash Table (Student Records) ==========\n";
    cout << "Index\tRoll No\tName\t\tMarks\n";
    cout << "==================================================\n";
    for (int i = 0; i < size; i++) {
        if (!table[i].isEmpty)
            cout << i << "\t" << table[i].rollNo << "\t" << table[i].name << "\t\t" << table[i].marks << endl;
        else
            cout << i << "\t" << "Empty" << endl;
    }
    cout << "==================================================\n";
}

// Display specific student details
void HashTable::displayStudent(int rollNo) {
    int index = hashFunction(rollNo);
    int startIndex = index;

    while (!table[index].isEmpty) {
        if (table[index].rollNo == rollNo) {
            cout << "\n--- Student Details ---\n";
            cout << "Roll No: " << table[index].rollNo << endl;
            cout << "Name: " << table[index].name << endl;
            cout << "Marks: " << table[index].marks << endl;
            cout << "Index in Table: " << index << endl;
            return;
        }

        index = (index + 1) % size;

        if (index == startIndex)
            break;
    }
    cout << "Student with roll number " << rollNo << " not found!\n";
}

int main() {
    int size, n, rollNo;
    string name;
    float marks;

    cout << "Enter size of hash table: ";
    cin >> size;

    HashTable ht(size);

    cout << "How many student records to insert? ";
    cin >> n;

    cout << "\nEnter student details:\n";
    for (int i = 0; i < n; i++) {
        cout << "\nStudent " << (i + 1) << ":\n";
        cout << "Roll No: ";
        cin >> rollNo;
        cout << "Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Marks: ";
        cin >> marks;
        
        ht.insert(rollNo, name, marks);
    }

    ht.display();

    cout << "\nEnter roll number to search: ";
    cin >> rollNo;

    if (ht.search(rollNo)) {
        cout << "Student found!\n";
        ht.displayStudent(rollNo);
    } else {
        cout << "Student with roll number " << rollNo << " not found in the hash table.\n";
    }

    return 0;
}

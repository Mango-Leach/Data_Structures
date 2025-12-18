#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int rollNo;
    int marks;
};

void display(Student arr[], int n) {
    cout << "\nRoll No\tName\tMarks\n";
    for (int i = 0; i < n; i++) {
        cout << arr[i].rollNo << "\t" << arr[i].name << "\t" << arr[i].marks << endl;
    }
}

int partition(Student arr[], int low, int high, int n, int &pass) {
    int pivot = arr[high].marks;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].marks < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);

    pass++;
    cout << "Pass " << pass << ": ";
    display(arr, n);

    return i + 1;
}

void quickSort(Student arr[], int low, int high, int n, int &pass) {
    if (low < high) {
        int pi = partition(arr, low, high, n, pass);
        quickSort(arr, low, pi - 1, n, pass);
        quickSort(arr, pi + 1, high, n, pass);
    }
}

pair<Student, Student> findMinMax(Student arr[], int low, int high) {
    if (low == high) {
        return {arr[low], arr[low]};
    }
    if (high == low + 1) {
        if (arr[low].marks < arr[high].marks)
            return {arr[low], arr[high]};
        else
            return {arr[high], arr[low]};
    }
    int mid = (low + high) / 2;
    pair<Student, Student> left = findMinMax(arr, low, mid);
    pair<Student, Student> right = findMinMax(arr, mid + 1, high);

    Student finalMin = (left.first.marks < right.first.marks) ? left.first : right.first;
    Student finalMax = (left.second.marks > right.second.marks) ? left.second : right.second;

    return {finalMin, finalMax};
}

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    Student arr[100];

    for (int i = 0; i < n; i++) {
        cout << "\nEnter details of student " << i + 1 << ":\n";
        cout << "Roll No: ";
        cin >> arr[i].rollNo;
        cout << "Name: ";
        cin >> arr[i].name;
        cout << "Marks: ";
        cin >> arr[i].marks;
    }

    cout << "\nOriginal List:";
    display(arr, n);

    int pass = 0;
    quickSort(arr, 0, n - 1, n, pass);

    cout << "\nSorted List:";
    display(arr, n);

    pair<Student, Student> ans = findMinMax(arr, 0, n - 1);
    cout << "\nMinimum Marks: " << ans.first.marks 
         << " (Roll No: " << ans.first.rollNo << ", Name: " << ans.first.name << ")" << endl;
    cout << "Maximum Marks: " << ans.second.marks 
         << " (Roll No: " << ans.second.rollNo << ", Name: " << ans.second.name << ")" << endl;

    return 0;
}

#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int marks;
    int roll_no;
};

// Bubble Sort function
void bubbleSort(Student arr[], int n) {
    int swapCount = 0;
    for (int i = 0; i < n - 1; i++) {
        cout << "\nPass " << i + 1 << ": ";
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].marks < arr[j + 1].marks) {
                swap(arr[j], arr[j + 1]);
                swapCount++;
            }
        }

        for (int k = 0; k < n; k++) {
            cout << arr[k].name << "(" << arr[k].marks << ") ";
        }
        cout << endl;
    }
    cout << "\nTotal swaps performed: " << swapCount << endl;
}

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    Student arr[50]; 
    for (int i = 0; i < n; i++) {
        cout << "\nEnter name of student " << i + 1 << ": ";
        cin >> arr[i].name;
        cout << "Enter marks: ";
        cin >> arr[i].marks;
    }

    bubbleSort(arr, n);

    cout << "\nFinal Roll Number Assignment (Topper = Roll No. 1):\n";
    for (int i = 0; i < n; i++) {
        arr[i].roll_no = i + 1;
        cout << "Roll No. " << arr[i].roll_no << " -> " << arr[i].name 
             << " (Marks: " << arr[i].marks << ")" << endl;
    }

    return 0;
}

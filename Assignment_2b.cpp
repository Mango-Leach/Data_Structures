#include <iostream>
#include <string>
using namespace std;


struct Student {
    string name;
    int roll_no;
    int total_marks;
};


void display(Student arr[], int n) {
    cout << "\nRoll No\tName\tMarks\n";
    for (int i = 0; i < n; i++) {
        cout << arr[i].roll_no << "\t" << arr[i].name << "\t" << arr[i].total_marks << endl;
    }
}


int bubbleSort(Student arr[], int n) {
    int swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].roll_no > arr[j + 1].roll_no) {
                swap(arr[j], arr[j + 1]);
                swaps++;
            }
        }
    }
    return swaps;
}


int quickSortSwaps = 0; 

int partition(Student arr[], int low, int high) {
    int pivot = arr[high].roll_no; 
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].roll_no < pivot) {
            i++;
            swap(arr[i], arr[j]);
            quickSortSwaps++;
        }
    }
    swap(arr[i + 1], arr[high]);
    quickSortSwaps++;
    return (i + 1);
}

void quickSort(Student arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    Student students[n];

    
    for (int i = 0; i < n; i++) {
        cout << "\nEnter details of student " << i + 1 << ":\n";
        cout << "Roll No: ";
        cin >> students[i].roll_no;
        cout << "Name: ";
        cin >> students[i].name;
        cout << "Total Marks: ";
        cin >> students[i].total_marks;
    }

   
    Student bubbleArr[n], quickArr[n];
    for (int i = 0; i < n; i++) {
        bubbleArr[i] = students[i];
        quickArr[i] = students[i];
    }

    cout << "\nOriginal List:";
    display(students, n);

    // Bubble Sort
    int bubbleSwaps = bubbleSort(bubbleArr, n);
    cout << "\nAfter Bubble Sort (by Roll No):";
    display(bubbleArr, n);
    cout << "Total swaps in Bubble Sort = " << bubbleSwaps << endl;

   // Quick Sort
    quickSortSwaps = 0; 
    quickSort(quickArr, 0, n - 1);
    cout << "\nAfter Quick Sort (by Roll No):";
    display(quickArr, n);
    cout << "Total swaps in Quick Sort = " << quickSortSwaps << endl;

    return 0;
}

#include <iostream>
#include <string>
using namespace std;

struct Employee {
    string name;
    float height;
    float weight;
    float avg; 
};

class Sorting {
public:
  
    static void calculateAvg(Employee arr[], int n) {
        for (int i = 0; i < n; i++) {
            arr[i].avg = (arr[i].height + arr[i].weight) / 2.0;
        }
    }

 
    static void selectionSort(Employee arr[], int n) {
        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j].avg < arr[minIndex].avg) {
                    minIndex = j;
                }
            }
            swap(arr[i], arr[minIndex]);
        }
    }

    
    static void merge(Employee arr[], int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        Employee L[50], R[50]; 
        for (int i = 0; i < n1; i++) L[i] = arr[left + i];
        for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i].avg <= R[j].avg) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];
    }

    static void mergeSort(Employee arr[], int left, int right) {
        if (left < right) {
            int mid = (left + right) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    
    static void display(Employee arr[], int n) {
        for (int i = 0; i < n; i++) {
            cout << arr[i].name << " (H=" << arr[i].height
                 << ", W=" << arr[i].weight
                 << ", Avg=" << arr[i].avg << ")\n";
        }
    }
};

int main() {
    int n;
    cout << "Enter number of employees: ";
    cin >> n;

    Employee arr1[50], arr2[50];
    for (int i = 0; i < n; i++) {
        cout << "\nEnter name of employee " << i + 1 << ": ";
        cin >> arr1[i].name;
        cout << "Enter height(in cm): ";
        cin >> arr1[i].height;
        cout << "Enter weight(in Kg): ";
        cin >> arr1[i].weight;
    }

    for (int i = 0; i < n; i++) arr2[i] = arr1[i];

  
    Sorting::calculateAvg(arr1, n);
    Sorting::calculateAvg(arr2, n);

   
    cout << "\nSorting using Selection Sort:\n";
    Sorting::selectionSort(arr1, n);
    Sorting::display(arr1, n);

  
    cout << "\nSorting using Merge Sort:\n";
    Sorting::mergeSort(arr2, 0, n - 1);
    Sorting::display(arr2, n);

    cout << "\n--- Time Complexity Analysis ---\n";
    cout << "Selection Sort: O(n^2)\n";
    cout << "Merge Sort: O(n log n)\n";
    cout << "Conclusion: Merge Sort is more efficient for larger datasets.\n";

    return 0;
}

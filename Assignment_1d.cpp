#include <iostream>
using namespace std;

struct Element {
    int row;
    int col;
    int value;
};

int main() {
    int m, n;
    cout << "Enter number of rows and columns: ";
    cin >> m >> n;

    int matrix[20][20];
    cout << "Enter matrix elements:\n";
    int zeroCount = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
            if (matrix[i][j] == 0)
                zeroCount++;
        }
    }

    int total = m * n;
    if (zeroCount <= total / 2) {
        cout << "\nMatrix is NOT Sparse (less than 50% zeros)." << endl;
        return 0;
    }

    cout << "\nMatrix is Sparse. Compact Representation:\n";
    Element compact[100];
    int k = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != 0) {
                compact[k].row = i;
                compact[k].col = j;
                compact[k].value = matrix[i][j];
                k++;
            }
        }
    }

    cout << "Row\tCol\tValue\n";
    for (int i = 0; i < k; i++) {
        cout << compact[i].row << "\t" << compact[i].col 
             << "\t" << compact[i].value << endl;
    }

    // Simple Transpose
    cout << "\nSimple Transpose (Row <-> Col):\n";
    cout << "Row\tCol\tValue\n";
    for (int i = 0; i < k; i++) {
        cout << compact[i].col << "\t" << compact[i].row 
             << "\t" << compact[i].value << endl;
    }

    return 0;
}

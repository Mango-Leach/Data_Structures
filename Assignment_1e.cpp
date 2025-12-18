#include <iostream>
using namespace std;

struct Element {
    int row, col, value;
};

int main() {
    int m, n;
    cout << "Enter number of rows and columns: ";
    cin >> m >> n;

    int matrix[20][20];
    cout << "Enter matrix elements:\n";
    int zeroCount = 0;

    // Read matrix & count zeros
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
            if (matrix[i][j] == 0) zeroCount++;
        }
    }

    int total = m * n;
    if (zeroCount <= total / 2) {
        cout << "\nMatrix is NOT Sparse (less than 50% zeros)." << endl;
        return 0;
    }

    // Step 1: Build Compact Representation
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

    cout << "\nCompact Representation:\nRow\tCol\tValue\n";
    for (int i = 0; i < k; i++)
        cout << compact[i].row << "\t" << compact[i].col << "\t" << compact[i].value << endl;

    // Step 2: Fast Transpose
    Element transpose[100];
    int colCount[20] = {0};
    int startPos[20] = {0};

    // Count number of entries in each column
    for (int i = 0; i < k; i++)
        colCount[compact[i].col]++;

    // Compute starting positions
    startPos[0] = 0;
    for (int i = 1; i < n; i++)
        startPos[i] = startPos[i - 1] + colCount[i - 1];

    // Place elements in transposed array
    for (int i = 0; i < k; i++) {
        int pos = startPos[compact[i].col]++;
        transpose[pos].row = compact[i].col;
        transpose[pos].col = compact[i].row;
        transpose[pos].value = compact[i].value;
    }

    // Display fast transpose
    cout << "\nFast Transpose (Row <-> Col):\nRow\tCol\tValue\n";
    for (int i = 0; i < k; i++)
        cout << transpose[i].row << "\t" << transpose[i].col << "\t" << transpose[i].value << endl;

    return 0;
}

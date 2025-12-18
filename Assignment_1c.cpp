#include <iostream>
#include <chrono>
using namespace std;

void inputMatrix(int** matrix, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << "Enter element [" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
    }
}

void displayMatrix(int** matrix, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void multiplyMatrices(int** matrix1, int** matrix2, int** result, 
                     int rows1, int cols1, int cols2) {
    auto start = chrono::high_resolution_clock::now();
    
    
    for(int i = 0; i < rows1; i++) {
        for(int j = 0; j < cols2; j++) {
            result[i][j] = 0;
            for(int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    
    cout << "\nTime taken by multiplication: " << duration.count() << " microseconds" << endl;
}

int main() {
    int rows1, cols1, rows2, cols2;
    
    cout << "Enter dimensions of first matrix (rows cols): ";
    cin >> rows1 >> cols1;
    
    cout << "Enter dimensions of second matrix (rows cols): ";
    cin >> rows2 >> cols2;
    
    if(cols1 != rows2) {
        cout << "Matrix multiplication not possible!" << endl;
        return 1;
    }
    
    
    int** matrix1 = new int*[rows1];
    int** matrix2 = new int*[rows2];
    int** result = new int*[rows1];
    
    for(int i = 0; i < rows1; i++) matrix1[i] = new int[cols1];
    for(int i = 0; i < rows2; i++) matrix2[i] = new int[cols2];
    for(int i = 0; i < rows1; i++) result[i] = new int[cols2];
    
    cout << "\nEnter elements of first matrix:\n";
    inputMatrix(matrix1, rows1, cols1);
    
    cout << "\nEnter elements of second matrix:\n";
    inputMatrix(matrix2, rows2, cols2);
    
    cout << "\nFirst Matrix:\n";
    displayMatrix(matrix1, rows1, cols1);
    
    cout << "\nSecond Matrix:\n";
    displayMatrix(matrix2, rows2, cols2);
    
    multiplyMatrices(matrix1, matrix2, result, rows1, cols1, cols2);
    
    cout << "\nResultant Matrix:\n";
    displayMatrix(result, rows1, cols2);
    
    for(int i = 0; i < rows1; i++) delete[] matrix1[i];
    for(int i = 0; i < rows2; i++) delete[] matrix2[i];
    for(int i = 0; i < rows1; i++) delete[] result[i];
    delete[] matrix1;
    delete[] matrix2;
    delete[] result;
    
    return 0;
}
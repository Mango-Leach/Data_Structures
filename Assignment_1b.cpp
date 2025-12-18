#include <iostream>
using namespace std;

void generateOddMagicSquare(int** square, int n) {
    int i = n/2, j = n-1;
    for (int num = 1; num <= n*n;) {
        if (i == -1 && j == n) {
            j = n-2;
            i = 0;
        }
        else {
            if (j == n)
                j = 0;
                
            if (i < 0)
                i = n-1;
        }
        if (square[i][j])
        {
            j -= 2;
            i++;
            continue;
        }
        else
            square[i][j] = num++;
        j++;
        i--;
    }
}

void generateEvenMagicSquare(int** square, int n) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            square[i][j] = ((i+1)*(j+1));
            
    for(int i = 0; i < n/4; i++)
        for(int j = 0; j < n/4; j++)
            square[i][j] = (n*n + 1) - square[i][j];
            
    for(int i = 0; i < n/4; i++)
        for(int j = 3*(n/4); j < n; j++)
            square[i][j] = (n*n + 1) - square[i][j];
            
    for(int i = 3*(n/4); i < n; i++)
        for(int j = 0; j < n/4; j++)
            square[i][j] = (n*n + 1) - square[i][j];
            
    for(int i = 3*(n/4); i < n; i++)
        for(int j = 3*(n/4); j < n; j++)
            square[i][j] = (n*n + 1) - square[i][j];
            
    for(int i = n/4; i < 3*(n/4); i++)
        for(int j = n/4; j < 3*(n/4); j++)
            square[i][j] = (n*n + 1) - square[i][j];
}

void printMagicSquare(int** square, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cout << square[i][j] << "\t";
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter the size of magic square: ";
    cin >> n;
    
    int** magicSquare = new int*[n];
    for(int i = 0; i < n; i++)
        magicSquare[i] = new int[n]();
        
    if(n % 2 == 0)
        generateEvenMagicSquare(magicSquare, n);
    else
        generateOddMagicSquare(magicSquare, n);
        
    cout << "\nThe Magic Square is:\n";
    printMagicSquare(magicSquare, n);
    
    for(int i = 0; i < n; i++)
        delete[] magicSquare[i];
    delete[] magicSquare;
    
    return 0;
}
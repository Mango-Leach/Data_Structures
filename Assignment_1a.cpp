#include <iostream>
using namespace std;

int main() {
    char str_1[100], str_2[100];
    int choice;

    do {
        cout << "\n=== String Operations Menu ===\n";
        cout << "1. Enter String\n";
        cout << "2. Calculate String Length\n";
        cout << "3. Copy String\n";
        cout << "4. Reverse String\n";
        cout << "5. Concatenate Strings\n";
        cout << "6. Find Substring\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                cout << "Enter string: ";
                cin.getline(str_1, 100);
                cout << "String entered successfully: " << str_1 << endl;
                break;
            }
            case 2: {
                int i = 0, length = 0;
                while (str_1[i] != '\0') {
                    length++;
                    i++;
                }
                cout << "Original string: " << str_1 << endl;
                cout << "Length of the string: " << length << endl;
                break;
            }
            case 3: {
                // Copy string without using strcpy()
                int i = 0;
                while (str_1[i] != '\0') {
                    str_2[i] = str_1[i];
                    i++;
                }
                str_2[i] = '\0';
                cout << "Original string: " << str_1 << endl;
                cout << "Copied string: " << str_2 << endl;
                break;
            }
            case 4: {
                int i = 0, len = 0;
                while (str_1[i] != '\0') {
                    len++;
                    i++;
                }
                
                char rev_str[100];
                for (i = 0; i < len; i++) {
                    rev_str[i] = str_1[len - 1 - i];
                }
                rev_str[len] = '\0';
                
                cout << "Original string: " << str_1 << endl;
                cout << "Reversed string: " << rev_str << endl;
                break;
            }
            case 5: {
                char str_3[200];
                cout << "Enter second string: ";
                cin.getline(str_2, 100);
                
                int i = 0, j = 0;
                while (str_1[i] != '\0') {
                    str_3[i] = str_1[i];
                    i++;
                }
                while (str_2[j] != '\0') {
                    str_3[i] = str_2[j];
                    i++;
                    j++;
                }
                str_3[i] = '\0';
                
                cout << "First string: " << str_1 << endl;
                cout << "Second string: " << str_2 << endl;
                cout << "Concatenated string: " << str_3 << endl;
                break;
            }
            case 6: {
                char substr[100];
                cout << "Enter substring to search: ";
                cin.getline(substr, 100);
                int i = 0, found = 0;
                while (str_1[i] != '\0') {
                    int j = 0, k = i;    
                    while (str_1[k] == substr[j] && substr[j] != '\0' && str_1[k] != '\0') {
                        k++;
                        j++;
                    }
                    if (substr[j] == '\0') {
                        found = 1;
                        break;
                    }
                    i++;
                }
                
                cout << "Original string: " << str_1 << endl;
                cout << "Substring to find: " << substr << endl;
                if (found)
                    cout << "Substring found in the string.\n";
                else
                    cout << "Substring not found in the string.\n";
                break;
            }
            case 7:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);
    return 0;
}
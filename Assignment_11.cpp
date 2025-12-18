#include <iostream>
using namespace std;

class HashTable {
private:
    int size;
    int* table;

public:
    HashTable(int s);
    int hashFunction(int key);
    void insert(int key);
    bool search(int key);
    void display();
};

// Constructor
HashTable::HashTable(int s) {
    size = s;
    table = new int[size];
    for (int i = 0; i < size; i++)
        table[i] = -1;
}

// Hash Function
int HashTable::hashFunction(int key) {
    return key % size;
}

// Insert Operation (Linear Probing)
void HashTable::insert(int key) {
    int index = hashFunction(key);

    while (table[index] != -1) {
        index = (index + 1) % size;
    }

    table[index] = key;
    cout << "Inserted " << key << " at index " << index << endl;
}

// Search Operation (Linear Probing)
bool HashTable::search(int key) {
    int index = hashFunction(key);
    int startIndex = index;

    while (table[index] != -1) {
        if (table[index] == key)
            return true;

        index = (index + 1) % size;

        if (index == startIndex)
            return false;
    }
    return false;
}

// Display Table
void HashTable::display() {
    cout << "\nHash Table:\n";
    for (int i = 0; i < size; i++) {
        if (table[i] != -1)
            cout << i << " --> " << table[i] << endl;
        else
            cout << i << " --> " << "Empty" << endl;
    }
}

int main() {
    int size, n, key;

    cout << "Enter size of hash table: ";
    cin >> size;

    HashTable ht(size);

    cout << "How many keys to insert? ";
    cin >> n;

    cout << "Enter keys:\n";
    for (int i = 0; i < n; i++) {
        cin >> key;
        ht.insert(key);
    }

    ht.display();

    cout << "\nEnter key to search: ";
    cin >> key;

    if (ht.search(key))
        cout << key << " found in the hash table.\n";
    else
        cout << key << " not found in the hash table.\n";

    return 0;
}

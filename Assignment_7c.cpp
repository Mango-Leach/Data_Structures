#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* insertRecursive(Node* node, int data) {
        if (node == nullptr) {
            return new Node(data);
        }

        if (data < node->data) {
            node->left = insertRecursive(node->left, data);
        } else if (data > node->data) {
            node->right = insertRecursive(node->right, data);
        }

        return node;
    }
    
    Node* findMinNode(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        while(node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
    Node* findMaxNode(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        while(node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    void displayInorderRecursive(Node* node) {
        if (node != nullptr) {
            displayInorderRecursive(node->left);
            cout << node->data << " ";
            displayInorderRecursive(node->right);
        }
    }
    
    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    BST() : root(nullptr) {}
    
    ~BST() {
        destroyTree(root);
    }

    void insert(int data) {
        root = insertRecursive(root, data);
    }
    
    void findMin() {
        Node* result = findMinNode(root);
        if (result) {
            cout << "Minimum value in the BST is: " << result->data << endl;
        } else {
            cout << "The tree is empty." << endl;
        }
    }

    void findMax() {
        Node* result = findMaxNode(root);
        if (result) {
            cout << "Maximum value in the BST is: " << result->data << endl;
        } else {
            cout << "The tree is empty." << endl;
        }
    }

    void display() {
        if (root == nullptr) {
            cout << "Tree is empty.";
        } else {
            displayInorderRecursive(root);
        }
        cout << endl;
    }
};

void showMenu() {
    cout << "\n--- BST Operations Menu ---\n";
    cout << "1. Insert a Node\n";
    cout << "2. Display Tree (In-order)\n";
    cout << "3. Find Minimum Value\n";
    cout << "4. Find Maximum Value\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    BST tree;
    int choice, value;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(value);
                cout << value << " has been inserted.\n";
                break;
            case 2:
                cout << "In-order traversal of the tree: ";
                tree.display();
                break;
            case 3:
                tree.findMin();
                break;
            case 4:
                tree.findMax();
                break;
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}

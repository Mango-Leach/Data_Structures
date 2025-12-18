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

    int countNodesRecursive(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + countNodesRecursive(node->left) + countNodesRecursive(node->right);
    }

    int computeHeightRecursive(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + max(computeHeightRecursive(node->left), computeHeightRecursive(node->right));
    }

    void mirrorImageRecursive(Node* node) {
        if (node == nullptr) {
            return;
        }

        mirrorImageRecursive(node->left);
        mirrorImageRecursive(node->right);

        Node* temp = node->left;
        node->left = node->right;
        node->right = temp;
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

    int countTotalNodes() {
        return countNodesRecursive(root);
    }

    int getTreeHeight() {
        return computeHeightRecursive(root);
    }

    void mirror() {
        mirrorImageRecursive(root);
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
    cout << "3. Count Total Number of Nodes\n";
    cout << "4. Compute Height of the Tree\n";
    cout << "5. Create Mirror Image\n";
    cout << "6. Exit\n";
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
                cout << "Total number of nodes: " << tree.countTotalNodes() << endl;
                break;
            case 4:
                cout << "Height of the tree: " << tree.getTreeHeight() << endl;
                break;
            case 5:
                tree.mirror();
                cout << "The tree has been mirrored. Use Display option to see the result.\n";
                break;
            case 6:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice.\n";
                break;
        }
    } while (choice != 6);

    return 0;
}


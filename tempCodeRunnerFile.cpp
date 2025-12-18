#include <iostream>
#include <queue>
#include <stack>
#include <algorithm> 

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    Node* root;

    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    void inorderRecursive(Node* node) {
        if (node == nullptr) {
            return;
        }
        inorderRecursive(node->left);
        cout << node->data << " ";
        inorderRecursive(node->right);
    }

    void preorderRecursive(Node* node) {
        if (node == nullptr) {
            return;
        }
        cout << node->data << " ";
        preorderRecursive(node->left);
        preorderRecursive(node->right);
    }

    int countLeafNodesRecursive(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        if (node->left == nullptr && node->right == nullptr) {
            return 1;
        }
        return countLeafNodesRecursive(node->left) + countLeafNodesRecursive(node->right);
    }

    void mirrorImageRecursive(Node* node) {
        if (node == nullptr) {
            return;
        }
        mirrorImageRecursive(node->left);
        mirrorImageRecursive(node->right);
        swap(node->left, node->right);
    }

public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        destroyTree(root);
    }

    void createTree() {
        if (root != nullptr) {
            cout << "Tree already exists. Cannot create a new one." << endl;
            return;
        }

        int val;
        cout << "Enter root value (-1 for no node): ";
        cin >> val;

        if (val == -1) {
            return;
        }

        root = new Node(val);
        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            cout << "Enter left child for " << current->data << " (-1 for no node): ";
            cin >> val;
            if (val != -1) {
                current->left = new Node(val);
                q.push(current->left);
            }

            cout << "Enter right child for " << current->data << " (-1 for no node): ";
            cin >> val;
            if (val != -1) {
                current->right = new Node(val);
                q.push(current->right);
            }
        }
    }

    void inorderTraversal() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }
        inorderRecursive(root);
        cout << endl;
    }

    void preorderTraversal() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }
        preorderRecursive(root);
        cout << endl;
    }

    void displayLeafNodesCount() {
        int count = countLeafNodesRecursive(root);
        if (root == nullptr) {
             cout << "Tree is empty. Number of leaf nodes: 0" << endl;
        } else {
            cout << "Total number of leaf nodes: " << count << endl;
        }
    }

    void mirrorImage() {
        if (root == nullptr) {
            cout << "Tree is empty. Cannot mirror." << endl;
            return;
        }
        mirrorImageRecursive(root);
        cout << "Tree has been mirrored." << endl;
    }
};

void showMenu() {
    cout << "\n--- Binary Tree Operations Menu ---\n";
    cout << "1. Inorder Traversal (Recursive)\n";
    cout << "2. Preorder Traversal (Recursive)\n";
    cout << "3. Display Number of Leaf Nodes\n";
    cout << "4. Create Mirror Image\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    BinaryTree tree;
    int choice;

    cout << "--- Create the Binary Tree first ---\n";
    tree.createTree();

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Inorder Traversal: ";
                tree.inorderTraversal();
                break;
            case 2:
                cout << "Preorder Traversal: ";
                tree.preorderTraversal();
                break;
            case 3:
                tree.displayLeafNodesCount();
                break;
            case 4:
                tree.mirrorImage();
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

#include <iostream>
#include <queue>
#include <stack>

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

        stack<Node*> s;
        Node* current = root;

        while (current != nullptr || !s.empty()) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }
            current = s.top();
            s.pop();
            cout << current->data << " ";
            current = current->right;
        }
        cout << endl;
    }

    void preorderTraversal() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }

        stack<Node*> s;
        s.push(root);

        while (!s.empty()) {
            Node* current = s.top();
            s.pop();
            cout << current->data << " ";

            if (current->right) {
                s.push(current->right);
            }
            if (current->left) {
                s.push(current->left);
            }
        }
        cout << endl;
    }

    void displayLeafNodesCount() {
        if (root == nullptr) {
            cout << "Tree is empty. Number of leaf nodes: 0" << endl;
            return;
        }

        queue<Node*> q;
        q.push(root);
        int count = 0;

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            if (current->left == nullptr && current->right == nullptr) {
                count++;
            }

            if (current->left) {
                q.push(current->left);
            }
            if (current->right) {
                q.push(current->right);
            }
        }
        cout << "Total number of leaf nodes: " << count << endl;
    }

    void mirrorImage() {
        if (root == nullptr) {
            cout << "Tree is empty. Cannot mirror." << endl;
            return;
        }

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            // Swap the children
            Node* temp = current->left;
            current->left = current->right;
            current->right = temp;

            if (current->left) {
                q.push(current->left);
            }
            if (current->right) {
                q.push(current->right);
            }
        }
        cout << "Tree has been mirrored." << endl;
    }
};

void showMenu() {
    cout << "\n--- Binary Tree Operations Menu ---\n";
    cout << "1. Inorder Traversal (Non-recursive)\n";
    cout << "2. Preorder Traversal (Non-recursive)\n";
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


#include <iostream>

class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void insertAtBeginning(int data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        std::cout << data << " inserted at the beginning.\n";
    }

    void insertAtEnd(int data) {
        Node* newNode = new Node(data);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        std::cout << data << " inserted at the end.\n";
    }

    void insertAtPosition(int data, int pos) {
        if (pos < 1) {
            std::cout << "Invalid position!\n";
            return;
        }
        if (pos == 1) {
            insertAtBeginning(data);
            return;
        }

        Node* current = head;
        for (int i = 1; i < pos - 1 && current != nullptr; ++i) {
            current = current->next;
        }

        if (current == nullptr) {
            std::cout << "Position out of bounds.\n";
            return;
        }

        if (current == tail) {
            insertAtEnd(data);
            return;
        }
        
        Node* newNode = new Node(data);
        newNode->next = current->next;
        newNode->prev = current;
        if (current->next != nullptr) {
            current->next->prev = newNode;
        }
        current->next = newNode;
        std::cout << data << " inserted at position " << pos << ".\n";
    }

    void deleteFromBeginning() {
        if (!head) {
            std::cout << "List is empty. Nothing to delete.\n";
            return;
        }
        Node* temp = head;
        int deletedValue = temp->data;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        std::cout << deletedValue << " deleted from the beginning.\n";
    }

    void deleteFromEnd() {
        if (!tail) {
            std::cout << "List is empty. Nothing to delete.\n";
            return;
        }
        Node* temp = tail;
        int deletedValue = temp->data;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        std::cout << deletedValue << " deleted from the end.\n";
    }

    void deleteByValue(int value) {
        if (!head) {
            std::cout << "List is empty.\n";
            return;
        }

        Node* current = head;
        while (current != nullptr && current->data != value) {
            current = current->next;
        }

        if (current == nullptr) {
            std::cout << "Value " << value << " not found in the list.\n";
            return;
        }

        if (current == head) {
            deleteFromBeginning();
        } else if (current == tail) {
            deleteFromEnd();
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            std::cout << value << " has been deleted from the list.\n";
        }
    }

    void display() const {
        if (!head) {
            std::cout << "List is empty.\n";
            return;
        }
        Node* current = head;
        std::cout << "List (Forward):  NULL <-> ";
        while (current != nullptr) {
            std::cout << current->data << " <-> ";
            current = current->next;
        }
        std::cout << "NULL\n";

        current = tail;
        std::cout << "List (Backward): NULL <-> ";
        while (current != nullptr) {
            std::cout << current->data << " <-> ";
            current = current->prev;
        }
        std::cout << "NULL\n";
    }
};

int main() {
    DoublyLinkedList dll;
    int choice, data, position;

    do {
        std::cout << "\n--- Doubly Linked List Menu ---\n";
        std::cout << "1. Insert at Beginning\n";
        std::cout << "2. Insert at End\n";
        std::cout << "3. Insert at Position\n";
        std::cout << "4. Delete from Beginning\n";
        std::cout << "5. Delete from End\n";
        std::cout << "6. Delete by Value\n";
        std::cout << "7. Display List\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter data to insert: ";
                std::cin >> data;
                dll.insertAtBeginning(data);
                break;
            case 2:
                std::cout << "Enter data to insert: ";
                std::cin >> data;
                dll.insertAtEnd(data);
                break;
            case 3:
                std::cout << "Enter data: ";
                std::cin >> data;
                std::cout << "Enter position: ";
                std::cin >> position;
                dll.insertAtPosition(data, position);
                break;
            case 4:
                dll.deleteFromBeginning();
                break;
            case 5:
                dll.deleteFromEnd();
                break;
            case 6:
                std::cout << "Enter value to delete: ";
                std::cin >> data;
                dll.deleteByValue(data);
                break;
            case 7:
                dll.display();
                break;
            case 0:
                std::cout << "Exiting program. Goodbye! 👋\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
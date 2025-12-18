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

public:
    DoublyLinkedList() : head(nullptr) {}

    ~DoublyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void push(int data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = newNode;
            return;
        }
        Node* last = head;
        while (last->next != nullptr) {
            last = last->next;
        }
        last->next = newNode;
        newNode->prev = last;
    }

    void printList() const {
        if (!head) {
            std::cout << "List is empty." << std::endl;
            return;
        }
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " <-> ";
            current = current->next;
        }
        std::cout << "NULL" << std::endl;
    }

    void bubbleSort() {
        if (!head || !head->next) {
            return;
        }

        bool swapped;
        Node* current;
        Node* lastSorted = nullptr;

        do {
            swapped = false;
            current = head;

            while (current->next != lastSorted) {
                if (current->data > current->next->data) {
                    Node* node1 = current;
                    Node* node2 = current->next;
                    
                    if (node1->prev) {
                        node1->prev->next = node2;
                    } else {
                        head = node2;
                    }
                    
                    if (node2->next) {
                        node2->next->prev = node1;
                    }

                    node2->prev = node1->prev;
                    node1->prev = node2;
                    node1->next = node2->next;
                    node2->next = node1;
                    
                    swapped = true;
                } else {
                    current = current->next;
                }
            }
            lastSorted = current;
        } while (swapped);
    }
};

int main() {
    DoublyLinkedList dll;
    
    dll.push(65);
    dll.push(52);
    dll.push(90);
    dll.push(13);
    dll.push(5);
    dll.push(74);

    std::cout << "Original List:" << std::endl;
    dll.printList();

    std::cout << "\nSorting the list using Bubble Sort..." << std::endl;
    dll.bubbleSort();

    std::cout << "\nSorted List:" << std::endl;
    dll.printList();

    return 0;
}
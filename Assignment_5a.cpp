#include <iostream>

class Node {
public:
    int price;
    Node* next;

    Node(int p) : price(p), next(nullptr) {}
};

class StockTracker {
private:
    Node* top;

public:
    StockTracker() : top(nullptr) {}

    ~StockTracker() {
        while (!isEmpty()) {
            remove();
        }
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void record(int price) {
        Node* newNode = new Node(price);
        newNode->next = top;
        top = newNode;
        std::cout << "Recorded price: " << price << std::endl;
    }

    int remove() {
        if (isEmpty()) {
            std::cout << "No prices to remove. History is empty." << std::endl;
            return -1;
        }
        Node* temp = top;
        int removedPrice = top->price;
        top = top->next;
        delete temp;
        return removedPrice;
    }

    int latest() {
        if (isEmpty()) {
            std::cout << "No prices recorded yet." << std::endl;
            return -1;
        }
        return top->price;
    }

    void displayHistory() {
        if (isEmpty()) {
            std::cout << "Price history is empty." << std::endl;
            return;
        }
        std::cout << "Stock Price History (Most Recent First):" << std::endl;
        Node* current = top;
        while (current != nullptr) {
            std::cout << "-> " << current->price << std::endl;
            current = current->next;
        }
    }
};

void showMenu() {
    std::cout << "\n--- Stock Price Tracker Menu ---" << std::endl;
    std::cout << "1. Record a new price" << std::endl;
    std::cout << "2. Remove the most recent price" << std::endl;
    std::cout << "3. View the latest price" << std::endl;
    std::cout << "4. Display price history" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    StockTracker tracker;
    int choice;
    int price;

    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter the stock price to record: ";
                std::cin >> price;
                tracker.record(price);
                break;
            case 2: {
                int removedPrice = tracker.remove();
                if (removedPrice != -1) {
                    std::cout << "Removed the last recorded price: " << removedPrice << std::endl;
                }
                break;
            }
            case 3: {
                int latestPrice = tracker.latest();
                if (latestPrice != -1) {
                    std::cout << "The latest recorded price is: " << latestPrice << std::endl;
                }
                break;
            }
            case 4:
                tracker.displayHistory();
                break;
            case 5:
                std::cout << "Exiting program. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 5);

    return 0;
}


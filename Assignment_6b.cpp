#include <iostream>
#include <string>
#include <limits>

struct Order {
    int orderId;
    std::string customerName;
};

class PizzaParlorQueue {
private:
    Order* orders;
    int front;
    int rear;
    int capacity;
    int currentSize;
    int nextOrderId;

public:
    PizzaParlorQueue(int n) {
        capacity = n;
        orders = new Order[capacity];
        front = 0;
        rear = -1;
        currentSize = 0;
        nextOrderId = 1;
    }

    ~PizzaParlorQueue() {
        delete[] orders;
    }

    bool isFull() {
        return currentSize == capacity;
    }

    bool isEmpty() {
        return currentSize == 0;
    }

    void placeOrder(const std::string& customerName) {
        if (isFull()) {
            std::cout << "Sorry, we are at maximum capacity and cannot accept new orders." << std::endl;
            return;
        }
        rear = (rear + 1) % capacity;
        orders[rear].orderId = nextOrderId++;
        orders[rear].customerName = customerName;
        currentSize++;
        std::cout << "Order #" << orders[rear].orderId << " for " << customerName << " has been placed." << std::endl;
    }

    void serveOrder() {
        if (isEmpty()) {
            std::cout << "There are no pending orders to serve." << std::endl;
            return;
        }
        Order servedOrder = orders[front];
        front = (front + 1) % capacity;
        currentSize--;
        std::cout << "Serving Order #" << servedOrder.orderId << " for customer " << servedOrder.customerName << "." << std::endl;
    }

    void displayOrders() {
        if (isEmpty()) {
            std::cout << "The order queue is empty." << std::endl;
            return;
        }
        std::cout << "\n--- Pending Pizza Orders ---" << std::endl;
        int count = 0;
        int i = front;
        while (count < currentSize) {
            std::cout << (count + 1) << ". Order #" << orders[i].orderId << " - " << orders[i].customerName << std::endl;
            i = (i + 1) % capacity;
            count++;
        }
        std::cout << "--------------------------" << std::endl;
    }
};

void showMenu() {
    std::cout << "\n--- Pizza Parlor Menu ---" << std::endl;
    std::cout << "1. Place a new order" << std::endl;
    std::cout << "2. Serve an order" << std::endl;
    std::cout << "3. Display all pending orders" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    int capacity;
    std::cout << "Enter the maximum number of orders the pizza parlor can handle: ";
    std::cin >> capacity;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    if (capacity <= 0) {
        std::cout << "Capacity must be a positive number. Exiting." << std::endl;
        return 1;
    }

    PizzaParlorQueue parlor(capacity);
    int choice;
    std::string name;

    do {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        switch (choice) {
            case 1:
                std::cout << "Enter customer name: ";
                std::getline(std::cin, name);
                parlor.placeOrder(name);
                break;
            case 2:
                parlor.serveOrder();
                break;
            case 3:
                parlor.displayOrders();
                break;
            case 4:
                std::cout << "Closing the pizza parlor. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 4);

    return 0;
}

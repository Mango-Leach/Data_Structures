#include <iostream>
#include <string>
#include <limits>

struct Passenger {
    std::string name;
    int ticketId;
};

struct Node {
    Passenger passenger;
    Node* next;
};

class TicketQueue {
private:
    Node *front, *rear;
    int nextTicketId;
    int currentSize;

public:
    TicketQueue() {
        front = rear = nullptr;
        nextTicketId = 101;
        currentSize = 0;
    }

    ~TicketQueue() {
        Node* temp = front;
        while (temp != nullptr) {
            front = front->next;
            delete temp;
            temp = front;
        }
    }

    bool isEmpty() {
        return front == nullptr;
    }
    
    int getSize() {
        return currentSize;
    }

    void insertPassenger(const std::string& name) {
        Node* temp = new Node;
        temp->passenger.name = name;
        temp->passenger.ticketId = nextTicketId++;
        temp->next = nullptr;
        currentSize++;

        if (isEmpty()) {
            front = rear = temp;
        } else {
            rear->next = temp;
            rear = temp;
        }

        std::cout << "Passenger '" << name << "' (Ticket ID: " << temp->passenger.ticketId << ") has been added to the queue." << std::endl;
    }

    void removePassenger() {
        if (isEmpty()) {
            std::cout << "The queue is empty. No passengers to remove." << std::endl;
            return;
        }

        Node* temp = front;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }
        
        currentSize--;
        std::cout << "Passenger '" << temp->passenger.name << "' (Ticket ID: " << temp->passenger.ticketId << ") has been served and removed from the queue." << std::endl;
        delete temp;
    }
    
    void displayFrontPassenger() {
        if (isEmpty()) {
            std::cout << "The queue is empty. No passengers are waiting." << std::endl;
            return;
        }
        std::cout << "The passenger at the front of the queue is '" << front->passenger.name << "' (Ticket ID: " << front->passenger.ticketId << ")." << std::endl;
    }
};

void showMenu() {
    std::cout << "\n--- Ticket Agent Queue System ---" << std::endl;
    std::cout << "1. Insert a new passenger" << std::endl;
    std::cout << "2. Remove passenger from the front" << std::endl;
    std::cout << "3. Display passenger at the front" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    TicketQueue queue;
    int choice;
    std::string name;

    do {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                std::cout << "Enter passenger's name: ";
                std::getline(std::cin, name);
                queue.insertPassenger(name);
                break;
            case 2:
                queue.removePassenger();
                break;
            case 3:
                queue.displayFrontPassenger();
                break;
            case 4:
                std::cout << "\nProgram terminating." << std::endl;
                std::cout << "Number of passengers left in the queue: " << queue.getSize() << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 4);

    return 0;
}

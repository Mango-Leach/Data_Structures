#include <iostream>
#include <string>
#include <limits>

struct Call {
    std::string callerName;
    int callId;
};

struct Node {
    Call call;
    Node* next;
};

class CallQueue {
private:
    Node *front, *rear;
    int nextCallId;

public:
    CallQueue() {
        front = rear = nullptr;
        nextCallId = 1;
    }

    ~CallQueue() {
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
    
    void enqueue(const std::string& name) {
        Node* temp = new Node;
        temp->call.callerName = name;
        temp->call.callId = nextCallId++;
        temp->next = nullptr;

        if (isEmpty()) {
            front = rear = temp;
        } else {
            rear->next = temp;
            rear = temp;
        }

        std::cout << "Call received from '" << name << "' (Call ID: " << temp->call.callId << "). Added to the queue." << std::endl;
    }

    void dequeue() {
        if (isEmpty()) {
            std::cout << "The queue is empty. No calls to answer." << std::endl;
            return;
        }

        Node* temp = front;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }
        
        std::cout << "Agent is now assisting '" << temp->call.callerName << "' (Call ID: " << temp->call.callId << ")." << std::endl;
        delete temp;
    }
    
    void displayFront() {
        if (isEmpty()) {
            std::cout << "The queue is empty. No calls are waiting." << std::endl;
            return;
        }
        std::cout << "Next call to be answered is from '" << front->call.callerName << "' (Call ID: " << front->call.callId << ")." << std::endl;
    }
};

void showMenu() {
    std::cout << "\n--- Call Center System ---" << std::endl;
    std::cout << "1. Add a new incoming call" << std::endl;
    std::cout << "2. Agent takes next call" << std::endl;
    std::cout << "3. Display next waiting call" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    CallQueue callQueue;
    int choice;
    std::string name;

    do {
        showMenu();
        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            showMenu();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                std::cout << "Enter caller's name: ";
                std::getline(std::cin, name);
                callQueue.enqueue(name);
                break;
            case 2:
                callQueue.dequeue();
                break;
            case 3:
                callQueue.displayFront();
                break;
            case 4:
                std::cout << "Shutting down the call center system." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 4);

    return 0;
}


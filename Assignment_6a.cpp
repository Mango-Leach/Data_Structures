#include <iostream>
#include <string>
#include <limits>  // Required for std::numeric_limits

struct Patient {
    std::string name;
    int patientId;
};

struct Node {
    Patient patient;
    Node* next;
};

class ClinicQueue {
private:
    Node *front, *rear;
    int nextPatientId;

public:
    ClinicQueue() {
        front = rear = nullptr;
        nextPatientId = 1;
    }

    ~ClinicQueue() {
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

    void checkIn(const std::string& name) {
        Node* temp = new Node;
        temp->patient.name = name;
        temp->patient.patientId = nextPatientId++;
        temp->next = nullptr;

        if (isEmpty()) {
            front = rear = temp;
        } else {
            rear->next = temp;
            rear = temp;
        }

        std::cout << "Patient '" << name << "' (ID: " << temp->patient.patientId << ") has checked in." << std::endl;
    }

    void assignToDoctor() {
        if (isEmpty()) {
            std::cout << "No patients are waiting." << std::endl;
            return;
        }

        Node* temp = front;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        std::cout << "Assigning Patient '" << temp->patient.name << "' (ID: " << temp->patient.patientId << ") to a doctor." << std::endl;
        delete temp;
    }

    void viewNextPatient() {
        if (isEmpty()) {
            std::cout << "No patients are waiting." << std::endl;
            return;
        }
        std::cout << "Next patient to be seen is '" << front->patient.name << "' (ID: " << front->patient.patientId << ")." << std::endl;
    }

    void displayWaitingList() {
        if (isEmpty()) {
            std::cout << "The waiting list is empty." << std::endl;
            return;
        }

        std::cout << "\n--- Current Waiting List ---" << std::endl;
        Node* temp = front;
        int position = 1;
        while (temp != nullptr) {
            std::cout << position++ << ". " << temp->patient.name << " (ID: " << temp->patient.patientId << ")" << std::endl;
            temp = temp->next;
        }
        std::cout << "--------------------------" << std::endl;
    }
};

void showMenu() {
    std::cout << "\n--- Clinic Patient Management ---" << std::endl;
    std::cout << "1. Check-in a new patient" << std::endl;
    std::cout << "2. Assign patient to doctor" << std::endl;
    std::cout << "3. View next patient" << std::endl;
    std::cout << "4. Display waiting list" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    ClinicQueue clinic;
    int choice;
    std::string name;

    do {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                std::cout << "Enter patient's name: ";
                std::getline(std::cin, name);
                clinic.checkIn(name);
                break;
            case 2:
                clinic.assignToDoctor();
                break;
            case 3:
                clinic.viewNextPatient();
                break;
            case 4:
                clinic.displayWaitingList();
                break;
            case 5:
                std::cout << "Exiting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 5);

    return 0;
}


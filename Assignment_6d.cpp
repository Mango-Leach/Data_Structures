#include <iostream>

class MultiQueue {
private:
    int* arr;
    int size;
    int front1, rear1;
    int front2, rear2;

public:
    MultiQueue(int n) {
        size = n;
        arr = new int[size];
        
        front1 = -1;
        rear1 = -1;

        front2 = size;
        rear2 = size;
    }

    ~MultiQueue() {
        delete[] arr;
    }

    void addQueue(int queueNum, int value) {
        if (rear1 + 1 == rear2) {
            std::cout << "Error: Queue is full. Cannot add element." << std::endl;
            return;
        }

        if (queueNum == 1) {
            if (front1 == -1) {
                front1 = 0;
            }
            rear1++;
            arr[rear1] = value;
            std::cout << value << " added to Queue 1." << std::endl;
        } else if (queueNum == 2) {
            if (front2 == size) {
                front2 = size - 1;
            }
            rear2--;
            arr[rear2] = value;
            std::cout << value << " added to Queue 2." << std::endl;
        } else {
            std::cout << "Invalid queue number." << std::endl;
        }
    }

    void deleteFromQueue(int queueNum) {
        if (queueNum == 1) {
            if (front1 == -1 || front1 > rear1) {
                std::cout << "Queue 1 is empty. Cannot delete." << std::endl;
                return;
            }
            int deletedValue = arr[front1];
            front1++;
            std::cout << deletedValue << " deleted from Queue 1." << std::endl;
            
            if (front1 > rear1) {
                front1 = rear1 = -1;
            }
        } else if (queueNum == 2) {
            if (front2 == size || front2 < rear2) {
                std::cout << "Queue 2 is empty. Cannot delete." << std::endl;
                return;
            }
            int deletedValue = arr[front2];
            front2--;
            std::cout << deletedValue << " deleted from Queue 2." << std::endl;

            if (front2 < rear2) {
                front2 = rear2 = size;
            }
        } else {
            std::cout << "Invalid queue number." << std::endl;
        }
    }

    void displayQueue(int queueNum) {
        if (queueNum == 1) {
            if (front1 == -1 || front1 > rear1) {
                std::cout << "Queue 1 is empty." << std::endl;
                return;
            }
            std::cout << "Elements in Queue 1: ";
            for (int i = front1; i <= rear1; i++) {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        } else if (queueNum == 2) {
            if (front2 == size || front2 < rear2) {
                std::cout << "Queue 2 is empty." << std::endl;
                return;
            }
            std::cout << "Elements in Queue 2: ";
            for (int i = front2; i >= rear2; i--) {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "Invalid queue number." << std::endl;
        }
    }
};

void showMenu() {
    std::cout << "\n--- Multi-Queue Operations ---" << std::endl;
    std::cout << "1. Add to Queue" << std::endl;
    std::cout << "2. Delete from Queue" << std::endl;
    std::cout << "3. Display Queue" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    int size;
    std::cout << "Enter the total size of the array for the queues: ";
    std::cin >> size;

    if (size < 2) {
        std::cout << "Size must be at least 2 to support two queues. Exiting." << std::endl;
        return 1;
    }

    MultiQueue mq(size);
    int choice, queueNum, value;

    do {
        showMenu();
        std::cin >> choice;

        if (choice >= 1 && choice <= 3) {
            std::cout << "Enter queue number (1 or 2): ";
            std::cin >> queueNum;
            if (queueNum != 1 && queueNum != 2) {
                std::cout << "Invalid queue number. Please try again." << std::endl;
                continue;
            }
        }

        switch (choice) {
            case 1:
                std::cout << "Enter value to add: ";
                std::cin >> value;
                mq.addQueue(queueNum, value);
                break;
            case 2:
                mq.deleteFromQueue(queueNum);
                break;
            case 3:
                mq.displayQueue(queueNum);
                break;
            case 4:
                std::cout << "Exiting program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 4);

    return 0;
}


#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

const int NUM_ROWS = 8;
const int NUM_SEATS_PER_ROW = 8;

class Seat {
public:
    int seat_number;
    char status;
    Seat* next;
    Seat* prev;

    Seat(int num) : seat_number(num), status('A'), next(nullptr), prev(nullptr) {}
};

class Theater {
private:
    Seat* rows[NUM_ROWS];

public:
    Theater() {
        srand(time(0));

        for (int i = 0; i < NUM_ROWS; ++i) {
            rows[i] = new Seat(1);
            Seat* head = rows[i];
            Seat* current = head;

            if (rand() % 3 == 0) {
                head->status = 'B';
            }

            for (int j = 2; j <= NUM_SEATS_PER_ROW; ++j) {
                Seat* newSeat = new Seat(j);
                if (rand() % 3 == 0) {
                    newSeat->status = 'B';
                }
                current->next = newSeat;
                newSeat->prev = current;
                current = newSeat;
            }

            current->next = head;
            head->prev = current;
        }
    }

    ~Theater() {
        for (int i = 0; i < NUM_ROWS; ++i) {
            Seat* head = rows[i];
            if (!head) continue;

            Seat* current = head;
            do {
                Seat* temp = current;
                current = current->next;
                delete temp;
            } while (current != head);
        }
    }

    void displaySeats() {
        std::cout << "\n==================== SCREEN THIS WAY ====================\n";
        for (int i = 0; i < NUM_ROWS; ++i) {
            std::cout << "Row " << (i + 1) << ":  ";
            Seat* head = rows[i];
            Seat* current = head;
            do {
                std::cout << "[S" << std::setw(2) << current->seat_number << ":" << current->status << "] ";
                current = current->next;
            } while (current != head);
            std::cout << std::endl;
        }
        std::cout << "=========================================================\n";
        std::cout << "Legend: [S#: A] = Available, [S#: B] = Booked\n";
    }

    void bookSeats() {
        int row, num_seats;
        std::cout << "Enter Row number (1-" << NUM_ROWS << "): ";
        std::cin >> row;
        if (row < 1 || row > NUM_ROWS) {
            std::cout << "Invalid row number.\n";
            return;
        }

        std::cout << "How many seats to book? ";
        std::cin >> num_seats;
        if (num_seats <= 0) {
            std::cout << "Invalid number of seats.\n";
            return;
        }

        std::vector<int> seats_to_book(num_seats);
        std::cout << "Enter seat numbers separated by spaces: ";
        for (int i = 0; i < num_seats; ++i) {
            std::cin >> seats_to_book[i];
        }

        Seat* head = rows[row - 1];
        bool all_available = true;

        for (int seat_num : seats_to_book) {
            Seat* current = head;
            bool found = false;
            do {
                if (current->seat_number == seat_num) {
                    found = true;
                    if (current->status == 'B') {
                        std::cout << "Error: Seat " << seat_num << " in Row " << row << " is already booked.\n";
                        all_available = false;
                    }
                    break;
                }
                current = current->next;
            } while (current != head);
            if (!found) {
                std::cout << "Error: Seat " << seat_num << " does not exist in Row " << row << ".\n";
                all_available = false;
            }
        }
        
        if (all_available) {
            for (int seat_num : seats_to_book) {
                Seat* current = head;
                do {
                    if (current->seat_number == seat_num) {
                        current->status = 'B';
                        break;
                    }
                    current = current->next;
                } while (current != head);
            }
            std::cout << "Booking successful for all requested seats in Row " << row << "!\n";
        } else {
            std::cout << "Booking failed. Please try again with different seats.\n";
        }
    }
    
    void cancelBooking() {
        int row, seat_num;
        std::cout << "Enter Row number for cancellation (1-" << NUM_ROWS << "): ";
        std::cin >> row;
        std::cout << "Enter Seat number for cancellation: ";
        std::cin >> seat_num;

        if (row < 1 || row > NUM_ROWS) {
            std::cout << "Invalid row number.\n";
            return;
        }
        
        Seat* head = rows[row - 1];
        Seat* current = head;
        bool found = false;
        
        do {
            if (current->seat_number == seat_num) {
                found = true;
                if (current->status == 'B') {
                    current->status = 'A';
                    std::cout << "Cancellation successful for Seat " << seat_num << " in Row " << row << ".\n";
                } else {
                    std::cout << "Seat " << seat_num << " in Row " << row << " was not booked.\n";
                }
                break;
            }
            current = current->next;
        } while (current != head);

        if (!found) {
            std::cout << "Invalid seat number for Row " << row << ".\n";
        }
    }
};

int main() {
    Theater multiplex;
    int choice;

    do {
        std::cout << "\n--- Galaxy Multiplex Ticket System ---\n";
        std::cout << "1. Display Seat Availability\n";
        std::cout << "2. Book Seats\n";
        std::cout << "3. Cancel Booking\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                multiplex.displaySeats();
                break;
            case 2:
                multiplex.bookSeats();
                break;
            case 3:
                multiplex.cancelBooking();
                break;
            case 0:
                std::cout << "Thank you for using the system. Goodbye! 👋\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
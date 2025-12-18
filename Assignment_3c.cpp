#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

const int DAY_START_TIME = 540;
const int DAY_END_TIME = 1020;
const int MIN_DURATION = 15;
const int MAX_DURATION = 60;

class Slot {
public:
    int start_time;
    int end_time;
    bool is_booked;
    Slot* next;
    Slot* prev;

    Slot(int start, int end, bool booked = false)
        : start_time(start), end_time(end), is_booked(booked), next(nullptr), prev(nullptr) {}
};

class Scheduler {
private:
    Slot* head;

    std::string minutesToString(int minutes) const {
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << minutes / 60 << ":"
            << std::setw(2) << std::setfill('0') << minutes % 60;
        return oss.str();
    }

    int stringToMinutes(const std::string& time_str) const {
        int hours, minutes;
        if (sscanf(time_str.c_str(), "%d:%d", &hours, &minutes) == 2) {
            return hours * 60 + minutes;
        }
        return -1;
    }

public:
    Scheduler() {
        head = new Slot(DAY_START_TIME, DAY_END_TIME, false);
    }

    ~Scheduler() {
        Slot* current = head;
        while (current != nullptr) {
            Slot* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void displayAllSlots() const {
        if (!head) {
            std::cout << "Schedule is empty.\n";
            return;
        }
        std::cout << "\n--- Full Day Schedule ---\n";
        Slot* temp = head;
        while (temp != nullptr) {
            std::cout << "Time: " << minutesToString(temp->start_time)
                      << " - " << minutesToString(temp->end_time)
                      << " | Status: " << (temp->is_booked ? "Booked" : "Free") << std::endl;
            temp = temp->next;
        }
        std::cout << "-------------------------\n";
    }

    void displayFreeSlots() const {
        if (!head) {
            std::cout << "Schedule is empty.\n";
            return;
        }
        std::cout << "\n--- Available Time Slots ---\n";
        Slot* temp = head;
        bool found = false;
        while (temp != nullptr) {
            if (!temp->is_booked) {
                std::cout << "Free from " << minutesToString(temp->start_time)
                          << " to " << minutesToString(temp->end_time) << " ("
                          << (temp->end_time - temp->start_time) << " mins)\n";
                found = true;
            }
            temp = temp->next;
        }
        if (!found) {
            std::cout << "No available slots found.\n";
        }
        std::cout << "---------------------------\n";
    }

    void bookAppointment() {
        std::string start_str, end_str;
        std::cout << "Enter start time (HH:MM): ";
        std::cin >> start_str;
        std::cout << "Enter end time (HH:MM): ";
        std::cin >> end_str;

        int start = stringToMinutes(start_str);
        int end = stringToMinutes(end_str);
        int duration = end - start;

        if (start < DAY_START_TIME || end > DAY_END_TIME || start >= end) {
            std::cout << "Error: Time is outside of working hours (09:00 - 17:00).\n";
            return;
        }
        if (duration < MIN_DURATION || duration > MAX_DURATION) {
            std::cout << "Error: Duration must be between " << MIN_DURATION << " and " << MAX_DURATION << " minutes.\n";
            return;
        }

        Slot* current = head;
        while (current != nullptr) {
            if (!current->is_booked && start >= current->start_time && end <= current->end_time) {
                int original_end_time = current->end_time;

                if (start == current->start_time && end == original_end_time) {
                    current->is_booked = true;
                }
                else if (start == current->start_time) {
                    current->end_time = end;
                    current->is_booked = true;
                    Slot* newFreeSlot = new Slot(end, original_end_time, false);
                    newFreeSlot->next = current->next;
                    if (current->next) {
                        current->next->prev = newFreeSlot;
                    }
                    current->next = newFreeSlot;
                    newFreeSlot->prev = current;
                }
                else if (end == original_end_time) {
                    current->end_time = start;
                    Slot* newBookedSlot = new Slot(start, end, true);
                    newBookedSlot->next = current->next;
                    if (current->next) {
                        current->next->prev = newBookedSlot;
                    }
                    current->next = newBookedSlot;
                    newBookedSlot->prev = current;
                }
                else {
                    current->end_time = start;
                    Slot* newBookedSlot = new Slot(start, end, true);
                    Slot* newFreeSlot = new Slot(end, original_end_time, false);
                    
                    newFreeSlot->next = current->next;
                    if (current->next) {
                        current->next->prev = newFreeSlot;
                    }
                    newBookedSlot->next = newFreeSlot;
                    newFreeSlot->prev = newBookedSlot;
                    current->next = newBookedSlot;
                    newBookedSlot->prev = current;
                }

                std::cout << "Appointment from " << start_str << " to " << end_str << " booked successfully!\n";
                return;
            }
            current = current->next;
        }
        std::cout << "Booking failed. The requested time slot is not available or invalid.\n";
    }

    void cancelAppointment() {
        std::string start_str;
        std::cout << "Enter the start time of the appointment to cancel (HH:MM): ";
        std::cin >> start_str;
        int start = stringToMinutes(start_str);

        Slot* current = head;
        while (current != nullptr) {
            if (current->is_booked && current->start_time == start) {
                current->is_booked = false;
                std::cout << "Appointment at " << start_str << " cancelled.\n";

                if (current->next && !current->next->is_booked) {
                    Slot* to_merge = current->next;
                    current->end_time = to_merge->end_time;
                    current->next = to_merge->next;
                    if (to_merge->next) to_merge->next->prev = current;
                    delete to_merge;
                }

                if (current->prev && !current->prev->is_booked) {
                    Slot* to_merge_with = current->prev;
                    to_merge_with->end_time = current->end_time;
                    to_merge_with->next = current->next;
                    if (current->next) current->next->prev = to_merge_with;
                    if (current == head) head = to_merge_with;
                    delete current;
                }
                return;
            }
            current = current->next;
        }
        std::cout << "No booked appointment found at the specified time.\n";
    }

    void sortData() {
        if (!head || !head->next) return;
        bool swapped;
        do {
            swapped = false;
            Slot* current = head;
            while (current->next != nullptr) {
                if (current->start_time > current->next->start_time) {
                    std::swap(current->start_time, current->next->start_time);
                    std::swap(current->end_time, current->next->end_time);
                    std::swap(current->is_booked, current->next->is_booked);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
        std::cout << "Schedule sorted by time (data swap).\n";
    }

    void sortPointers() {
        if (!head || !head->next) return;
        bool swapped;
        do {
            swapped = false;
            Slot* current = head;
            while (current->next != nullptr) {
                if (current->start_time > current->next->start_time) {
                    Slot* node1 = current;
                    Slot* node2 = current->next;
                    
                    if (node1->prev) node1->prev->next = node2;
                    else head = node2;
                    
                    if (node2->next) node2->next->prev = node1;
                    
                    node2->prev = node1->prev;
                    node1->prev = node2;
                    node1->next = node2->next;
                    node2->next = node1;
                    
                    swapped = true;
                } else {
                    current = current->next;
                }
            }
        } while (swapped);
        std::cout << "Schedule sorted by time (pointer manipulation).\n";
    }
};

int main() {
    Scheduler schedule;
    int choice;

    do {
        std::cout << "\n--- Appointment Scheduler Menu ---\n";
        std::cout << "1. Display Free Slots\n";
        std::cout << "2. Book an Appointment\n";
        std::cout << "3. Cancel an Appointment\n";
        std::cout << "4. Sort Appointments (by swapping data)\n";
        std::cout << "5. Sort Appointments (by manipulating pointers)\n";
        std::cout << "6. Display Full Schedule\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: schedule.displayFreeSlots(); break;
            case 2: schedule.bookAppointment(); break;
            case 3: schedule.cancelAppointment(); break;
            case 4: schedule.sortData(); break;
            case 5: schedule.sortPointers(); break;
            case 6: schedule.displayAllSlots(); break;
            case 0: std::cout << "Exiting program. Goodbye! \n"; break;
            default: std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
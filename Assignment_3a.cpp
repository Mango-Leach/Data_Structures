#include <iostream>
#include <string>
#include <limits>

class Member {
public:
    int prn;
    std::string name;
    Member* next;

    Member(int p, const std::string& n) : prn(p), name(n), next(nullptr) {}
};

class VertexClub {
private:
    Member* head;

public:
    VertexClub() : head(nullptr) {}

    ~VertexClub() {
        Member* current = head;
        while (current != nullptr) {
            Member* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void addMember() {
        int prn;
        std::string name;
        std::cout << "Enter PRN: ";
        std::cin >> prn;
        std::cout << "Enter Name: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, name);
        
        Member* newMember = new Member(prn, name);

        if (!head) {
            head = newMember;
        } else {
            Member* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newMember;
        }
        std::cout << "Member added successfully!\n";
    }

    void deleteMemberByPRN(int prn) {
        if (!head) {
            std::cout << "Club is empty. Nothing to delete.\n";
            return;
        }

        if (head->prn == prn) {
            Member* temp = head;
            head = head->next;
            delete temp;
            std::cout << "President with PRN " << prn << " deleted.\n";
            return;
        }

        Member* current = head->next;
        Member* prev = head;
        while (current != nullptr) {
            if (current->prn == prn) {
                prev->next = current->next;
                delete current;
                std::cout << "Member with PRN " << prn << " deleted.\n";
                return;
            }
            prev = current;
            current = current->next;
        }
        std::cout << "Member with PRN " << prn << " not found.\n";
    }

    int countMembers() {
        int count = 0;
        Member* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void displayMembers() {
        if (!head) {
            std::cout << "The club has no members.\n";
            return;
        }

        Member* temp = head;
        std::cout << "\n--- Vertex Club Members ---\n";
        while (temp != nullptr) {
            std::cout << "PRN: " << temp->prn << ", Name: " << temp->name;
            if (temp == head) {
                std::cout << " (President)";
            }
            if (temp->next == nullptr && temp != head) {
                std::cout << " (Secretary)";
            }
            std::cout << std::endl;
            temp = temp->next;
        }
        std::cout << "-------------------------\n";
    }

    void concatenate(VertexClub& otherList) {
        if (!otherList.head) {
            std::cout << "The other list is empty, nothing to concatenate.\n";
            return;
        }
        if (!this->head) {
            this->head = otherList.head;
        } else {
            Member* temp = this->head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = otherList.head;
        }
        otherList.head = nullptr;
        std::cout << "Lists concatenated successfully.\n";
    }

    void reverse() {
        if (!head || !head->next) {
            return;
        }
        Member* prev = nullptr;
        Member* current = head;
        Member* nextNode = nullptr;
        while (current != nullptr) {
            nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }
        head = prev;
        std::cout << "List reversed successfully.\n";
    }

    void searchByPRN(int prn) {
        if (!head) {
            std::cout << "Club is empty.\n";
            return;
        }
        Member* temp = head;
        while (temp != nullptr) {
            if (temp->prn == prn) {
                std::cout << "Member Found -> PRN: " << temp->prn << ", Name: " << temp->name << std::endl;
                return;
            }
            temp = temp->next;
        }
        std::cout << "Member with PRN " << prn << " not found.\n";
    }

    void sortByPRN() {
        if (!head || !head->next) {
            return;
        }
        
        bool swapped;
        Member* ptr1;
        Member* lptr = nullptr;

        do {
            swapped = false;
            ptr1 = head;

            while (ptr1->next != lptr) {
                if (ptr1->prn > ptr1->next->prn) {
                    std::swap(ptr1->prn, ptr1->next->prn);
                    std::swap(ptr1->name, ptr1->next->name);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);

        std::cout << "List sorted successfully by PRN.\n";
    }
};

void manageClub(VertexClub& club, const std::string& divisionName) {
    int choice, prn;
    do {
        std::cout << "\n--- Managing Division " << divisionName << " ---\n";
        std::cout << "1. Add Member\n";
        std::cout << "2. Delete Member by PRN\n";
        std::cout << "3. Display Members\n";
        std::cout << "4. Count Members\n";
        std::cout << "5. Search by PRN\n";
        std::cout << "6. Sort by PRN\n";
        std::cout << "7. Reverse List\n";
        std::cout << "8. Return to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: club.addMember(); break;
            case 2:
                std::cout << "Enter PRN to delete: ";
                std::cin >> prn;
                club.deleteMemberByPRN(prn);
                break;
            case 3: club.displayMembers(); break;
            case 4:
                std::cout << "Total members: " << club.countMembers() << std::endl;
                break;
            case 5:
                std::cout << "Enter PRN to search: ";
                std::cin >> prn;
                club.searchByPRN(prn);
                break;
            case 6: club.sortByPRN(); break;
            case 7: club.reverse(); break;
            case 8: std::cout << "Returning to Main Menu...\n"; break;
            default: std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);
}

int main() {
    VertexClub divisionA, divisionB;
    int choice;

    do {
        std::cout << "\n========= Main Menu =========\n";
        std::cout << "1. Manage Division A Club\n";
        std::cout << "2. Manage Division B Club\n";
        std::cout << "3. Concatenate Division B list to Division A list\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                manageClub(divisionA, "A");
                break;
            case 2:
                manageClub(divisionB, "B");
                break;
            case 3:
                std::cout << "Concatenating B into A...\n";
                divisionA.concatenate(divisionB);
                std::cout << "Division A now contains all members.\n";
                divisionA.displayMembers();
                break;
            case 4:
                std::cout << "Exiting program. Goodbye! 👋\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}



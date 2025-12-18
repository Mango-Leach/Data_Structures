#include <iostream>
#include <string>
#include <algorithm>

class BitNode {
public:
    int bit;
    BitNode* next;
    BitNode* prev;

    BitNode(int b) : bit(b), next(nullptr), prev(nullptr) {}
};

class BinaryNumber {
private:
    BitNode* head;
    BitNode* tail;

    void prependBit(int bit) {
        BitNode* newNode = new BitNode(bit);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

public:
    BinaryNumber() : head(nullptr), tail(nullptr) {}

    ~BinaryNumber() {
        BitNode* current = head;
        while (current != nullptr) {
            BitNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    BinaryNumber(const BinaryNumber& other) : head(nullptr), tail(nullptr) {
        BitNode* temp = other.head;
        while (temp != nullptr) {
            int bit = temp->bit;
            BitNode* newNode = new BitNode(bit);
            if (!head) {
                head = tail = newNode;
            } else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
            temp = temp->next;
        }
    }

    BinaryNumber& operator=(const BinaryNumber& other) {
        if (this == &other) {
            return *this;
        }

        BitNode* current = head;
        while (current != nullptr) {
            BitNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;

        BitNode* temp = other.head;
        while (temp != nullptr) {
            int bit = temp->bit;
            BitNode* newNode = new BitNode(bit);
            if (!head) {
                head = tail = newNode;
            } else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
            temp = temp->next;
        }
        return *this;
    }

    void create(const std::string& binStr) {
        if (!binStr.empty()) {
            for (char bitChar : binStr) {
                if (bitChar == '0' || bitChar == '1') {
                    int bit = bitChar - '0';
                    BitNode* newNode = new BitNode(bit);
                    if (!head) {
                        head = tail = newNode;
                    } else {
                        tail->next = newNode;
                        newNode->prev = tail;
                        tail = newNode;
                    }
                }
            }
        }
    }

    void display() const {
        if (!head) {
            std::cout << " (empty)";
            return;
        }
        BitNode* temp = head;
        while (temp != nullptr) {
            std::cout << temp->bit;
            temp = temp->next;
        }
    }

    BinaryNumber onesComplement() const {
        BinaryNumber result;
        BitNode* temp = head;
        while (temp != nullptr) {
            std::string bit_str = std::to_string(1 - temp->bit);
            result.create(bit_str);
            temp = temp->next;
        }
        return result;
    }

    BinaryNumber twosComplement() const {
        BinaryNumber onesComp = this->onesComplement();
        if (!onesComp.head) {
            return onesComp;
        }

        int carry = 1;
        BitNode* temp = onesComp.tail;
        while (temp != nullptr && carry > 0) {
            int sum = temp->bit + carry;
            temp->bit = sum % 2;
            carry = sum / 2;
            temp = temp->prev;
        }

        if (carry > 0) {
            onesComp.prependBit(carry);
        }

        return onesComp;
    }

    BinaryNumber add(const BinaryNumber& other) const {
        BinaryNumber result;
        BitNode* p1 = this->tail;
        BitNode* p2 = other.tail;
        int carry = 0;

        while (p1 != nullptr || p2 != nullptr || carry != 0) {
            int bit1 = (p1) ? p1->bit : 0;
            int bit2 = (p2) ? p2->bit : 0;

            int sum = bit1 + bit2 + carry;
            int resultBit = sum % 2;
            carry = sum / 2;

            result.prependBit(resultBit);

            if (p1) p1 = p1->prev;
            if (p2) p2 = p2->prev;
        }
        return result;
    }
};

int main() {
    BinaryNumber num1, num2;
    int choice;
    std::string binStr1, binStr2;

    std::cout << "Enter the first binary number: ";
    std::cin >> binStr1;
    num1.create(binStr1);

    std::cout << "Enter the second binary number: ";
    std::cin >> binStr2;
    num2.create(binStr2);

    do {
        std::cout << "\n--- Binary Number Operations Menu ---\n";
        std::cout << "Current Numbers -> 1: "; num1.display(); std::cout << " | 2: "; num2.display(); std::cout << "\n";
        std::cout << "1. Calculate 1's and 2's Complement\n";
        std::cout << "2. Add the two binary numbers\n";
        std::cout << "3. Enter new numbers\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int numChoice;
                std::cout << "Calculate complement for which number (1 or 2)? ";
                std::cin >> numChoice;
                BinaryNumber selectedNum = (numChoice == 1) ? num1 : num2;

                std::cout << "Original Number: "; selectedNum.display(); std::cout << "\n";

                BinaryNumber ones = selectedNum.onesComplement();
                std::cout << "1's Complement:  "; ones.display(); std::cout << "\n";

                BinaryNumber twos = selectedNum.twosComplement();
                std::cout << "2's Complement:  "; twos.display(); std::cout << "\n";
                break;
            }
            case 2: {
                std::cout << "  "; num1.display(); std::cout << "\n";
                std::cout << "+ "; num2.display(); std::cout << "\n";
                std::cout << "--------------------\n";
                BinaryNumber sum = num1.add(num2);
                std::cout << "= "; sum.display(); std::cout << "\n";
                break;
            }
            case 3:
                std::cout << "Enter the first binary number: ";
                std::cin >> binStr1;
                num1 = BinaryNumber(); 
                num1.create(binStr1);

                std::cout << "Enter the second binary number: ";
                std::cin >> binStr2;
                num2 = BinaryNumber();
                num2.create(binStr2);
                break;
            case 0:
                std::cout << "Exiting program. Goodbye! \n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
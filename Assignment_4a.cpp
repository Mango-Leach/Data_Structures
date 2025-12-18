#include <iostream>

class Term {
public:
    int coefficient;
    int exponent;
    Term* next;

    Term(int coeff, int exp) : coefficient(coeff), exponent(exp), next(nullptr) {}
};

class Polynomial {
private:
    Term* head;

    void appendTerm(int coeff, int exp) {
        Term* newTerm = new Term(coeff, exp);
        if (!head) {
            head = newTerm;
        } else {
            Term* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newTerm;
        }
    }

public:
    Polynomial() : head(nullptr) {}

    ~Polynomial() {
        Term* current = head;
        while (current != nullptr) {
            Term* nextTerm = current->next;
            delete current;
            current = nextTerm;
        }
    }

    void create() {
        int n;
        std::cout << "Enter the number of terms: ";
        std::cin >> n;
        if (n <= 0) return;
        
        std::cout << "Enter each term (coefficient and exponent), ensuring exponents are in DESCENDING order.\n";
        for (int i = 0; i < n; ++i) {
            int coeff, exp;
            std::cout << "Term " << i + 1 << " (coeff exp): ";
            std::cin >> coeff >> exp;
            if (coeff != 0) {
                appendTerm(coeff, exp);
            }
        }
    }

    Polynomial operator+(const Polynomial& other) const {
        Polynomial result;
        Term* p1 = this->head;
        Term* p2 = other.head;

        while (p1 && p2) {
            if (p1->exponent > p2->exponent) {
                result.appendTerm(p1->coefficient, p1->exponent);
                p1 = p1->next;
            } else if (p2->exponent > p1->exponent) {
                result.appendTerm(p2->coefficient, p2->exponent);
                p2 = p2->next;
            } else {
                int sum_coeff = p1->coefficient + p2->coefficient;
                if (sum_coeff != 0) {
                    result.appendTerm(sum_coeff, p1->exponent);
                }
                p1 = p1->next;
                p2 = p2->next;
            }
        }

        while (p1) {
            result.appendTerm(p1->coefficient, p1->exponent);
            p1 = p1->next;
        }

        while (p2) {
            result.appendTerm(p2->coefficient, p2->exponent);
            p2 = p2->next;
        }

        return result;
    }

    void display() const {
        if (!head) {
            std::cout << "0\n";
            return;
        }

        Term* current = head;
        bool isFirst = true;

        while (current) {
            if (current->coefficient == 0) {
                 current = current->next;
                 continue;
            }
            
            if (!isFirst) {
                if (current->coefficient > 0) std::cout << " + ";
                else std::cout << " - ";
            } else if (current->coefficient < 0) {
                 std::cout << "-";
            }
            
            int absCoeff = (current->coefficient > 0) ? current->coefficient : -current->coefficient;

            if (absCoeff != 1 || current->exponent == 0) {
                std::cout << absCoeff;
            }

            if (current->exponent != 0) {
                std::cout << "x";
                if (current->exponent != 1) {
                    std::cout << "^" << current->exponent;
                }
            }
            
            isFirst = false;
            current = current->next;
        }
        
        if (isFirst) {
            std::cout << "0";
        }
        
        std::cout << std::endl;
    }
};

int main() {
    Polynomial p1, p2;

    std::cout << "--- Create First Polynomial ---\n";
    p1.create();

    std::cout << "\n--- Create Second Polynomial ---\n";
    p2.create();

    Polynomial p3 = p1 + p2;

    std::cout << "\n----------------------------------\n";
    std::cout << "First Polynomial:  ";
    p1.display();
    std::cout << "Second Polynomial: ";
    p2.display();
    std::cout << "Sum of Polynomials: ";
    p3.display();
    std::cout << "----------------------------------\n";

    return 0;
}
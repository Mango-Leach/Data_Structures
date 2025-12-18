#include <iostream>
#include <string>

class StudentNode {
public:
    int roll_number;
    std::string name;
    StudentNode* next;

    StudentNode(int roll, const std::string& studentName)
        : roll_number(roll), name(studentName), next(nullptr) {}
};

class StudentSet {
private:
    StudentNode* head;

public:
    StudentSet();
    ~StudentSet();
    StudentNode* getHead() const;
    bool contains(int roll) const;
    void addStudent(int roll, const std::string& name);
    void display() const;
};

StudentSet::StudentSet() : head(nullptr) {}

StudentSet::~StudentSet() {
    StudentNode* current = head;
    while (current != nullptr) {
        StudentNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

StudentNode* StudentSet::getHead() const {
    return head;
}

bool StudentSet::contains(int roll) const {
    StudentNode* temp = head;
    while (temp != nullptr) {
        if (temp->roll_number == roll) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void StudentSet::addStudent(int roll, const std::string& name) {
    if (contains(roll)) {
        return;
    }
    StudentNode* newStudent = new StudentNode(roll, name);
    if (!head) {
        head = newStudent;
    } else {
        StudentNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newStudent;
    }
}

void StudentSet::display() const {
    if (!head) {
        std::cout << " (empty set)" << std::endl;
        return;
    }
    StudentNode* temp = head;
    while (temp != nullptr) {
        std::cout << " [" << temp->roll_number << ": " << temp->name << "]";
        temp = temp->next;
        if (temp) std::cout << ",";
    }
    std::cout << std::endl;
}

StudentSet findIntersection(const StudentSet& setA, const StudentSet& setB) {
    StudentSet result;
    StudentNode* current = setA.getHead();
    while (current != nullptr) {
        if (setB.contains(current->roll_number)) {
            result.addStudent(current->roll_number, current->name);
        }
        current = current->next;
    }
    return result;
}

StudentSet findSymmetricDifference(const StudentSet& setA, const StudentSet& setB) {
    StudentSet result;
    StudentNode* currentA = setA.getHead();
    while (currentA != nullptr) {
        if (!setB.contains(currentA->roll_number)) {
            result.addStudent(currentA->roll_number, currentA->name);
        }
        currentA = currentA->next;
    }

    StudentNode* currentB = setB.getHead();
    while (currentB != nullptr) {
        if (!setA.contains(currentB->roll_number)) {
            result.addStudent(currentB->roll_number, currentB->name);
        }
        currentB = currentB->next;
    }
    return result;
}

StudentSet findUnion(const StudentSet& setA, const StudentSet& setB) {
    StudentSet result;
    StudentNode* currentA = setA.getHead();
    while (currentA != nullptr) {
        result.addStudent(currentA->roll_number, currentA->name);
        currentA = currentA->next;
    }

    StudentNode* currentB = setB.getHead();
    while (currentB != nullptr) {
        result.addStudent(currentB->roll_number, currentB->name);
        currentB = currentB->next;
    }
    return result;
}

int main() {
    StudentSet totalStudents, cricketFans, footballFans;

    totalStudents.addStudent(1, "Rahul");
    totalStudents.addStudent(2, "Amit");
    totalStudents.addStudent(3, "Priya");
    totalStudents.addStudent(4, "Sneha");
    totalStudents.addStudent(5, "Vikas");
    totalStudents.addStudent(6, "Nidhi");
    totalStudents.addStudent(7, "Ravi");
    totalStudents.addStudent(8, "Kavita");

    cricketFans.addStudent(1, "Rahul");
    cricketFans.addStudent(3, "Priya");
    cricketFans.addStudent(5, "Vikas");
    cricketFans.addStudent(7, "Ravi");

    footballFans.addStudent(3, "Priya");
    footballFans.addStudent(4, "Sneha");
    footballFans.addStudent(5, "Vikas");
    footballFans.addStudent(8, "Kavita");

    std::cout << "--- Initial Student Groups ---\n";
    std::cout << "Total Students in Class:";
    totalStudents.display();
    std::cout << "Cricket Fans (Set A):";
    cricketFans.display();
    std::cout << "Football Fans (Set B):";
    footballFans.display();
    std::cout << "\n--- Set Operations ---\n";

    std::cout << "a) Students who like BOTH Cricket and Football (A n B):\n";
    StudentSet bothSports = findIntersection(cricketFans, footballFans);
    bothSports.display();

    std::cout << "\n" << "b) Students who like EITHER Cricket OR Football, but NOT BOTH (A ^ B):\n";
    StudentSet oneSportOnly = findSymmetricDifference(cricketFans, footballFans);
    oneSportOnly.display();

    std::cout << "\n" << "c) Students who like NEITHER Cricket NOR Football:\n";
    StudentSet sportsFans = findUnion(cricketFans, footballFans);
    int neitherCount = 0;
    StudentNode* current = totalStudents.getHead();
    while (current != nullptr) {
        if (!sportsFans.contains(current->roll_number)) {
            neitherCount++;
            std::cout << " [" << current->roll_number << ": " << current->name << "]";
        }
        current = current->next;
    }
    if (neitherCount == 0) {
        std::cout << " (none)";
    }
    std::cout << "\nTotal number of students who like neither sport: " << neitherCount << std::endl;

    return 0;
}
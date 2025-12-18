#include <iostream>


class MultiStack {
private:
    int *arr;      
    int *top;      
    int *base;     
    int num_stacks;
    int arr_size;  
    int stack_capacity;

public:
    MultiStack(int k, int n) {
        num_stacks = k;
        arr_size = n;
        stack_capacity = arr_size / num_stacks;

        arr = new int[arr_size];
        top = new int[num_stacks];
        base = new int[num_stacks];

        for (int i = 0; i < num_stacks; ++i) {
            base[i] = i * stack_capacity;
            top[i] = base[i] - 1;
        }
    }

    ~MultiStack() {
        delete[] arr;
        delete[] top;
        delete[] base;
    }

    bool isFull(int stack_num) {
        if (stack_num < 0 || stack_num >= num_stacks) {
             std::cout << "Error: Invalid stack number." << std::endl;
             return true; 
        }
        return top[stack_num] >= base[stack_num] + stack_capacity - 1;
    }

    bool isEmpty(int stack_num) {
         if (stack_num < 0 || stack_num >= num_stacks) {
             std::cout << "Error: Invalid stack number." << std::endl;
             return true; 
        }
        return top[stack_num] < base[stack_num];
    }

    void push(int stack_num, int value) {
        if (isFull(stack_num)) {
            std::cout << "Stack Overflow on stack " << stack_num << std::endl;
            return;
        }
        top[stack_num]++;
        arr[top[stack_num]] = value;
        std::cout << value << " pushed to stack " << stack_num << "." << std::endl;
    }

    int pop(int stack_num) {
        if (isEmpty(stack_num)) {
            std::cout << "Stack Underflow on stack " << stack_num << std::endl;
            return -1; // Return a sentinel value
        }
        int value = arr[top[stack_num]];
        top[stack_num]--;
        return value;
    }

    void display(int stack_num) {
        if (isEmpty(stack_num)) {
            std::cout << "Stack " << stack_num << " is empty." << std::endl;
            return;
        }
        std::cout << "Elements in stack " << stack_num << ": ";
        for (int i = base[stack_num]; i <= top[stack_num]; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
};

void showMenu() {
    std::cout << "\n--- Multi-Stack Operations ---\n";
    std::cout << "1. Push\n";
    std::cout << "2. Pop\n";
    std::cout << "3. Display Stack\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    int total_size, num_stacks;
    std::cout << "Enter total size of the array: ";
    std::cin >> total_size;
    std::cout << "Enter number of stacks: ";
    std::cin >> num_stacks;

    if (num_stacks > total_size) {
        std::cout << "Error: Number of stacks cannot be greater than array size." << std::endl;
        return 1;
    }

    MultiStack ms(num_stacks, total_size);
    int choice, stack_num, value;

    do {
        showMenu();
        std::cin >> choice;

        if (choice >= 1 && choice <= 3) {
            std::cout << "Enter stack number (0 to " << num_stacks - 1 << "): ";
            std::cin >> stack_num;
             if (stack_num < 0 || stack_num >= num_stacks) {
                std::cout << "Invalid stack number. Please try again." << std::endl;
                continue;
            }
        }
        
        switch (choice) {
            case 1:
                std::cout << "Enter value to push: ";
                std::cin >> value;
                ms.push(stack_num, value);
                break;
            case 2: {
                int popped_value = ms.pop(stack_num);
                if (popped_value != -1) {
                    std::cout << "Popped value from stack " << stack_num << ": " << popped_value << std::endl;
                }
                break;
            }
            case 3:
                ms.display(stack_num);
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

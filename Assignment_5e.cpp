#include <iostream>
#include <stack>
#include <string>
#include <cctype>

// Function to evaluate a postfix expression
int evaluatePostfix(const std::string& expr) {
    std::stack<int> s;

    // Iterate through each character of the expression
    for (char const &c: expr) {
        // If the character is a digit, convert it to an integer and push it onto the stack
        if (isdigit(c)) {
            s.push(c - '0');
        } 
        // If the character is an operator
        else {
            // There must be at least two operands on the stack
            if (s.size() < 2) {
                std::cerr << "Error: Invalid postfix expression." << std::endl;
                return -1; // Indicate error
            }

            // Pop the top two operands
            int val2 = s.top();
            s.pop();
            int val1 = s.top();
            s.pop();

            // Perform the operation and push the result back onto the stack
            switch (c) {
                case '+':
                    s.push(val1 + val2);
                    break;
                case '-':
                    s.push(val1 - val2);
                    break;
                case '*':
                    s.push(val1 * val2);
                    break;
                case '/':
                    if (val2 == 0) {
                        std::cerr << "Error: Division by zero." << std::endl;
                        return -1; // Indicate error
                    }
                    s.push(val1 / val2);
                    break;
                default:
                    std::cerr << "Error: Invalid character in expression." << std::endl;
                    return -1; // Indicate error
            }
        }
    }

    // After iterating, the stack should contain exactly one element: the final result
    if (s.size() != 1) {
        std::cerr << "Error: Invalid postfix expression." << std::endl;
        return -1; // Indicate error
    }

    return s.top();
}

int main() {
    std::string postfixExpr1 = "23*54*+9-"; // (2*3) + (5*4) - 9 = 6 + 20 - 9 = 17
    std::string postfixExpr2 = "82/3-32*+"; // (8/2) - 3 + (3*2) = 4 - 3 + 6 = 7

    std::cout << "Postfix Expression: " << postfixExpr1 << std::endl;
    int result1 = evaluatePostfix(postfixExpr1);
    if (result1 != -1) {
        std::cout << "Result: " << result1 << std::endl;
    }

    std::cout << "\nPostfix Expression: " << postfixExpr2 << std::endl;
    int result2 = evaluatePostfix(postfixExpr2);
    if (result2 != -1) {
        std::cout << "Result: " << result2 << std::endl;
    }

    return 0;
}
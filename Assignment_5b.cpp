#include <iostream>
#include <stack>
#include <string>
#include <cctype>

int getPrecedence(char op) {
    if (op == '^') {
        return 3;
    } else if (op == '*' || op == '/') {
        return 2;
    } else if (op == '+' || op == '-') {
        return 1;
    } else {
        return -1;
    }
}

std::string infixToPostfix(const std::string& infix) {
    std::stack<char> operatorStack;
    std::string postfix = "";

    for (char symbol : infix) {
        if (isalnum(symbol)) {
            postfix += symbol;
        }
        else if (symbol == '(') {
            operatorStack.push(symbol);
        }
        else if (symbol == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            if (!operatorStack.empty()) {
                operatorStack.pop();
            }
        }
        else {
            while (!operatorStack.empty() && operatorStack.top() != '(' && getPrecedence(symbol) <= getPrecedence(operatorStack.top())) {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(symbol);
        }
    }

    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }

    return postfix;
}

int main() {
    std::string infixExpression = "a-b*c-d/e+f";
    
    std::cout << "Infix Expression: " << infixExpression << std::endl;
    
    std::string postfixExpression = infixToPostfix(infixExpression);
    
    std::cout << "Postfix Expression: " << postfixExpression << std::endl;

    return 0;
}


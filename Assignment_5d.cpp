#include <iostream>
#include <stack>
#include <string>

bool areParenthesesBalanced(const std::string& expr) {
    std::stack<char> s;
    char ch;

    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{') {
            s.push(expr[i]);
            continue;
        }

        if (s.empty()) {
            return false;
        }

        switch (expr[i]) {
        case ')':
            ch = s.top();
            s.pop();
            if (ch == '{' || ch == '[') {
                return false;
            }
            break;

        case '}':
            ch = s.top();
            s.pop();
            if (ch == '(' || ch == '[') {
                return false;
            }
            break;

        case ']':
            ch = s.top();
            s.pop();
            if (ch == '(' || ch == '{') {
                return false;
            }
            break;
        }
    }

    return (s.empty());
}

int main() {
    std::string balancedExpr = "{()}[]";
    std::string unbalancedExpr = "{([)]}";
    std::string anotherBalancedExpr = "()[]{}";
    std::string anotherUnbalancedExpr = "(]";

    std::cout << "Expression: " << balancedExpr << std::endl;
    if (areParenthesesBalanced(balancedExpr)) {
        std::cout << "Result: Balanced" << std::endl;
    } else {
        std::cout << "Result: Not Balanced" << std::endl;
    }

    std::cout << "\nExpression: " << unbalancedExpr << std::endl;
    if (areParenthesesBalanced(unbalancedExpr)) {
        std::cout << "Result: Balanced" << std::endl;
    } else {
        std::cout << "Result: Not Balanced" << std::endl;
    }
    
    std::cout << "\nExpression: " << anotherBalancedExpr << std::endl;
    if (areParenthesesBalanced(anotherBalancedExpr)) {
        std::cout << "Result: Balanced" << std::endl;
    } else {
        std::cout << "Result: Not Balanced" << std::endl;
    }

    std::cout << "\nExpression: " << anotherUnbalancedExpr << std::endl;
    if (areParenthesesBalanced(anotherUnbalancedExpr)) {
        std::cout << "Result: Balanced" << std::endl;
    } else {
        std::cout << "Result: Not Balanced" << std::endl;
    }

    return 0;
}


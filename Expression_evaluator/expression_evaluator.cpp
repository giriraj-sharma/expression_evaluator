#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#include <cctype>
#include <stdexcept>

using namespace std;

// ==========================================
// Expression Evaluator (Mini Compiler)
// ==========================================

/**
 * Returns the precedence of mathematical operators.
 * Higher number means higher precedence.
 */
int getPrecedence(char op) {
    if (op == '^')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return -1;
}

/**
 * Applies a mathematical operator to two operands.
 * Includes basic error handling like division by zero.
 */
double applyOperator(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) throw runtime_error("Division by zero!");
            return a / b;
        case '^': return pow(a, b);
        default: throw runtime_error("Invalid operator!");
    }
}

/**
 * Checks if a character is a supported operator.
 */
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

/**
 * Converts an Infix expression (e.g., "3 + 4 * 2") 
 * to Postfix expression (e.g., "3 4 2 * +") using a stack.
 */
string infixToPostfix(const string& infix) {
    stack<char> st;
    string postfix = "";
    
    for (size_t i = 0; i < infix.length(); ++i) {
        char c = infix[i];
        
        // Skip whitespaces
        if (isspace(c)) continue;
        
        // If character is an operand (number), add to postfix string.
        // This loop handles multi-digit numbers and decimal points.
        if (isdigit(c) || c == '.') {
            while (i < infix.length() && (isdigit(infix[i]) || infix[i] == '.')) {
                postfix += infix[i];
                i++;
            }
            postfix += " "; // Add space to separate numbers in postfix
            i--; // Decrement 'i' since the outer loop will increment it again
        }
        // If character is an opening parenthesis, push to stack
        else if (c == '(') {
            st.push('(');
        }
        // If character is a closing parenthesis, pop and add to postfix until '(' is found
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                postfix += " ";
                st.pop();
            }
            // Pop the '(' if it exists, otherwise we have mismatched parentheses
            if (!st.empty() && st.top() == '(') {
                st.pop(); 
            } else {
                throw runtime_error("Mismatched parentheses!");
            }
        }
        // If character is an operator
        else if (isOperator(c)) {
            // Pop operators with higher or equal precedence from stack to postfix
            // Note: '^' is right-associative, so we treat it slightly differently
            while (!st.empty() && getPrecedence(c) <= getPrecedence(st.top())) {
                // Right-associativity condition for '^'
                if (c == '^' && st.top() == '^') {
                    break;
                }
                postfix += st.top();
                postfix += " ";
                st.pop();
            }
            st.push(c); // Push the current operator to stack
        } else {
            throw runtime_error(string("Invalid character encountered: ") + c);
        }
    }
    
    // Pop any remaining operators from the stack
    while (!st.empty()) {
        if (st.top() == '(') {
            throw runtime_error("Mismatched parentheses!");
        }
        postfix += st.top();
        postfix += " ";
        st.pop();
    }
    
    return postfix;
}

/**
 * Evaluates a given Postfix expression using a stack.
 */
double evaluatePostfix(const string& postfix) {
    stack<double> st;
    
    for (size_t i = 0; i < postfix.length(); ++i) {
        char c = postfix[i];
        
        // Skip whitespaces
        if (isspace(c)) continue;
        
        // If character is part of a number, extract the full number and push to stack
        if (isdigit(c) || c == '.') {
            string numStr = "";
            while (i < postfix.length() && (isdigit(postfix[i]) || postfix[i] == '.')) {
                numStr += postfix[i];
                i++;
            }
            st.push(stod(numStr)); // Convert string to double and push
            i--;
        }
        // If character is an operator, pop two operands and apply the operator
        else if (isOperator(c)) {
            if (st.size() < 2) {
                throw runtime_error("Invalid expression format! Missing operands.");
            }
            double val2 = st.top(); st.pop(); // The right operand is popped first
            double val1 = st.top(); st.pop(); // The left operand is popped second
            
            double result = applyOperator(val1, val2, c);
            st.push(result);
        }
    }
    
    // After parsing everything, there should be exactly one result in the stack
    if (st.size() != 1) {
        throw runtime_error("Invalid expression format! Too many operands.");
    }
    
    return st.top();
}

/**
 * Main wrapper function that coordinates parsing and evaluation.
 */
double evaluateExpression(const string& expression) {
    // Step 1: Parse and convert Infix string to Postfix
    string postfix = infixToPostfix(expression);
    cout << "  [Debug] Postfix string: " << postfix << endl;
    
    // Step 2: Evaluate the Postfix string to a final numeric result
    return evaluatePostfix(postfix);
}

// ==========================================
// Main Function Loop
// ==========================================
int main() {
    cout << "========================================================" << endl;
    cout << "    Expression Evaluator (Mini Compiler using Stack)    " << endl;
    cout << "========================================================" << endl;
    cout << "Supported operations: +, -, *, /, ^ (Power), () (Parentheses)" << endl;
    cout << "Type 'exit' to quit." << endl << endl;

    string expression;
    while (true) {
        cout << "Enter expression > ";
        getline(cin, expression);

        if (expression == "exit" || expression == "quit") {
            break;
        }

        if (expression.empty()) {
            continue;
        }

        try {
            // Attempt to parse and evaluate
            double result = evaluateExpression(expression);
            cout << "  [Result] " << result << endl;
        } catch (const exception& e) {
            // Handle any runtime errors gracefully (e.g., divide by zero, bad syntax)
            cout << "  [Error] " << e.what() << endl;
        }
        cout << "--------------------------------------------------------" << endl;
    }

    return 0;
}

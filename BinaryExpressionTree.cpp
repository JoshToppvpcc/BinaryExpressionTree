// binaryExpressionTree.cpp

#include "binaryExpressionTree.h"
#include <sstream>

// Constructor
binaryExpressionTree::binaryExpressionTree() = default;

// Destructor
binaryExpressionTree::~binaryExpressionTree() {
    destroyTree();
}

// No-op implementations for the pure virtual functions
void binaryExpressionTree::search(const std::string&) {}
void binaryExpressionTree::insert(const std::string&) {}
void binaryExpressionTree::deleteNode(const std::string&) {}

// Build expression tree from a postfix expression
void binaryExpressionTree::buildExpressionTree(const std::string& postfixExpression) {
    destroyTree(); // Clear any existing tree
    std::stack<nodeType<std::string>*> nodeStack;

    std::istringstream iss(postfixExpression);
    std::string token;

    while (iss >> token) {
        if (isdigit(token[0])) { // Operand
            nodeType<std::string>* newNode = new nodeType<std::string>();
            newNode->info = token;
            newNode->lLink = nullptr;
            newNode->rLink = nullptr;
            nodeStack.push(newNode);
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/") { // Operator
            if (nodeStack.empty()) throw std::runtime_error("Invalid expression: stack is empty");

            nodeType<std::string>* newNode = new nodeType<std::string>();
            newNode->info = token;
            newNode->rLink = nodeStack.top();
            nodeStack.pop();

            if (nodeStack.empty()) throw std::runtime_error("Invalid expression: stack is empty");

            newNode->lLink = nodeStack.top();
            nodeStack.pop();

            nodeStack.push(newNode);
        }
        else {
            throw std::runtime_error("Unsupported token in expression");
        }
    }

    if (nodeStack.empty()) throw std::runtime_error("Error: No expression tree formed");

    root = nodeStack.top();
    nodeStack.pop();

    if (!nodeStack.empty()) {
        root = nullptr;
        throw std::runtime_error("Error: Stack not empty after tree formation");
    }
}

// Public evaluate expression tree function
double binaryExpressionTree::evaluateExpressionTree() {
    if (!root) throw std::runtime_error("Error: Tree is empty");
    return evaluateExpressionTree(root);
}

// Private recursive evaluate function
double binaryExpressionTree::evaluateExpressionTree(nodeType<std::string>* p) {
    if (!p->lLink && !p->rLink) { // Leaf node, base case
        return std::stod(p->info);
    }

    // Recursive evaluation for left and right subtrees
    double x = evaluateExpressionTree(p->lLink);
    double y = evaluateExpressionTree(p->rLink);
    std::string op = p->info;

    if (op == "+") return x + y;
    if (op == "-") return x - y;
    if (op == "*") return x * y;
    if (op == "/") return x / y;

    throw std::runtime_error("Unsupported operator in expression tree");
}


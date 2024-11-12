#include "binaryTree.h"
#include <stack>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

class binaryExpressionTree : public binaryTreeType<std::string> {
public:
    // Constructor and destructor
    binaryExpressionTree() = default;
    ~binaryExpressionTree() { destroyTree(); }

    // Required no-op implementations for pure virtual functions
    void search(const std::string&) override {}
    void insert(const std::string&) override {}
    void deleteNode(const std::string&) override {}

    // Build tree from a postfix expression
    void buildExpressionTree(const std::string& postfixExpression);

    // Evaluate the expression tree
    double evaluateExpressionTree();

private:
    double evaluateExpressionTree(nodeType<std::string>* p);
};

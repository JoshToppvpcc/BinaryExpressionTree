#include "binaryExpressionTree.h"
#include <iostream>
#include <fstream>

int main() {
    std::ifstream inputFile("RpnData.txt");
    std::ofstream outputFile("expressionResults.txt");

    if (!inputFile) {
        std::cerr << "Error opening input file.\n";
        return 1;
    }
    if (!outputFile) {
        std::cerr << "Error opening output file.\n";
        return 1;
    }

    binaryExpressionTree exprTree;
    std::string line;

    while (std::getline(inputFile, line)) {
        try {
            exprTree.buildExpressionTree(line);
            double result = exprTree.evaluateExpressionTree();
            outputFile << "Expression: " << line << " = " << result << "\n";
        }
        catch (const std::exception& e) {
            outputFile << "Error evaluating expression: " << line << " - " << e.what() << "\n";
        }
    }

    inputFile.close();
    outputFile.close();
    std::cout << "Expressions evaluated and results saved to expressionResults.txt\n";

    return 0;
}
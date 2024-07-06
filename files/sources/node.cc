#include <node.h>

#include <regex>

Node::Node(std::string lexVal, Node* l, Node* r) {
    _lexicalValue = lexVal;
    _left = l;
    _right = r;
};

Node::Node(std::string lexVal) {
    _lexicalValue = lexVal;
};

bool isInteger(std::string str) {
    std::regex integerRegex("^-?\\d+$");
    return std::regex_match(str, integerRegex);
}

bool isFloat(std::string str) {
    std::regex floatRegex("^-?\\d*\\.\\d+$|^-?\\d+\\.\\d*$");
    return std::regex_match(str, floatRegex);
}

std::string Node::getExpressionType(SymbolTable *symbolTable) {
    if (_left == nullptr && _right == nullptr) {
        if (isInteger(_lexicalValue)) {
            return "int";
        }

        if (isFloat(_lexicalValue)) {
            return "float";
        }

        std::string type = symbolTable->getType(_lexicalValue);
        return type;
    }
    
    if (_left == nullptr) {
        return _right->getExpressionType(symbolTable);
    }

    if (_right == nullptr) {
        return _left->getExpressionType(symbolTable);
    }

    std::string rightExpressionType = _right->getExpressionType(symbolTable);
    std::string leftExpressionType = _left->getExpressionType(symbolTable);
    if (rightExpressionType == leftExpressionType) {
        return rightExpressionType;
    }

    throw "expression types do not match";
};

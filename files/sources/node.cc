#include <node.h>

#include <regex>
#include <iostream>

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

std::string Node::code(TemporaryVariable *t) {
    if (_left == nullptr && _right == nullptr) {
        std::string newT = t->newT();
        _t = newT;
        return newT + " = " + _lexicalValue + '\n';
    }

    if (_left == nullptr) {
        std::string newT = t->newT();
        _t = newT;
        std::string rightCode = _right->code(t);
        return rightCode + newT + " = " + _lexicalValue + ' ' + _right->_t + '\n';
    }

    if (_right == nullptr) {
        std::string newT = t->newT();
        _t = newT;
        std::string leftCode = _right->code(t);
        return leftCode + newT + " = " + _lexicalValue + ' ' + _left->_t + '\n';
    }

    std::string rightCode = _right->code(t);
    std::string leftCode = _left->code(t);
    std::string newT = t->newT();
    _t = newT;
    return rightCode + leftCode + newT + " = " + _right->_t + _lexicalValue + _left->_t + '\n' ;
}

std::string Node::getExpressionType(SymbolTable *symbolTable) {
    if (_left == nullptr && _right == nullptr) {
        std::string type;
        try {
            type = symbolTable->getType(_lexicalValue);
        } catch (...) {
            if (isInteger(_lexicalValue)) {
                type = "int";
            }

            if (isFloat(_lexicalValue)) {
                type = "float";
            }   
        }

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

    std::string error = "expression types do not match";
    throw std::logic_error(error);
};

void Node::printLeftFromRight() {
    if (_left == nullptr && _right == nullptr) {
        if (!_lexicalValue.empty()) {
            // Print identificators and constants.
            std::cout << _lexicalValue << " ";
        }
    }
    
    if (_left != nullptr) {
        _left->printLeftFromRight();
    }

    if (_left != nullptr || _right != nullptr) {
        // Print operations.
        std::cout << _lexicalValue << " ";
    }
    
    if (_right != nullptr) {
        _right->printLeftFromRight();
    }
}

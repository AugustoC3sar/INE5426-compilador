#include <node.h>

Node::Node(std::string lexVal, Node* l, Node* r) {
    _lexicalValue = lexVal;
    _left = l;
    _right = r;
};

#ifndef NODE_H
#define NODE_H

#include <string>

class Node
{
private:
    Node *_left;
    Node *_right;
    std::string _lexicalValue;

public:
    Node(std::string lexVal, Node *l, Node *r);
};

#endif

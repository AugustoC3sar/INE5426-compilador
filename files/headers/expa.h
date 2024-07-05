#ifndef EXPA_H
#define EXPA_H

#include <parser.h>

class AssignTreeSemanticAction : public SemanticAction
{
public:
  std::string name;
  std::string type;
  NonTerminal *parent;

  AssignTreeSemanticAction(std::string t, NonTerminal *p)
  {
    name = "ASSIGN_TREE";
    parent = p;
    type = t;
  }

  std::string value() override
  {
    return name;
  }

  void execute() override
  {
    Item expression = parent->children.at(0);
    parent->node = expression.nonTerminal->node;
  }
};

class AssignTree : public Item
{
public:
  AssignTree(std::string t, NonTerminal *p)
  {
    semanticAction = new AssignTreeSemanticAction(t, p);
    type = SEMANTIC_ACTION;
  }
};

class CreateLeafNodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  std::string type;
  NonTerminal *parent;

  CreateLeafNodeSemanticAction(std::string t, NonTerminal *p)
  {
    name = "CREATE_LEAF_NODE";
    parent = p;
    type = t;
  }

  std::string value() override
  {
    return name;
  }

  void execute() override
  {
    Item item = parent->children.at(0);
    parent->node = new Node(item.terminal->lexicalValue, NULL, NULL);
  }
};

class CreateLeafNode : public Item
{
public:
  CreateLeafNode(std::string t, NonTerminal *p)
  {
    semanticAction = new CreateLeafNodeSemanticAction(t, p);
    type = SEMANTIC_ACTION;
  }
};

class ReturnNodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  std::string type;
  NonTerminal *parent;

  ReturnNodeSemanticAction(std::string t, NonTerminal *p)
  {
    name = "RETURN_NODE";
    parent = p;
    type = t;
  }

  std::string value() override
  {
    return name;
  }

  void execute() override
  {
    Item lastItem = parent->children.at(parent->children.size() - 1);
    parent->node = lastItem.nonTerminal->node;
  }
};

class ReturnNode : public Item
{
public:
  ReturnNode(std::string t, NonTerminal *p)
  {
    semanticAction = new ReturnNodeSemanticAction(t, p);
    type = SEMANTIC_ACTION;
  }
};

class ReturnOperationValueSemanticAction : public SemanticAction
{
public:
  std::string name;
  std::string type;
  NonTerminal *parent;

  ReturnOperationValueSemanticAction(std::string t, NonTerminal *p)
  {
    name = "RETURN_OPERATION_VALUE";
    parent = p;
    type = t;
  }

  std::string value() override
  {
    return name;
  }

  void execute() override
  {
    Item operation = parent->children.at(parent->children.size() - 1);
    parent->operationValue = operation.terminal->lexicalValue;
  }
};

class ReturnOperationValue : public Item
{
public:
  ReturnOperationValue(std::string t, NonTerminal *p)
  {
    semanticAction = new ReturnOperationValueSemanticAction(t, p);
    type = SEMANTIC_ACTION;
  }
};

class SyntehsizeNodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  std::string type;
  NonTerminal *parent;

  SyntehsizeNodeSemanticAction(std::string t, NonTerminal *p)
  {
    name = "SYNTHESIZE_NODE";
    parent = p;
    type = t;
  }

  std::string value() override
  {
    return name;
  }

  void execute() override
  {
    parent->node = parent->leftNode;
  }
};

class SyntehsizeNode : public Item
{
public:
  SyntehsizeNode(std::string t, NonTerminal *p)
  {
    semanticAction = new SyntehsizeNodeSemanticAction(t, p);
    type = SEMANTIC_ACTION;
  }
};

class CreateSignalNodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  std::string type;
  NonTerminal *parent;

  CreateSignalNodeSemanticAction(std::string t, NonTerminal *p)
  {
    name = "CREATE_SIGNAL_NODE";
    parent = p;
    type = t;
  }

  std::string value() override
  {
    return name;
  }

  void execute() override
  {
    Item signal = parent->children.at(0);
    Item factor = parent->children.at(1);
    parent->node = new Node(signal.nonTerminal->operationValue, parent->leftNode, factor.nonTerminal->node);
  }
};

class CreateSignalNode : public Item
{
public:
  CreateSignalNode(std::string t, NonTerminal *p)
  {
    semanticAction = new CreateSignalNodeSemanticAction(t, p);
    type = SEMANTIC_ACTION;
  }
};

class CreateOperatorNodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  std::string type;
  NonTerminal *parent;

  CreateOperatorNodeSemanticAction(std::string t, NonTerminal *p)
  {
    name = "CREATE_SIGNAL_NODE";
    parent = p;
    type = t;
  }

  std::string value() override
  {
    return name;
  }

  void execute() override
  {
    Item op = parent->children.at(0);
    Item unaryexpr = parent->children.at(1);
    parent->node = new Node(op.nonTerminal->operationValue, parent->leftNode, unaryexpr.nonTerminal->node);
  }
};

class CreateOperatorNode : public Item
{
public:
  CreateOperatorNode(std::string t, NonTerminal *p)
  {
    semanticAction = new CreateOperatorNodeSemanticAction(t, p);
    type = SEMANTIC_ACTION;
  }
};

class InheritUnaryexprNodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  std::string type;
  NonTerminal *parent;

  InheritUnaryexprNodeSemanticAction(std::string t, NonTerminal *p)
  {
    name = "INHERIT_UNARYEXPR_NODE";
    parent = p;
    type = t;
  }

  std::string value() override
  {
    return name;
  }

  void execute() override
  {
    Item unaryexpr = parent->children.at(0);
    Item term = parent->children.at(1);
    term.nonTerminal->leftNode = unaryexpr.nonTerminal->node;
  }
};

class InheritUnaryexprNode : public Item
{
public:
  InheritUnaryexprNode(std::string t, NonTerminal *p)
  {
    semanticAction = new InheritUnaryexprNodeSemanticAction(t, p);
    type = SEMANTIC_ACTION;
  }
};

class CreateSignalNodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  std::string type;
  NonTerminal *parent;

  CreateSignalNodeSemanticAction(std::string t, NonTerminal *p)
  {
    name = "CREATE_TERM_SIGNAL_NODE";
    parent = p;
    type = t;
  }

  std::string value() override
  {
    return name;
  }

  void execute() override
  {
    Item signal = parent->children.at(0);
    Item term = parent->children.at(1);
    Item termrec = parent->children.at(3);
    termrec.nonTerminal->leftNode = new Node(signal.terminal->lexicalValue, parent->leftNode, term.nonTerminal->node);
  }
};

class CreateSignalNode : public Item
{
public:
  CreateSignalNode(std::string t, NonTerminal *p)
  {
    semanticAction = new CreateSignalNodeSemanticAction(t, p);
    type = SEMANTIC_ACTION;
  }
};

class InheritTermNodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  std::string type;
  NonTerminal *parent;

  InheritTermNodeSemanticAction(std::string t, NonTerminal *p)
  {
    name = "INHERIT_TERM_NODE";
    parent = p;
    type = t;
  }

  std::string value() override
  {
    return name;
  }

  void execute() override
  {
    Item term = parent->children.at(0);
    Item numexpression = parent->children.at(2);
    numexpression.nonTerminal->leftNode = term.nonTerminal->node;
  }
};

class InheritTermNode : public Item
{
public:
  InheritTermNode(std::string t, NonTerminal *p)
  {
    semanticAction = new InheritTermNodeSemanticAction(t, p);
    type = SEMANTIC_ACTION;
  }
};
class InheritNumexpressionNodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  std::string type;
  NonTerminal *parent;

  InheritNumexpressionNodeSemanticAction(std::string t, NonTerminal *p)
  {
    name = "INHERIT_NUMEXPRESSION_NODE";
    parent = p;
    type = t;
  }

  std::string value() override
  {
    return name;
  }

  void execute() override
  {
    Item expression = parent->children.at(2);
    Item numexpression = parent->children.at(0);
    expression.nonTerminal->leftNode = numexpression.nonTerminal->node;
  }
};

class InheritNumexpressionNode : public Item
{
public:
  InheritNumexpressionNode(std::string t, NonTerminal *p)
  {
    semanticAction = new InheritNumexpressionNodeSemanticAction(t, p);
    type = SEMANTIC_ACTION;
  }
};

#endif

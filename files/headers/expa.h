#ifndef EXPA_H
#define EXPA_H

#include <parser.h>

#include <iostream>

class AssignTreeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;
  TemporaryVariable* _t;

  AssignTreeSemanticAction(NonTerminal *p, TemporaryVariable *t)
  {
    name = "ASSIGN_TREE";
    parent = p;
    _t = t;
  }

  std::string value() override
  {
    return name;
  }

  void execute()
  {
    Item expression = parent->children.at(0);
    parent->node = expression.nonTerminal->node;

    // Validates that all expressions arguments have the same type returning the expression type.
    if (parent->node != nullptr) {
      parent->node->getExpressionType(parent->symbolTable);
    }
  }
};

class AssignTree : public Item
{
public:
  AssignTree(NonTerminal *p,  TemporaryVariable *t)
  {
    semanticAction = new AssignTreeSemanticAction(p, t);
    type = SEMANTIC_ACTION;
  }
};

class CreateLeafNodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;

  CreateLeafNodeSemanticAction(NonTerminal *p)
  {
    name = "CREATE_LEAF_NODE";
    parent = p;
  }

  std::string value() override
  {
    return name;
  }

  void execute() override
  {
    Item item = parent->children.at(0);
    Node *node = new Node(item.terminal->lexicalValue);
    parent->node = node;
  }
};

class CreateLeafNode : public Item
{
public:
  CreateLeafNode(NonTerminal *p)
  {
    semanticAction = new CreateLeafNodeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class ReturnNodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;

  ReturnNodeSemanticAction(NonTerminal *p)
  {
    name = "RETURN_NODE";
    parent = p;
  }

  std::string value() override
  {
    return name;
  }

  void execute() override
  {
    Item lastItem = parent->children.at(parent->children.size() - 2);
    parent->node = lastItem.nonTerminal->node;
  }
};

class ReturnNode : public Item
{
public:
  ReturnNode(NonTerminal *p)
  {
    semanticAction = new ReturnNodeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class ReturnOperationValueSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;

  ReturnOperationValueSemanticAction(NonTerminal *p)
  {
    name = "RETURN_OPERATION_VALUE";
    parent = p;
  }

  std::string value() override
  {
    return name;
  }

  void execute() override
  {
    Item operation = parent->children.at(0);
    parent->operationValue = operation.terminal->lexicalValue;
  }
};

class ReturnOperationValue : public Item
{
public:
  ReturnOperationValue(NonTerminal *p)
  {
    semanticAction = new ReturnOperationValueSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class SyntehsizeNodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;

  SyntehsizeNodeSemanticAction(NonTerminal *p)
  {
    name = "SYNTHESIZE_NODE";
    parent = p;
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
  SyntehsizeNode(NonTerminal *p)
  {
    semanticAction = new SyntehsizeNodeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class CreateSignalNodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;

  CreateSignalNodeSemanticAction(NonTerminal *p)
  {
    name = "CREATE_SIGNAL_NODE";
    parent = p;
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
  CreateSignalNode(NonTerminal *p)
  {
    semanticAction = new CreateSignalNodeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class CreateOperatorNodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;

  CreateOperatorNodeSemanticAction(NonTerminal *p)
  {
    name = "CREATE_OPERATOR_NODE";
    parent = p;
  }

  std::string value() override
  {
    return name;
  }

  void execute() override
  {
    Item op = parent->children.at(0);
    Item factor = parent->children.at(1);
    parent->node = new Node(op.nonTerminal->operationValue, parent->leftNode, factor.nonTerminal->node);
  }
};

class CreateOperatorNode : public Item
{
public:
  CreateOperatorNode(NonTerminal *p)
  {
    semanticAction = new CreateOperatorNodeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class InheritUnaryexprNodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;

  InheritUnaryexprNodeSemanticAction(NonTerminal *p)
  {
    name = "INHERIT_UNARYEXPR_NODE";
    parent = p;
  }

  std::string value() override
  {
    return name;
  }

  void execute() override
  {
    Item unaryexpr = parent->children.at(0);
    Item term = parent->children.at(2);
    term.nonTerminal->leftNode = unaryexpr.nonTerminal->node;
  }
};

class InheritUnaryexprNode : public Item
{
public:
  InheritUnaryexprNode(NonTerminal *p)
  {
    semanticAction = new InheritUnaryexprNodeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class CreateInheritedSignalNodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;

  CreateInheritedSignalNodeSemanticAction(NonTerminal *p)
  {
    name = "CREATE_INHERITED_SIGNAL_NODE";
    parent = p;
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
    termrec.nonTerminal->leftNode = new Node(signal.nonTerminal->operationValue, parent->leftNode, term.nonTerminal->node);
  }
};

class CreateInheritedSignalNode : public Item
{
public:
  CreateInheritedSignalNode(NonTerminal *p)
  {
    semanticAction = new CreateInheritedSignalNodeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class InheritTermNodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;

  InheritTermNodeSemanticAction(NonTerminal *p)
  {
    name = "INHERIT_TERM_NODE";
    parent = p;
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
  InheritTermNode(NonTerminal *p)
  {
    semanticAction = new InheritTermNodeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class CreateUnaryexprRecInheritedNodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;

  CreateUnaryexprRecInheritedNodeSemanticAction(NonTerminal *p)
  {
    name = "CREATE_UNARYEXPR_REC_INHERITED_NODE";
    parent = p;
  }

  std::string value() override
  {
    return name;
  }

  void execute() override
  {
    Item op = parent->children.at(0);
    Item unaryexpr = parent->children.at(1);
    Item unaryexprRec = parent->children.at(3);
    unaryexprRec.nonTerminal->leftNode = new Node(op.nonTerminal->operationValue, parent->leftNode, unaryexpr.nonTerminal->node);
  }
};

class CreateUnaryexprRecInheritedNode : public Item
{
public:
  CreateUnaryexprRecInheritedNode(NonTerminal *p)
  {
    semanticAction = new CreateUnaryexprRecInheritedNodeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class InheritNumexpressionNodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;

  InheritNumexpressionNodeSemanticAction(NonTerminal *p)
  {
    name = "INHERIT_NUMEXPRESSION_NODE";
    parent = p;
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
  InheritNumexpressionNode(NonTerminal *p)
  {
    semanticAction = new InheritNumexpressionNodeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class SynthesizeNumexpressionNodeSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;

  SynthesizeNumexpressionNodeSemanticAction(NonTerminal *p)
  {
    name = "SynthesizeNumexpressionNode";
    parent = p;
  }

  std::string value() override
  {
    return name;
  }

  void execute() override
  {
    Item numexpression = parent->children.at(1);
    parent->node = numexpression.nonTerminal->node;
  }
};

class SynthesizeNumexpressionNode : public Item
{
public:
  SynthesizeNumexpressionNode(NonTerminal *p)
  {
    semanticAction = new SynthesizeNumexpressionNodeSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

class InheritLeftNodeToFirstChildSemanticAction : public SemanticAction
{
public:
  std::string name;
  NonTerminal *parent;

  InheritLeftNodeToFirstChildSemanticAction(NonTerminal *p)
  {
    name = "InheritLeftNodeToFirstChild";
    parent = p;
  }

  std::string value() override
  {
    return name;
  }

  void execute() override
  {
    Item firstChild = parent->children.at(1);
    firstChild.nonTerminal->leftNode = parent->leftNode;
  }
};

class InheritLeftNodeToFirstChild : public Item
{
public:
  InheritLeftNodeToFirstChild(NonTerminal *p)
  {
    semanticAction = new InheritLeftNodeToFirstChildSemanticAction(p);
    type = SEMANTIC_ACTION;
  }
};

#endif

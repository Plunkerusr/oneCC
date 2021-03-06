#pragma once
#include "../ASTNode.h"
namespace oneCC::AST {

class TernaryOperationNode : public Node {
public:
    TernaryOperationNode()
        : Node(servedType())
    {
    }
    
    TernaryOperationNode(Node* left, Node* middle, Node* right, Lexer::TokenType operation)
        : Node(servedType())
        , m_left(left)
        , m_middle(middle)
        , m_right(right)
        , m_operation(operation)
    {
    }

    ~TernaryOperationNode() override = default;

    void setChildren(Node* left, Node* middle, Node* right) { m_left = left, m_middle = middle, m_right = right; }
    void setLeftChild(Node* left) { m_left = left; }
    void setMiddleChild(Node* middle) { m_middle = middle; }
    void setRightChild(Node* right) { m_right = right; }
    void setOperation(Lexer::TokenType operation) { m_operation = operation; }

    Node* leftChild() const { return m_left; }
    Node* middleChild() const { return m_middle; }
    Node* rightChild() const { return m_right; }
    const Lexer::TokenType& operation() const { return m_operation; }

    static NodeType servedType() { return TernaryOperation; }

private:
    Node* m_left;
    Node* m_middle;
    Node* m_right;
    Lexer::TokenType m_operation;
};

}

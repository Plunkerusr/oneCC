#pragma once
#include "../ASTNode.h"

namespace oneCC::AST {

class Expression : public Node {
using Node::Node;

public:
    void setExpressionType(Lexer::TokenType expressionType) { m_expressionType = expressionType; }
    Lexer::TokenType expressionType() const { return m_expressionType ; }

protected:
    Lexer::TokenType m_expressionType;
};

}
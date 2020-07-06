#pragma once
#include "../ASTNode.h"
#include <string>

namespace oneCC::AST {

class IdentifierNode : public Node {
public:
    IdentifierNode() : Node(Identifier) { };
    explicit IdentifierNode(const std::string value)
            : Node(Identifier)
            , m_value(std::move(value)) { }

    ~IdentifierNode() override = default;

    std::string value() const { return m_value; }

private:
    std::string m_value;
};

}
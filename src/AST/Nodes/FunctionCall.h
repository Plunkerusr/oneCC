#pragma once
#include <utility>

#include "../ASTNode.h"

namespace oneCC::AST {

class FunctionCallNode : public Expression {
public:
    FunctionCallNode()
        : Expression(servedType())
    {
    }

    FunctionCallNode(const std::string& name, const std::vector<Node*>& arguments)
        : Expression(servedType())
        , m_name(name)
        , m_arguments(arguments)
    {
    }

    FunctionCallNode(const std::string& name, std::vector<Node*>&& arguments)
        : Expression(servedType())
        , m_name(name)
        , m_arguments(std::move(arguments))
    {
    }

    ~FunctionCallNode() override = default;

    void setName(const std::string& name) { m_name = name; }
    void setArguments(const std::vector<Node*>& arguments) { m_arguments = arguments; }

    const std::string& name() const { return m_name; }
    const std::vector<Node*>& arguments() const { return m_arguments; }

    static NodeType servedType() { return FunctionCallExpression; }

private:
    std::string m_name {};
    std::vector<Node*> m_arguments {};
};

}
#pragma once

#include "../../AST/AbstractAST.h"
#include "../../Lexer/Token.h"
#include "../../SemanticAnalyzer/Scoper/Scoper.h"
#include "../RegisterManager/RegisterManager.h"
#include "Translators/AsmTranslator.h"
#include "Common/Regs.h"
#include <cstdint>
#include <iostream>
#include <map>
#include <stack>
#include <string>

namespace oneCC::CodeGenerator::X86_32 {

class CodeGeneratorX86_32 final : public AST::AbstractAST {
public:
    CodeGeneratorX86_32();
    int processTree(AST::Node* program);

private:
    // From AST::AbstractAST
    using AST::AbstractAST::visitNode;
    void visitNode(AST::BinaryOperationNode* a) override;
    void visitNode(AST::TernaryOperationNode* a) override;
    void visitNode(AST::IdentifierNode* a) override;
    void visitNode(AST::BlockStatementNode* a) override;
    void visitNode(AST::ReturnStatementNode* a) override;
    void visitNode(AST::IfStatementNode* a) override;
    void visitNode(AST::WhileStatementNode* a) override;
    void visitNode(AST::FunctionNode* a) override;
    void visitNode(AST::FunctionCallNode* a) override;
    void visitNode(AST::ProgramNode* a) override;
    void visitNode(AST::IntConstNode* a) override;

    int generateLabel();
    std::string generateFunctionLabel(AST::FunctionNode* function);

    RegisterManager m_registerManager {};
    AsmTranslator m_asmTranslator {};
    SemanticAnalyzer::Scoper m_scoper {};

    std::map<std::string, std::string> m_functionLabels;
    uint64_t m_labelCount { 0 };
    uint64_t m_basePointerOffset { 0 };
};

}
#include "../AST/Nodes/BinaryOperation.h"
#include "../AST/Nodes/BlockStatement.h"
#include "../AST/Nodes/Function.h"
#include "../AST/Nodes/FunctionArgument.h"
#include "../AST/Nodes/FunctionCall.h"
#include "../AST/Nodes/Identifier.h"
#include "../AST/Nodes/IfStatement.h"
#include "../AST/Nodes/IntConst.h"
#include "../AST/Nodes/Program.h"
#include "../AST/Nodes/ReturnStatement.h"
#include "../AST/Nodes/TernaryOperation.h"
#include "../AST/Nodes/Type.h"
#include "../AST/Nodes/WhileStatement.h"
#include "../Exceptions.h"
#include "../Utils/ASTReader/ASTReader.h"
#include "Defines.h"
#include "Parser.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

namespace oneCC::Parser {

AST::FunctionArgumentNode* Parser::eatFunctionArgument()
{
    auto type = lookupToken();
    eatToken(Lexer::TokenType::TypeInt);
    auto varName = lookupToken();
    eatToken(Lexer::TokenType::Identifier);
    // TODO: where's createIntStatement()? Consider moving it back here

    AST::Node* expr = NULL;
    if (lookupToken().type() == Lexer::TokenType::Assign) {
        eatToken(Lexer::TokenType::Assign);
        expr = expression();
    }
    return new AST::FunctionArgumentNode(new AST::IdentifierNode(varName.lexeme(), type.type()), expr);
}

AST::Node* Parser::declareFunction()
{
    // FIXME: Now we eat only int
    auto type = lookupToken();
    eatToken(Lexer::TokenType::TypeInt);
    auto funcName = lookupToken();
    eatToken(Lexer::TokenType::Identifier);
    eatToken(Lexer::TokenType::OpenRoundBracket);

    // Eating args
    std::vector<AST::FunctionArgumentNode*> arguments;
    if (isType(lookupToken())) {
        auto* argDecl = eatFunctionArgument();
        softAssertNode(argDecl);
        arguments.push_back(argDecl);

        while (lookupToken().type() == Lexer::TokenType::Comma) {
            eatToken(Lexer::TokenType::Comma);
            auto* argDecl = eatFunctionArgument();
            softAssertNode(argDecl);
            arguments.push_back(argDecl);
        }
    }

    eatToken(Lexer::TokenType::CloseRoundBracket);

    if (lookupToken().type() == Lexer::TokenType::EndOfStatement) {
        // FIXME: Add support for function declaration
        return NULL;
    } else {
        auto functionNode = new AST::FunctionNode(new AST::IdentifierNode(funcName.lexeme(), type.type()), arguments, NULL);
        auto blockStat = blockStatement(functionNode);
        softAssertNode(blockStat);
        functionNode->setStatement((AST::BlockStatementNode*)(blockStat));
        return functionNode;
    }
}

}
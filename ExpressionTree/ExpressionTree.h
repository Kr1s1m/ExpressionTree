#pragma once
#include "ExprNode.h"
#include <string>
#include <map>
#include <vector>

class ExpressionTree
{
	ExprNode* root;

	std::map<char, int> variables;

	
	

	std::vector<std::string> generateExprVector(std::string);
	ExprNode* createTreeFromExprVector(std::vector<std::string>);
	
	int toInt(const std::string&);
	int evaluate(ExprNode*);

	bool isVariable(const std::string&) const;
	bool isOperator(const std::string&) const;

	void addNewVariable(std::string);
	void fillVariables();

	void printNormal(ExprNode*) const;
	void printReversePolish(ExprNode*) const;
	
public:

	ExpressionTree();
	ExpressionTree(std::string);

	int getResult();

	void printInfixExpr() const;
	void printPostFixExpr() const;
	
	
};


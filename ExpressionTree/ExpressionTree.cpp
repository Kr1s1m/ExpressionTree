#include "ExpressionTree.h"
#include <iostream>
#include <stack>

std::vector<std::string> ExpressionTree::generateExprVector(std::string expr)
{
	std::vector<std::string> exprVector;
	
	for(int i = 0; i < expr.length(); ++i)
	{
		if (expr[i] == ' ')
			continue;
		
		std::string currentExpr;
		
		while(expr[i] != ' ' && i < expr.length())
		{
			currentExpr.insert(currentExpr.end(), expr[i]);
			++i;
		}

		exprVector.push_back(currentExpr);
		
	}

	return exprVector;
}

ExprNode* ExpressionTree::createTreeFromExprVector(std::vector<std::string> exprVector)
{
	std::stack<ExprNode*> nodeStack;

	std::vector<std::string>::reverse_iterator it;

	for(it = exprVector.rbegin(); it != exprVector.rend(); ++it)
	{
		if(isOperator(*it))
		{
			ExprNode* leftNode = nodeStack.top();
			nodeStack.pop();
			
			ExprNode* rightNode = nodeStack.top();
			nodeStack.pop();

			ExprNode* tempNode = new ExprNode(*it, leftNode, rightNode);
			nodeStack.push(tempNode);
		}
		else
		{
			if (isVariable(*it))
				addNewVariable(*it);
			
			ExprNode* tempNode = new ExprNode(*it, nullptr, nullptr);
			nodeStack.push(tempNode);
		}
	}

	ExprNode* topNode = nodeStack.top();
	nodeStack.pop();

	return topNode;
}


bool ExpressionTree::isVariable(const std::string& expr) const
{
	return (expr.length() == 1 && expr[0] >= 'a' && expr[0] <= 'z');
}

bool ExpressionTree::isOperator(const std::string& expr) const
{
	return (expr.length() == 1 && 
			(expr[0] == '+' || expr[0] == '-' || expr[0] == '*'  ) );
}

void ExpressionTree::addNewVariable(std::string expr)
{
	variables.insert(std::map<char, int>::value_type(expr[0], 0));
}

void ExpressionTree::fillVariables()
{
	for(auto& variable : variables)
	{
		int variableValue;
		
		std::cout << "Enter " << variable.first << "\n";
		std::cin >> variableValue;

		variables[variable.first] = variableValue;
	}
}

void ExpressionTree::printNormal(ExprNode* node) const
{
	if (!node)
		return;

	if (node->left && node->right)
		std::cout << "( ";

	printNormal(node->left);

	std::cout << node->data << " ";

	printNormal(node->right);

	if (node->left && node->right)
		std::cout << ") ";
	
}

void ExpressionTree::printReversePolish(ExprNode* node) const
{
	if (!node)
		return;


	printReversePolish(node->left);
	printReversePolish(node->right);

	std::cout << node->data << ' ';
}

ExpressionTree::ExpressionTree()
{
	root = nullptr;
}

ExpressionTree::ExpressionTree(std::string prefixExpr)
{
	root = createTreeFromExprVector(generateExprVector(prefixExpr));
}

int ExpressionTree::getResult()
{
	fillVariables();

	std::cout << "Eval:     ";
	
	return evaluate(root);
}

int ExpressionTree::evaluate(ExprNode* node)
{
	if (!node)
		return 0;

	if (!node->left && !node->right)
		return toInt(node->data);

	int left = evaluate(node->left);
	int right = evaluate(node->right);

	if(isOperator(node->data))
	{
		if (node->data[0] == '+')
			return left + right;

		if (node->data[0] == '-')
			return left - right;

		if (node->data[0] == '*')
			return left * right;
	}
}

int ExpressionTree::toInt(const std::string& expr)
{
	if(isVariable(expr))
	{
		return variables[expr[0]];
	}

	int number = 0;

	if(expr[0] != '-')
	{
		for (int i = 0; i < expr.length(); ++i)
			number = number * 10 + ((int)expr[i] - 48);
	}
	else
	{
		for (int i = 1; i < expr.length(); ++i)
		{
			number = number * 10 + ((int)expr[i] - 48);
			number *= -1;
		}
			
	}

	return number;
	
}

void ExpressionTree::printInfixExpr() const
{
	std::cout << "Infix:    ";
	printNormal(root);
}

void ExpressionTree::printPostFixExpr() const
{
	std::cout << "Postfix:  ";
	printReversePolish(root);
}

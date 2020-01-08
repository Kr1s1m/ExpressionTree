#include "ExpressionTree.h"
#include <fstream>
#include <iostream>

std::vector<ExpressionTree> fillFromFile(std::string);

int main()
{
	
	std::vector<ExpressionTree> exprTrees = fillFromFile("expressions.txt");

	for(auto& exprTree : exprTrees)
	{
		exprTree.printInfixExpr();
		std::cout << '\n';
		std::cout << '\n';
		exprTree.printPostFixExpr();
		std::cout << '\n';
		std::cout << '\n';
		std::cout << exprTree.getResult() << '\n';
		std::cout << '\n';
		std::cout << '\n';
		std::cout << '\n';
	}
	
	return 0;
}

std::vector<ExpressionTree> fillFromFile(std::string fileName)
{
	std::ifstream iFile(fileName);
	
	std::vector<ExpressionTree> exprTrees;

	if(iFile)
	{
		while(!iFile.eof())
		{
			std::string expr;
			std::getline(iFile, expr);
			
			ExpressionTree exprTree(expr);
			exprTrees.push_back(exprTree);
		}
	}

	return exprTrees;
}
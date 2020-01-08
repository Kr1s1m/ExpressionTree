#pragma once
#include <string>

struct ExprNode
{
	std::string data;
	ExprNode* left, * right;

	ExprNode(std::string _data = "", ExprNode* _left = nullptr, ExprNode* _right = nullptr) : data(_data), left(_left), right(_right) {};
};

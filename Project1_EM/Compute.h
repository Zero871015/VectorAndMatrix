#pragma once
#include <string>
#include <iostream>
#include <map>
#include "Vector.h"
#include "Matrix.h"

MyMatrix Compute(std::string s,std::map<std::string,MyVector>, std::map<std::string, MyMatrix>);

int operatorPriorityInInput(char c);

int operatorPriorityInStack(char c);

bool isOperator(char c);

bool ispriority(char input, char stack);

std::string Postorder(std::string inorder);

bool cmdCheck(std::string, std::string);

std::string subOrder(std::string);

void subTwoOrder(std::string,std::string&,std::string&);

std::vector<std::string> subMultiOrder(std::string);
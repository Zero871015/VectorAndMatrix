#include "Compute.h"
#include "Exception.h"

MyMatrix Compute(std::string s, std::map<std::string, MyVector> vectors, std::map<std::string, MyMatrix> matrices)
{
	//std::cout << Postorder(s) << std::endl;
	s = Postorder(s);

	std::vector<MyMatrix> stackMatrix;
	std::vector<MyVector> stackVector;	//一個stack用於存放運算元
	std::string temp = "";	//一個暫存空間
	for (int i = 0; i < (int)s.length(); i++)
	{
		//假如遇上分隔字元...
		if (s[i] == ' ')
		{
			//判斷其是否為運算子
			if ((int)temp.length() == 1 && (isOperator(temp[0]) || temp == "@"))
			{
				int size = (int)stackVector.size();
				//矩陣部分
				if(size==0)
				{
					size = (int)stackMatrix.size();
					//從堆疊拿出兩個數做加法
					if (temp == "+")
					{
						if (size < 2)
						{
							//錯誤，運算式有錯誤
							throw Exceptions(computeError);
						}
						stackMatrix[size - 2] = add(stackMatrix[size - 2], stackMatrix[size - 1]);
						stackMatrix.pop_back();
						size--;
					}
					//從堆疊拿出兩個數做減法
					else if (temp == "-")
					{
						if (size < 2)
						{
							//錯誤，運算式有錯誤
							throw Exceptions(computeError);
						}
						stackMatrix[size - 2] = sub(stackMatrix[size - 2], stackMatrix[size - 1]);
						stackMatrix.pop_back();
						size--;
					}
					//從堆疊拿出兩個數做乘法
					else if (temp == "*")
					{
						if (size < 2)
						{
							//錯誤，運算式有錯誤
							throw Exceptions(computeError);
						}
						stackMatrix[size - 2] = mul(stackMatrix[size - 2], stackMatrix[size - 1]);
						stackMatrix.pop_back();
						size--;
					}
					//從堆疊拿出兩個數做除法
					else if (temp == "/")
					{
						//錯誤，運算式有錯誤
						throw Exceptions(computeError);
					}
					//從堆疊拿出一個數加負號
					else if (temp == "@")
					{
						//錯誤，運算式有錯誤
						throw Exceptions(computeError);
					}
					//從堆疊拿出兩個數做次方
					else if (temp == "^")
					{
						//錯誤，運算式有錯誤
						throw Exceptions(computeError);
					}
					//從堆疊拿出一個數做階層
					else if (temp == "!")
					{
						//錯誤，運算式有錯誤
						throw Exceptions(computeError);
					}
				}
				else
				{
					//向量部分
					//從堆疊拿出兩個數做加法
					if (temp == "+")
					{
						if (size < 2)
						{
							//錯誤，運算式有錯誤
							throw Exceptions(computeError);
						}
						stackVector[size - 2] = add(stackVector[size - 2], stackVector[size - 1]);
						stackVector.pop_back();
						size--;
					}
					//從堆疊拿出兩個數做減法
					else if (temp == "-")
					{
						if (size < 2)
						{
							//錯誤，運算式有錯誤
							throw Exceptions(computeError);
						}
						stackVector[size - 2] = sub(stackVector[size - 2], stackVector[size - 1]);
						stackVector.pop_back();
						size--;
					}
					//從堆疊拿出兩個數做乘法
					else if (temp == "*")
					{
						if (size < 2)
						{
							//錯誤，運算式有錯誤
							throw Exceptions(computeError);
						}
						stackVector[size - 2] = dot(stackVector[size - 2], stackVector[size - 1]);
						stackVector.pop_back();
						size--;
					}
					//從堆疊拿出兩個數做除法
					else if (temp == "/")
					{
						//錯誤，運算式有錯誤
						throw Exceptions(computeError);
					}
					//從堆疊拿出一個數加負號
					else if (temp == "@")
					{
						//錯誤，運算式有錯誤
						throw Exceptions(computeError);
					}
					//從堆疊拿出兩個數做次方
					else if (temp == "^")
					{
						//錯誤，運算式有錯誤
						throw Exceptions(computeError);
					}
					//從堆疊拿出一個數做階層
					else if (temp == "!")
					{
						//錯誤，運算式有錯誤
						throw Exceptions(computeError);
					}
				}
				
			}
			//不是運算符號，代表其為運算元
			//將此數放入堆疊中
			//先檢查是否為變數
			else
			{
				//特殊指令
				if (temp[0] == '\\')
				{
					int size = (int)stackVector.size();

					if (cmdCheck(temp, "length"))
					{
						stackVector.push_back(Compute(subOrder(temp), vectors, matrices)[0]);
						size = (int)stackVector.size();
						stackVector[size - 1] = length(stackVector[size - 1]);
					}
					else if (cmdCheck(temp, "normalize"))
					{
						stackVector.push_back(Compute(subOrder(temp), vectors, matrices)[0]);
						size = (int)stackVector.size();
						stackVector[size - 1] = normalize(stackVector[size - 1]);
					}
					else if (cmdCheck(temp, "cross"))
					{
						std::string a = "", b = "";
						subTwoOrder(temp, a, b);
						stackVector.push_back(Compute(a, vectors, matrices)[0]);
						stackVector.push_back(Compute(b, vectors, matrices)[0]);
						size = (int)stackVector.size();
						stackVector[size - 2] = cross(stackVector[size - 2], stackVector[size - 1]);
						stackVector.pop_back();
					}
					else if (cmdCheck(temp, "component"))
					{
						std::string a = "", b = "";
						subTwoOrder(temp, a, b);
						stackVector.push_back(Compute(a, vectors, matrices)[0]);
						stackVector.push_back(Compute(b, vectors, matrices)[0]);
						size = (int)stackVector.size();
						stackVector[size - 2] = component(stackVector[size - 2], stackVector[size - 1]);
						stackVector.pop_back();
					}
					else if (cmdCheck(temp, "projection"))
					{
						std::string a = "", b = "";
						subTwoOrder(temp, a, b);
						stackVector.push_back(Compute(a, vectors, matrices)[0]);
						stackVector.push_back(Compute(b, vectors, matrices)[0]);
						size = (int)stackVector.size();
						stackVector[size - 2] = projection(stackVector[size - 2], stackVector[size - 1]);
						stackVector.pop_back();
					}
					else if (cmdCheck(temp, "triangle"))
					{
						std::string a = "", b = "";
						subTwoOrder(temp, a, b);
						stackVector.push_back(Compute(a, vectors, matrices)[0]);
						stackVector.push_back(Compute(b, vectors, matrices)[0]);
						size = (int)stackVector.size();
						stackVector[size - 2] = triangle(stackVector[size - 2], stackVector[size - 1]);
						stackVector.pop_back();
					}
					else if (cmdCheck(temp, "parallel"))
					{
						std::string a = "", b = "";
						subTwoOrder(temp, a, b);
						stackVector.push_back(Compute(a, vectors, matrices)[0]);
						stackVector.push_back(Compute(b, vectors, matrices)[0]);
						size = (int)stackVector.size();
						if (parallel(stackVector[size - 2], stackVector[size - 1]))
							std::cout << "yes" << std::endl;
						else
							std::cout << "no" << std::endl;
						throw Exceptions(done);
					}
					else if (cmdCheck(temp, "orthogonal"))
					{
						std::string a = "", b = "";
						subTwoOrder(temp, a, b);
						stackVector.push_back(Compute(a, vectors, matrices)[0]);
						stackVector.push_back(Compute(b, vectors, matrices)[0]);
						size = (int)stackVector.size();
						if (orthogonal(stackVector[size - 2], stackVector[size - 1]))
							std::cout << "yes" << std::endl;
						else
							std::cout << "no" << std::endl;
						throw Exceptions(done);
					}
					else if (cmdCheck(temp, "angle"))
					{
						std::string a = "", b = "";
						subTwoOrder(temp, a, b);
						stackVector.push_back(Compute(a, vectors, matrices)[0]);
						stackVector.push_back(Compute(b, vectors, matrices)[0]);
						size = (int)stackVector.size();
						stackVector[size - 2] = findAngle(stackVector[size - 2], stackVector[size - 1]);
						stackVector.pop_back();
					}
					else if (cmdCheck(temp, "planeNormal"))
					{
						std::string a = "", b = "";
						subTwoOrder(temp, a, b);
						stackVector.push_back(Compute(a, vectors, matrices)[0]);
						stackVector.push_back(Compute(b, vectors, matrices)[0]);
						size = (int)stackVector.size();
						stackVector[size - 2] = planeNormal(stackVector[size - 2], stackVector[size - 1]);
						stackVector.pop_back();
					}
					else if (cmdCheck(temp, "linearIndependent"))
					{
						std::string a = "", b = "";
						subTwoOrder(temp, a, b);
						stackVector.push_back(Compute(a, vectors, matrices)[0]);
						stackVector.push_back(Compute(b, vectors, matrices)[0]);
						size = (int)stackVector.size();
						if (linearIndependent(stackVector[size - 2], stackVector[size - 1]))
							std::cout << "yes" << std::endl;
						else
							std::cout << "no" << std::endl;
						throw Exceptions(done);
					}
					else if (cmdCheck(temp, "gramSchmidt"))
					{
						std::vector<std::string> strs;
						std::vector<MyVector> vecs;
						strs = subMultiOrder(temp);
						for (int j = 0; j < (int)strs.size(); j++)
						{
							vecs.push_back(Compute(strs[j],vectors,matrices)[0]);
						}
						vecs = gramSchmidt(vecs);
						for (int j = 0; j < (int)strs.size(); j++)
						{
							std::cout << vecs[j] << std::endl;
						}
						throw Exceptions(done);
					}
					//矩陣部分
					else if (cmdCheck(temp, "rank"))
					{
						stackMatrix.push_back(Compute(subOrder(temp), vectors, matrices));
						size = (int)stackMatrix.size();
						std::cout << rank(stackMatrix[size - 1]) << std::endl;
						throw Exceptions(done);
					}
					else if (cmdCheck(temp, "transpose"))
					{
						stackMatrix.push_back(Compute(subOrder(temp), vectors, matrices));
						size = (int)stackMatrix.size();
						stackMatrix[size - 1] = transpose(stackMatrix[size - 1]);
					}
					else if (cmdCheck(temp, "linearSystem"))
					{
						std::string a = "", b = "";
						subTwoOrder(temp, a, b);
						stackMatrix.push_back(Compute(a, vectors, matrices));
						stackMatrix.push_back(Compute(b, vectors, matrices));
						size = (int)stackMatrix.size();
						stackMatrix[size - 2] = SolveLinearSystem(stackMatrix[size - 2], stackMatrix[size - 1]);
						stackMatrix.pop_back();
					}
					else if (cmdCheck(temp, "determinants"))
					{
						stackMatrix.push_back(Compute(subOrder(temp), vectors, matrices));
						size = (int)stackMatrix.size();
						std::cout << Determinants(stackMatrix[size - 1]) << std::endl;
						throw Exceptions(done);
					}
					else if (cmdCheck(temp, "inverse"))
					{
						stackMatrix.push_back(Compute(subOrder(temp), vectors, matrices));
						size = (int)stackMatrix.size();
						stackMatrix[size - 1] = Inverse(stackMatrix[size - 1]);
					}
					else if (cmdCheck(temp, "adjoint"))
					{
						stackMatrix.push_back(Compute(subOrder(temp), vectors, matrices));
						size = (int)stackMatrix.size();
						stackMatrix[size - 1] = Adjoint(stackMatrix[size - 1]);
					}
					else if (cmdCheck(temp, "leastSquare"))
					{
						std::string a = "", b = "";
						subTwoOrder(temp, a, b);
						stackMatrix.push_back(Compute(a, vectors, matrices));
						stackMatrix.push_back(Compute(b, vectors, matrices));
						size = (int)stackMatrix.size();
						stackMatrix[size - 2] = LeastSquare(stackMatrix[size - 2], stackMatrix[size - 1]);
						stackMatrix.pop_back();
					}
					else if (cmdCheck(temp, "powerMethod"))
					{
						stackMatrix.push_back(Compute(subOrder(temp), vectors, matrices));
						size = (int)stackMatrix.size();
						MyMatrix v, d;
						PowerMethod(stackMatrix[size - 1], v, d);
						std::cout << "v = " << std::endl;
						std::cout << v << std::endl;
						std::cout << "d = " << std::endl;
						std::cout << d << std::endl;
						throw Exceptions(done);
					}
				}
				//變數
				if (vectors.find(temp)!=vectors.end())
				{
					stackVector.push_back(vectors[temp]);
				}
				else if (matrices.find(temp) != matrices.end())
				{
					stackMatrix.push_back(matrices[temp]);
				}
			}
			temp = "";
		}
		else
		{
			//還沒遇到分隔符號，代表該字元與前面是一體的
			temp += s[i];
		}
	}
	if (stackVector.size() != 0)
		return stackVector[0];
	else if (stackMatrix.size() != 0)
		return stackMatrix[0];
	else
		throw Exceptions(computeError);
}

//中序轉後序的輸入運算子優先度
int operatorPriorityInInput(char c)
{
	if (c == '+' || c == '-')return 1;
	else if (c == '*' || c == '/')return 2;
	else if (c == '@')return 3;
	else if (c == '^')return 5;
	else if (c == '!')return 6;
	else if (c == ')')return 0;
	else if (c == '(')return 7;
	else return -1;
}

//中序轉後序的堆疊運算子優先度
int operatorPriorityInStack(char c)
{
	if (c == '+' || c == '-')return 1;
	else if (c == '*' || c == '/')return 2;
	else if (c == '@')return 3;
	else if (c == '^')return 4;
	else if (c == '!')return 6;
	else if (c == '(')return 0;
	else return -1;
}

//回傳是否為運算子
bool isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^' || c == '!')
		return true;
	else
		return false;
}

//判斷兩運算子是否優先
bool ispriority(char input, char stack)
{
	if (operatorPriorityInInput(input) > operatorPriorityInStack(stack))
	{
		return true;
	}
	else
		return false;
}

//中序轉後序
std::string Postorder(std::string inorder)
{
	//去除多餘的空白鍵
	for (int i = 0; i < (int)inorder.length(); i++)
	{
		if (inorder[i] == ' ')
		{
			inorder.erase(i, 1);
			i--;
		}
	}
	std::string stack;	//堆疊運算子
	std::string ans;		//後序表示法
	bool isBlank = false;	//儲存是否已經輸出分隔符號用

	for (int i = 0; i < (int)inorder.length(); i++)
	{
		//遇到特別指令，全部直接輸出直至括號為止
		if (inorder[i] == '\\')
		{
			bool isbrackets = false;
			int count = 0;
			while (isbrackets == false || count != 0)
			{
				if (inorder[i] == '(')
				{
					isbrackets = true;
					count++;
				}
				else if (inorder[i] == ')')
					count--;

				ans += inorder[i];
				i++;
			}
			ans += " ";
		}
		//如果是運算子...
		if (isOperator(inorder[i]))
		{
			isBlank = false;	//重設分隔符號

			//判別是正負號還是加減
			if (inorder[i] == '-' || inorder[i] == '+')
			{
				if (i == 0 || (isOperator(inorder[i - 1]) && inorder[i - 1] != ')'&&inorder[i - 1] != '!'))
				{
					if (inorder[i] == '-')	//如果是負號就放入@代替，正號直接無視
						stack.push_back('@');
					continue;
				}
			}
			//若運算子堆疊為空，則push
			if (stack.size() == 0)
			{
				stack.push_back(inorder[i]);
			}
			//若遇到後括號需特別處理
			else if (inorder[i] == ')')
			{
				//直到前括號出現前，把堆疊都pop出來
				while (!(stack.back() == '('))
				{
					ans += stack.back();
					ans += " ";
					stack.pop_back();
				}
				//括號不用輸出，純pop
				stack.pop_back();
			}
			//若是優先度大於堆疊中的運算子，則push進去
			else if (ispriority(inorder[i], stack.back()))
			{
				stack.push_back(inorder[i]);
			}
			//若是皆不符合，則將運算子pop出一位，直到輸入運算子優先度大於堆疊
			else
			{
				if (stack.back() != '('&&stack.back() != ')')
				{
					ans += stack.back();
					ans += " ";
				}
				stack.pop_back();
				i--;
			}
		}
		//如果是運算元，直接輸出
		else
		{
			//如果還是同一個運算元，先把空白鍵拿掉
			if (isBlank)
				ans.pop_back();
			ans += inorder[i];
			ans += " ";
			isBlank = true;
		}
	}
	//當輸入結束，將堆疊中的運算子全pop出來
	for (; !stack.empty();)
	{
		if (stack.back() != '('&&stack.back() != ')')
		{
			ans += stack.back();
			ans += " ";
		}
		stack.pop_back();
	}
	//最後如果沒有空白鍵，補上
	if (ans[(int)ans.length() - 1] != ' ')
		ans += ' ';
	return ans;
}

bool cmdCheck(std::string s, std::string cmd)
{
	for (int i = 0; i < (int)cmd.size(); i++)
	{
		if (s[i + 1] != cmd[i])
			return false;
	}
	return true;
}

std::string subOrder(std::string s)
{
	std::string ans = "";
	int i = 0;
	bool isbrackets = false;
	int count = 0;
	while (isbrackets == false || count != 0)
	{
		if (s[i] == '(')
		{
			isbrackets = true;
			count++;
		}
		else if (s[i] == ')')
			count--;
		if(isbrackets == true)
			ans += s[i];
		i++;
	}
	return ans;
}

void subTwoOrder(std::string s, std::string& ans1, std::string& ans2)
{
	int i = 0;
	bool isbrackets = false;
	bool isTwo = false;
	int count = 0;

	while (isbrackets == false || count != 0)
	{
		if (isTwo == false && count == 1 && s[i] == ',')
		{
			isTwo = true;
			i++;
			continue;
		}
		if (isbrackets == true && isTwo == false)
			ans1 += s[i];
		else if (isbrackets == true && isTwo == true && i + 1 != (int)s.size())
			ans2 += s[i];
		if (s[i] == '(')
		{
			isbrackets = true;
			count++;
		}
		else if (s[i] == ')')
			count--;
		
		i++;
	}
}

std::vector<std::string> subMultiOrder(std::string s)
{
	std::vector<std::string> ans;
	std::string temp="";
	int i = 0;
	bool isbrackets = false;
	int count = 0;

	while (isbrackets == false || count != 0)
	{
		if (i + 1 == (int)s.size())
		{
			ans.push_back(temp);
			break;
		}
		if (count == 1 && s[i] == ',')
		{
			i++;
			ans.push_back(temp);
			temp = "";
			continue;
		}
		if (isbrackets == true)
			temp += s[i];
		if (s[i] == '(')
		{
			isbrackets = true;
			count++;
		}
		else if (s[i] == ')')
			count--;

		i++;
	}
	return ans;
}

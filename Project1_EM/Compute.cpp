#include "Compute.h"
#include "Exception.h"

MyMatrix Compute(std::string s, std::map<std::string, MyVector> vectors, std::map<std::string, MyMatrix> matrices)
{
	//std::cout << Postorder(s) << std::endl;
	s = Postorder(s);

	std::vector<MyMatrix> stackMatrix;
	std::vector<MyVector> stackVector;	//�@��stack�Ω�s��B�⤸
	std::string temp = "";	//�@�ӼȦs�Ŷ�
	for (int i = 0; i < (int)s.length(); i++)
	{
		//���p�J�W���j�r��...
		if (s[i] == ' ')
		{
			//�P�_��O�_���B��l
			if ((int)temp.length() == 1 && (isOperator(temp[0]) || temp == "@"))
			{
				int size = (int)stackVector.size();
				//�x�}����
				if(size==0)
				{
					size = (int)stackMatrix.size();
					//�q���|���X��Ӽư��[�k
					if (temp == "+")
					{
						if (size < 2)
						{
							//���~�A�B�⦡�����~
							throw Exceptions(computeError);
						}
						stackMatrix[size - 2] = add(stackMatrix[size - 2], stackMatrix[size - 1]);
						stackMatrix.pop_back();
						size--;
					}
					//�q���|���X��Ӽư���k
					else if (temp == "-")
					{
						if (size < 2)
						{
							//���~�A�B�⦡�����~
							throw Exceptions(computeError);
						}
						stackMatrix[size - 2] = sub(stackMatrix[size - 2], stackMatrix[size - 1]);
						stackMatrix.pop_back();
						size--;
					}
					//�q���|���X��Ӽư����k
					else if (temp == "*")
					{
						if (size < 2)
						{
							//���~�A�B�⦡�����~
							throw Exceptions(computeError);
						}
						stackMatrix[size - 2] = mul(stackMatrix[size - 2], stackMatrix[size - 1]);
						stackMatrix.pop_back();
						size--;
					}
					//�q���|���X��Ӽư����k
					else if (temp == "/")
					{
						//���~�A�B�⦡�����~
						throw Exceptions(computeError);
					}
					//�q���|���X�@�Ӽƥ[�t��
					else if (temp == "@")
					{
						//���~�A�B�⦡�����~
						throw Exceptions(computeError);
					}
					//�q���|���X��Ӽư�����
					else if (temp == "^")
					{
						//���~�A�B�⦡�����~
						throw Exceptions(computeError);
					}
					//�q���|���X�@�Ӽư����h
					else if (temp == "!")
					{
						//���~�A�B�⦡�����~
						throw Exceptions(computeError);
					}
				}
				else
				{
					//�V�q����
					//�q���|���X��Ӽư��[�k
					if (temp == "+")
					{
						if (size < 2)
						{
							//���~�A�B�⦡�����~
							throw Exceptions(computeError);
						}
						stackVector[size - 2] = add(stackVector[size - 2], stackVector[size - 1]);
						stackVector.pop_back();
						size--;
					}
					//�q���|���X��Ӽư���k
					else if (temp == "-")
					{
						if (size < 2)
						{
							//���~�A�B�⦡�����~
							throw Exceptions(computeError);
						}
						stackVector[size - 2] = sub(stackVector[size - 2], stackVector[size - 1]);
						stackVector.pop_back();
						size--;
					}
					//�q���|���X��Ӽư����k
					else if (temp == "*")
					{
						if (size < 2)
						{
							//���~�A�B�⦡�����~
							throw Exceptions(computeError);
						}
						stackVector[size - 2] = dot(stackVector[size - 2], stackVector[size - 1]);
						stackVector.pop_back();
						size--;
					}
					//�q���|���X��Ӽư����k
					else if (temp == "/")
					{
						//���~�A�B�⦡�����~
						throw Exceptions(computeError);
					}
					//�q���|���X�@�Ӽƥ[�t��
					else if (temp == "@")
					{
						//���~�A�B�⦡�����~
						throw Exceptions(computeError);
					}
					//�q���|���X��Ӽư�����
					else if (temp == "^")
					{
						//���~�A�B�⦡�����~
						throw Exceptions(computeError);
					}
					//�q���|���X�@�Ӽư����h
					else if (temp == "!")
					{
						//���~�A�B�⦡�����~
						throw Exceptions(computeError);
					}
				}
				
			}
			//���O�B��Ÿ��A�N��䬰�B�⤸
			//�N���Ʃ�J���|��
			//���ˬd�O�_���ܼ�
			else
			{
				//�S����O
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
						stackVector[size - 1] = length(stackVector[size - 1]);
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
					//�x�}����
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
				//�ܼ�
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
			//�٨S�J����j�Ÿ��A�N��Ӧr���P�e���O�@�骺
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

//�������Ǫ���J�B��l�u����
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

//�������Ǫ����|�B��l�u����
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

//�^�ǬO�_���B��l
bool isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^' || c == '!')
		return true;
	else
		return false;
}

//�P�_��B��l�O�_�u��
bool ispriority(char input, char stack)
{
	if (operatorPriorityInInput(input) > operatorPriorityInStack(stack))
	{
		return true;
	}
	else
		return false;
}

//��������
std::string Postorder(std::string inorder)
{
	//�h���h�l���ť���
	for (int i = 0; i < (int)inorder.length(); i++)
	{
		if (inorder[i] == ' ')
		{
			inorder.erase(i, 1);
			i--;
		}
	}
	std::string stack;	//���|�B��l
	std::string ans;		//��Ǫ�ܪk
	bool isBlank = false;	//�x�s�O�_�w�g��X���j�Ÿ���

	for (int i = 0; i < (int)inorder.length(); i++)
	{
		//�J��S�O���O�A����������X���ܬA������
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
		//�p�G�O�B��l...
		if (isOperator(inorder[i]))
		{
			isBlank = false;	//���]���j�Ÿ�

			//�P�O�O���t���٬O�[��
			if (inorder[i] == '-' || inorder[i] == '+')
			{
				if (i == 0 || (isOperator(inorder[i - 1]) && inorder[i - 1] != ')'&&inorder[i - 1] != '!'))
				{
					if (inorder[i] == '-')	//�p�G�O�t���N��J@�N���A���������L��
						stack.push_back('@');
					continue;
				}
			}
			//�Y�B��l���|���šA�hpush
			if (stack.size() == 0)
			{
				stack.push_back(inorder[i]);
			}
			//�Y�J���A���ݯS�O�B�z
			else if (inorder[i] == ')')
			{
				//����e�A���X�{�e�A����|��pop�X��
				while (!(stack.back() == '('))
				{
					ans += stack.back();
					ans += " ";
					stack.pop_back();
				}
				//�A�����ο�X�A��pop
				stack.pop_back();
			}
			//�Y�O�u���פj����|�����B��l�A�hpush�i�h
			else if (ispriority(inorder[i], stack.back()))
			{
				stack.push_back(inorder[i]);
			}
			//�Y�O�Ҥ��ŦX�A�h�N�B��lpop�X�@��A�����J�B��l�u���פj����|
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
		//�p�G�O�B�⤸�A������X
		else
		{
			//�p�G�٬O�P�@�ӹB�⤸�A����ť��䮳��
			if (isBlank)
				ans.pop_back();
			ans += inorder[i];
			ans += " ";
			isBlank = true;
		}
	}
	//���J�����A�N���|�����B��l��pop�X��
	for (; !stack.empty();)
	{
		if (stack.back() != '('&&stack.back() != ')')
		{
			ans += stack.back();
			ans += " ";
		}
		stack.pop_back();
	}
	//�̫�p�G�S���ť���A�ɤW
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
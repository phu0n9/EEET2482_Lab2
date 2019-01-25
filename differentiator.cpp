#include "pch.h"
#include "differentiator.h"

using namespace std;

string term::addMissing(string str)
{
	if (str == "")
	{
		cout << "No input found." << endl;
		exit(1);
	}

	int strSize = str.size();
	int k = 1;
	int space = 0;
	for (int i = 1; i < strSize; ++i)
	{
		if (str[i] == '+' || str[i] == '-')
		{
			k++;
		}
	}

	int monoms = k;
	if (isdigit(str[0]))
	{
		str.insert(0, "+");
	}
	if (str[0] == 'x' || str[0] == 'l' || str[0] == 'c' || str[0] == 's' || str[0] == 'e')
	{
		str.insert(0, "+");
	}
	str.append("+");
	strSize = str.size();

	k = 0;
	int j = 0;
	string monomStr[MAX];
	for (int i = 1; i < strSize; ++i)
	{
		if (str[i] == '+' || str[i] == '-')
		{
			monomStr[k++] = str.substr(j, i - j);
			j = i;
		}
	}

	string tempStr;
	for (int i = 0; i < monoms; ++i)
	{
		if (monomStr[i][1] == 'x')
		{
			monomStr[i].insert(1, "1*");
		}
		if (monomStr[i][1] == 'l' || monomStr[i][1] == 'c' || monomStr[i][1] == 's' || monomStr[i][1] == 'e')
		{
			monomStr[i].insert(1, "1*");
		}
		int len = monomStr[i].size();
		for (int j = 1; j < len; ++j)
		{
			if (monomStr[i][j] == 'x')
			{
				if (j == len - 1)
				{
					monomStr[i].append("^1");
				}
				break;
			}
			if (isdigit(monomStr[i][j]) && monomStr[i][j + 1] == '\0')
			{
				monomStr[i].append("*x^0");
			}
			if (monomStr[i][j] == '(' && monomStr[i][j + 1] == 'x')
			{
				monomStr[i].insert(j + 1, "1*");
			}
		}
		tempStr += monomStr[i];
	}

	string finalStr = tempStr;

	string token;
	for (unsigned int i = 0; i < finalStr.size(); i++)
	{
		if ((finalStr[i] == '-') || (finalStr[i] == '+'))
		{
			token = finalStr.insert(i++, "#");
		}
	}
	return token;
}

string term::separateTerms(string str)
{
	string token = addMissing(str);
	if (token[0] == '#')
	{
		token.erase(token.begin());
	}
	strTerm = token;
	return strTerm;
}

term *createTerm(string str)
{
	term *thisTerm = NULL;
	bool flag = false;
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (str.substr(i, 3) == "*x^")
		{
			thisTerm = new powTerm(str);
			flag = true;
		}
		if (str.substr(i, 4) == "*x^1")
		{
			thisTerm = new LinearTerm(str);
			flag = true;
		}
		if (str.substr(i, 4) == "*x^0")
		{
			thisTerm = new ConstantTerm(str);
			flag = true;
		}
		if (str.substr(i, 3) == "cos")
		{
			thisTerm = new CosTerm(str);
			flag = true;
		}
		if (str.substr(i, 3) == "sin")
		{
			thisTerm = new SinTerm(str);
			flag = true;
		}
		if (str.substr(i, 8) == "cos(1*x)")
		{
			thisTerm = new CoVarTerm(str);
			flag = true;
		}
		if (str.substr(i, 8) == "sin(1*x)")
		{
			thisTerm = new SinVarTerm(str);
			flag = true;
		}
		if (str.substr(i, 5) == "log10")
		{
			thisTerm = new logarithmTerm(str);
			flag = true;
		}
		if (str.substr(i, 4) == "loge")
		{
			thisTerm = new LogarithmETerm(str);
			flag = true;
		}
		if (str.substr(i, 3) == "*e^")
		{
			thisTerm = new ExponentialTerm(str);
			flag = true;
		}
		if (str.substr(i, 8) == "*e^(1*x)")
		{
			thisTerm = new ExponentialVarTerm(str);
			flag = true;
		}
	}
	if (flag == false)
	{
		cout << "Input Error.Please try again." << endl;
		exit(1);
	}
	return thisTerm;
}

void term::printResult(term *&hd)
{
	term *crt = hd;
	string resultTemp;
	string strTemp;
	string result;

	crt = hd;
	resultTemp = crt->print();
	result = resultTemp;
	while (crt->getNext() != NULL)
	{
		crt = crt->getNext();
		strTemp = "+" + crt->print();
		result = resultTemp.append(strTemp);
	}

	for (unsigned int i = 0; i < result.length(); i++)
	{
		if (result[i] == '+' && result[i + 1] == '-')
		{
			result.erase(result.begin() + i);
		}
	}
	cout << "Result = " << result << endl;
}

void term::linkedlist(term *&head, term *&crt, string str)
{
	string tempStr = separateTerms(str);
	istringstream tok(tempStr);
	string token;
	term *differentiatorHead = NULL;
	term *differentiatorCrt = differentiatorHead;
	while (getline(tok, token, '#'))
	{
		if (head == NULL)
		{
			head = createTerm(token);
			differentiatorHead = head->differentiate();
			crt = head;
			differentiatorCrt = differentiatorHead;
		}
		else
		{
			term *store1 = createTerm(token);
			term *store2 = store1->differentiate();
			crt->setNext(store1);
			differentiatorCrt->setNext(store2);
			crt = crt->getNext();
			differentiatorCrt = differentiatorCrt->getNext();
		}
	}
	printResult(head);
}

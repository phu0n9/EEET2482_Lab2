#include "pch.h"
#include "differentiator.h"

using namespace std;

string node::setName(string str)
{
	cout << "Enter equation = ";
	cin >> str;
	if (str == "")
	{
		cout << "Please enter another input." << endl;
		return nullptr;
	}
	int strSize = str.size();
	int k = 1;
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
		if (monomStr[i][1] == 'x')
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
			if (isdigit(monomStr[i][j]) && monomStr[i][j+1] == '\0')
			{
				monomStr[i].append("*x^0");
			}
		}
		tempStr += monomStr[i];
	}
	
	string finalStr;
	if (tempStr[0] == '+')
	{
		 tempStr.erase(tempStr.begin());
	}
	finalStr = tempStr;

	string tempToken;
	string token;
	for (unsigned int i = 0; i < finalStr.size(); i++)
	{
		if ((finalStr[i] == '-')|| (finalStr[i] == '+'))
		{
			tempToken = finalStr.insert(i++, " ");
		}
	}
	if (tempToken[0] == ' ')
	{
		tempToken.erase(tempToken.begin());
	}
	token = tempToken;
	return token;
}

void node::terms(node *next)
{
	string token;
	istringstream a(setName(token));
	string temp;
	next = crt;
	while (getline(a, temp, ' '))
	{
		name = temp;
		if (crt == NULL)
		{
			crt = new node(name);
			next = crt;
			cout << "Head = " << next->getName() << endl;
		}
		else
		{
			node *store = new node(name);
			next->setNext(store);
			next = next->getNext();
			cout << "Current = " << next->getName() << endl;
		}
	}
}

void node::setReal(int real)
{
	string token;
	istringstream c(setName(token));
	node *next = crt;
	terms(next);
	while (getline(c, token, ' ') && getline(c, token, '*'))
	{
		real = stoi(token);
		a = real;
		if (next == NULL)
		{
			next = new node(a);
			cout << "Real1 = " << next->getReal() << endl;
		}
		else
		{
			node *store = new node(a);
			next->setNext(store);
			next = next->getNext();
			cout << "Real = " << next->getReal() << endl;
		}
	}
}

void node::setCoeff(int imag)
{
	string token;
	istringstream c(setName(token));
	node *next = crt;
	terms(next);
	while ((getline(c, token, '^')) || (getline(c,token,'(')) && getline(c, token, '\0'))
	{
		imag = stoi(token);
		b = imag;
		if (next == NULL)
		{
			next = new node(b);
			cout << "Imagine1 = " << next->getCoeff() << endl;
		}
		else
		{
			node *store = new node(b);
			next->setNext(store);
			next = next->getNext();
			cout << "Imagine = " << next->getCoeff() << endl;
		}
	}
}


void CosNode::forwardProp()
{
	node *next = head;
	if (next == NULL)
	{
		a = (-1)*(next->getReal()) * (next->getCoeff());
		next = new node(a);
		cout << "next.getReal1() = " << next->getReal() << endl;
	}
	else
	{
		next->setNext(next);
		next = next->getNext();
		cout << "next.getReal() = " << next->getReal() << endl;
	}
}

void CosNode::backwardProp()
{
	node *next = head;
	if (next == NULL)
	{
		next = new node(next->getReal(),next->getCoeff());
	}
	else
	{
		node *store = new node(next->getReal(), next->getCoeff());
		next->setNext(store);
		next = next->getNext();
	}
	next->backwardProp();
}

void CosNode::Debug()
{
	node *next = head;
	string temp;
	string finalTemp;
	if (next == NULL)
	{
		temp = next->getReal() + "*sin(" + next->getCoeff();
		finalTemp = temp + "*x(";
		next = new node(finalTemp);
		cout << "next.get_last_str1" << next->get_last_str() << endl;
	}
	else
	{
		node *store = new node(finalTemp);
		next->setNext(store);
		next = next->getNext();
		cout << "next.get_last_str1" << next->get_last_str() << endl;
	}
}

void SinNode::forwardProp()
{
	node *next = head;
	if (next == NULL)
	{
		a = (next->getReal()) * (next->getCoeff());
		next = new node(a);
		cout << "next.getReal1() = " << next->getReal() << endl;
	}
	else
	{
		next->setNext(next);
		next = next->getNext();
		cout << "next.getReal() = " << next->getReal() << endl;
	}
}

void SinNode::backwardProp()
{
	node *next = head;
	if (next == NULL)
	{
		next = new node(next->getReal(), next->getCoeff());
	}
	else
	{
		node *store = new node(next->getReal(), next->getCoeff());
		next->setNext(store);
		next = next->getNext();
	}
	next->backwardProp();
}

void SinNode::Debug()
{
	node *next = head;
	string temp;
	string finalTemp;
	temp = next->getReal() + "*cos(" + next->getCoeff();
	finalTemp = temp + "*x(";
	next = new node(finalTemp);
	cout << "next.get_last_str1" << next->get_last_str() << endl;
	while (next->getNext() != NULL)
	{
		node *store = new node(finalTemp);
		next->setNext(store);
		next = next->getNext();
		cout << "next.get_last_str1" << next->get_last_str() << endl;
	}
}

string sum::get_output()
{
	output->backwardProp();
	return output->get_last_str();
}

string sum::output_deb()
{
	output->Debug();
	return output->get_last_str();
}

node& cos(node& a) { return *new CosNode(&a); }

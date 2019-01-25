#include <iostream>
#include <string>
#include <sstream>
#define MAX 200

using namespace std;

class term
{
protected:
	int a;
	int b;
	term *next;
	string strTerm;
	string fnStr;
public:
	term(string str) :strTerm(str) {}
	term(int real, int imag) { a = real, b = imag; }
	term() { ; }
	~term() { ; }
	term* getNext() { return next; }
	void setNext(term *ptr) { next = ptr; }

	string addMissing(string str);
	string separateTerms(string str);
	virtual term *differentiate() { return new term(a, b); }
	virtual string print() { return fnStr; }

	void linkedlist(term *&head, term *&crt, string str);
	void printResult(term *&hd);
};
term *createTerm(string str);

class CosTerm :public term
{
public:
	CosTerm(string str)
	{
		string temp = addMissing(str);
		istringstream c(temp);
		istringstream d(temp);
		string first;
		string second;
		while ((getline(c, first, '#') && getline(c, first, '*')) && (getline(d, second, '(') && getline(d, second, ')')))
		{
			a = stoi(first);
			b = stoi(second);
		}
	}
	CosTerm() { ; }
	CosTerm(term *n) { ; }
	string print() { fnStr = to_string(a*b*(-1)) + "*sin(" + to_string(b) + "*x)"; return fnStr; }
	term *differentiate() { return new term(a*b*(-1), b); }
	~CosTerm() { ; }
};

class powTerm : public term
{
public:
	powTerm(string str)
	{
		string temp = addMissing(str);
		istringstream c(temp);
		istringstream d(temp);
		string first;
		string second;
		while ((getline(c, first, '#') && getline(c, first, '*')) && (getline(d, second, '^') && getline(d, second, ' ')))
		{
			int real = stoi(first);
			int imag = stoi(second);
			a = real;
			b = imag;
		}
	}
	powTerm() { ; }
	powTerm(term *n) { ; }
	string print() { fnStr = to_string(a*b) + "*x^" + to_string(b - 1); return fnStr; }
	term *differentiate() { return new term(a*b, b - 1); }
	~powTerm() { ; }
};

class SinTerm :public term
{
public:
	SinTerm(string str)
	{
		string temp = addMissing(str);
		istringstream c(temp);
		istringstream d(temp);
		string first;
		string second;
		while ((getline(c, first, '#') && getline(c, first, '*')) && (getline(d, second, '(') && getline(d, second, ')')))
		{
			int real = stoi(first);
			int imag = stoi(second);
			a = real;
			b = imag;
		}
	}
	SinTerm() { ; }
	SinTerm(term *n) { ; }
	string print() { fnStr = to_string(a*b) + "*cos(" + to_string(b) + "*x)"; return fnStr; }
	term *differentiate() { return new term(a*b, b); }
	~SinTerm() { ; }
};

class logarithmTerm : public term
{
public:
	logarithmTerm(string str)
	{
		string temp = addMissing(str);
		istringstream c(temp);
		string first;
		while ((getline(c, first, '#') && getline(c, first, '*')))
		{
			a = stoi(first);
			b = 0;
		}
	}
	logarithmTerm() { ; }
	logarithmTerm(term *n) { ; }
	string print() { fnStr = to_string(a) + "/x*" + "ln(10)"; return fnStr; }
	term *differentiate() { return new term(a, b); }
	~logarithmTerm() { ; }
};

class LogarithmETerm :public term
{
public:
	LogarithmETerm(string str)
	{
		string temp = addMissing(str);
		istringstream c(temp);
		string first;
		while ((getline(c, first, '#') && getline(c, first, '*')))
		{
			a = stoi(first);
			b = 0;
		}
	}
	LogarithmETerm() { ; }
	LogarithmETerm(term *n) { ; }
	string print() { fnStr = to_string(a) + "/x"; return fnStr; }
	term *differentiate() { return new term(a, b); }
	~LogarithmETerm() { ; }
};

class ExponentialTerm :public term
{
public:
	ExponentialTerm(string str)
	{
		string temp = addMissing(str);
		istringstream c(temp);
		istringstream d(temp);
		string first;
		string second;
		while ((getline(c, first, '#') && getline(c, first, '*')) && (getline(d, second, '(') && getline(d, second, ')')))
		{
			a = stoi(first);
			b = stoi(second);
		}
	}
	ExponentialTerm() { ; }
	ExponentialTerm(term *n) { ; }
	string print() { fnStr = to_string(a*b) + "*e^(" + to_string(b) + "*x)"; return fnStr; }
	term *differentiate() { return new term(a*b, b); }
	~ExponentialTerm() { ; }
};

class ExponentialVarTerm :public term
{
public:
	ExponentialVarTerm(string str)
	{
		string temp = addMissing(str);
		istringstream c(temp);
		string first;
		while ((getline(c, first, '#') && getline(c, first, '*')))
		{
			a = stoi(first);
			b = 1;
		}
	}
	ExponentialVarTerm() { ; }
	ExponentialVarTerm(term *n) { ; }
	string print() { fnStr = to_string(a) + "*e^(x)"; return fnStr; }
	term *differentiate() { return new term(a, b); }
	~ExponentialVarTerm() { ; }
};

class LinearTerm :public term
{
public:
	LinearTerm(string str)
	{
		string temp = addMissing(str);
		istringstream c(temp);
		string first;
		while ((getline(c, first, '#') && getline(c, first, '*')))
		{
			a = stoi(first);
			b = 0;
		}
	}
	LinearTerm() { ; }
	LinearTerm(term *n) { ; }
	string print() { fnStr = to_string(a); return fnStr; }
	term *differentiate() { return new term(a, b); }
	~LinearTerm() { ; }
};

class ConstantTerm :public term
{
public:
	ConstantTerm(string str)
	{
		string temp = addMissing(str);
		a = 0;
		b = 0;
	}
	ConstantTerm() { ; }
	ConstantTerm(term *n) { ; }
	string print() { fnStr = to_string(0); return fnStr; }
	term *differentiate() { return new term(a, b); }
	~ConstantTerm() { ; }
};

class CoVarTerm :public term
{
public:
	CoVarTerm(string str)
	{
		string temp = addMissing(str);
		istringstream c(temp);
		string first;
		while ((getline(c, first, '#') && getline(c, first, '*')))
		{
			a = stoi(first);
			b = 0;
		}
	}
	CoVarTerm() { ; }
	CoVarTerm(term *n) { ; }
	string print() { fnStr = to_string(a*(-1)) + "*sin(x)"; return fnStr; }
	term *differentiate() { return new term(a*(-1), b); }
	~CoVarTerm() { ; }
};

class SinVarTerm :public term
{
public:
	SinVarTerm(string str)
	{
		string temp = addMissing(str);
		istringstream c(temp);
		string first;
		while ((getline(c, first, '#') && getline(c, first, '*')))
		{
			a = stoi(first);
			b = 0;
		}
	}
	SinVarTerm() { ; }
	SinVarTerm(term *n) { ; }
	string print() { fnStr = to_string(a) + "*cos(x)"; return fnStr; }
	term *differentiate() { return new term(a, b); }
	~SinVarTerm() { ; }
};
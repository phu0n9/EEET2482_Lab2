#include <iostream>
#include <string>
#include <sstream>
#define MAX 200

using namespace std;

class node
{
protected:
	int a;
	int b;
	node *crt;
	string name;
	string lastStr;
public:
	node(string str) :a(0), b(0), name(str) {}
	node(int real, int imag) { a = real, b = imag, crt = NULL; }
	node(int x) { a = x, crt = NULL; }
	node() { ; }
	~node() { ; }
	node* getNext() { return crt; }
	void setNext(node *ptr) { crt = ptr; }
	int getReal() { return a; }
	void setReal(int real);
	int getCoeff() { return b; }
	void setCoeff(int imag);
	string setName(string str);
	string getName() { return name; }

	void terms(node *next);
	virtual void forwardProp() { return; }
	virtual void backwardProp() { return; }
	virtual void Debug() { return; }

	string get_last_str() { return lastStr; }
	void set_last_str(string str) { lastStr = str; }
};

class UnaryNode:public node
{
protected:
	node *head;
public:
	UnaryNode() { ; }
	UnaryNode(node *frt,string str): node(str),head(frt){ }
	~UnaryNode(){;}
	virtual void forwardProp() = 0;
	virtual void backwardProp() = 0;
		
	//Debugging
	virtual void Debug() = 0;
};

class BinaryNode : public node
{
private:
	node* in_1;
	node* in_2;
public:
	BinaryNode(node* a, node* b, string str) :node(str), in_1(a), in_2(b) {}
	~BinaryNode() { ; }
	virtual void forwardProp() = 0;
	virtual void backwardProp() = 0;

	//Debugging
	virtual void Debug() = 0;
};

class CosNode : public UnaryNode 
{
public:
	CosNode(node* a) :UnaryNode(a, string("cos")) {}

	void forwardProp();
	void backwardProp();

	void Debug();
};

class SinNode : public UnaryNode
{
public:
	SinNode(node* a) :UnaryNode(a, string("sin")) {}

	void forwardProp();
	void backwardProp();

	void Debug();
};



class sum :public node
{
public:
	sum() { ; }
	~sum() { output->~node(); output = nullptr; }
	string output_deb();
	
private:
	node *output;
};
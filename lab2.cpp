#include "pch.h"
#include "differentiator.h"

using namespace std;

int main()
{
	node *test = new node;
	test->forwardProp();
	test->backwardProp();
	test->Debug();
	test->get_last_str();
	delete test;
	return 0;
}
#include "pch.h"
#include "differentiator.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 3 && argc > 1)
	{
		string temp(argv[1]);
		string str = temp;
		term *head = NULL;
		term *crt = head;
		term *test = new term;
		test->linkedlist(head, crt, str);
		delete test;
	}
	else if (argc == 1)
	{
		cout << "LABORATORY GROUP 06 " << endl;
		cout << "s3695662, s3695662@rmit.edu.vn, Phuong Anh, Nguyen Huynh" << endl;
		return 0;
	}
	else
	{
		cout << "Wrong input arguement." << endl;
		return 0;
	}
	return 0;
}
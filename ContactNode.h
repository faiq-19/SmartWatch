#pragma once
#include<iostream>
using namespace std;
class ContactNode
{
public:
	string name;
	string phone;
	ContactNode* next;
	int index;

	ContactNode();
	ContactNode(string name, string phone, int index);
};


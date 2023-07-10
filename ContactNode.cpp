#include "ContactList.h"
#include "ContactNode.h"
#include<iostream>
using namespace std;

ContactNode::ContactNode()
{
	next = NULL;
	name = "\0";
	phone = "\0";
	index = 0;
}

ContactNode::ContactNode(string name, string phone, int index)
{
	this->name = name;
	this->phone = phone;
	this->index = index;
}
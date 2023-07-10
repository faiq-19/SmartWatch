#pragma once
#include "ContactNode.h"

class ContactList
{
public:
	ContactNode* head;

	ContactList();
	ContactList(const ContactList&);
	ContactList Menu(ContactList&);
	void addContact(string name, string phone);
	void addContact();
	void sort();
private:
	ContactNode* middle(ContactNode*, ContactNode*);
public:
	ContactNode* searchContact(string name);
	ContactNode* searchContact(int index);
	void deleteContact(string name);
	void editContact(string name, string phone);
};
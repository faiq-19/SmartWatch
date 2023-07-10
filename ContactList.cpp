#include "ContactList.h"
#include "ContactNode.h"
#include <conio.h>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

void gotoxy(int, int);
void arrowHere(int, int);
void WriteContacts(ContactList);

ContactList::ContactList(const ContactList &obj)
{
	head = obj.head;
}

ContactList ContactList::Menu(ContactList& Cl)
{
	int position = 1;
	int keyPressed = 0;

	while (keyPressed != 13) {

		gotoxy(0, 6);

		cout << "\n\n\n\n--------CONTACTS-------|\n\n";
		arrowHere(1, position); cout << " ADD CONTACT" << endl;
		arrowHere(2, position); cout << " EDIT CONTACT" << endl;
		arrowHere(3, position); cout << " DELETE CONTACT" << endl;
		arrowHere(4, position); cout << " SEARCH CONTACT" << endl;
		arrowHere(5, position); cout << " DISPLAY CONTACTS" << endl;
		arrowHere(6, position); cout << " SAVE CONTACTS" << endl;
		arrowHere(7, position); cout << " EXIT" << endl;


		keyPressed = _getch();

		if (keyPressed == 80 && position != 7) {
			position++;
		}
		else if (keyPressed == 72 && position != 1) {
			position--;
		}
		else {
			position = position;
		}

		system("cls");
	}

	string name, phone;
	int index, choice;
	ContactNode* temp = Cl.head;
	ContactNode* searched = NULL;

	switch (position) {

	case 1:
		system("cls");
		Cl.addContact();
		break;

	case 2:
		system("cls");
		cout << "---------EDIT CONTACT--------" << endl << endl;

		cout << "Enter Name:";
		getline(cin, name);

		cout << "Enter Phone Number:";
		getline(cin, phone);

		Cl.editContact(name, phone);
		break;

	case 3:
		system("cls");
		cout << "---------DELETE CONTACT--------" << endl << endl;

		cout << "Enter Name:";
		getline(cin, name);

		Cl.deleteContact(name);
		break;

	case 4:
		system("cls");

		cout << "---------SEARCH CONTACT--------" << endl << endl;

		cout << "1. Name\n2. Index" << endl;
		cout << "Enter Choice:";
		cin >> choice;

		if (choice == 1)
		{
			cout << "Enter Name:";
			cin >> name;

			searched = Cl.searchContact(name);

			cout << searched->index << ". " << searched->name << " - " << searched->phone << endl;
		}
		else if (choice == 2)
		{
			cout << "\nEnter Index:";
			cin >> index;

			searched = Cl.searchContact(index);

			cout << searched->index << ". " << searched->name << " - " << searched->phone << endl;
		}
		else
		{
			cout << "Invalid Choice" << endl;
		}
		break;

	case 5:
		system("cls");
		while (temp != NULL)
		{
			cout << temp->index << ". " << temp->name << " - " << temp->phone << endl;
			temp = temp->next;
		}
		break;

	case 6:
		WriteContacts(Cl);
		break;

	case 7:
		WriteContacts(Cl);
		return Cl;
		break;

	default:
		WriteContacts(Cl);
		return Cl;
		break;
	}
	Menu(Cl);
}

void ContactList::addContact(string name, string phone)
{
	static int index = 0;

	if (phone.length() != 11 && phone[0] != 0)
	{
		cout << "Invalid input Contact not created." << endl << endl;
		return;
	}

	ContactNode* n = new ContactNode(name, phone, ++index);

	if (head == NULL)
	{
		head = n;
		return;
	}
	ContactNode* temp = head;

	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = n;
}

void ContactList::addContact()
{
	static int index = 0;
	string name, phone;

	cout << "---------ADD CONTACT--------" << endl << endl;

	cout << "Enter Name:";
	getline(cin, name);

	cout << "Enter Phone Number:";
	getline(cin, phone);

	if (phone.length() != 11 && phone[0] != 0)
	{
		cout << "Invalid input Contact not created." << endl << endl;
		addContact();
	}

	ContactNode* n = new ContactNode(name, phone, ++index);

	if (head == NULL)
	{
		head = n;
		return;
	}
	ContactNode* temp = head;

	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = n;

	cout << "\nContact Added Successfuly" << endl;

	sort();
}

void ContactList::sort()
{
	ContactNode* first = head;
	ContactNode* second = head;
	string name_t, phone_t;

	while (first != NULL)
	{
		while (second != NULL)
		{
			if (first->name[0] > second->name[0])
			{
				name_t = first->name;
				first->name = second->name;
				second->name = name_t;

				phone_t = first->phone;
				first->phone = second->phone;
				second->phone = phone_t;
			}
			second = second->next;
		}
		first = first->next;
		second = first;
	}
}

 ContactNode* ContactList:: middle(ContactNode* start, ContactNode* last)
{
	if (start == NULL)
		return NULL;

	ContactNode* slow = start;
	ContactNode* fast = start->next;

	while (fast != last)
	{
		fast = fast->next;
		if (fast != last)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}

	return slow;
}

ContactNode* ContactList::searchContact(string name) {

	ContactNode* temp = head;

	while (temp != NULL)
	{
		if (temp->name == name)
		{
			return temp;
		}

		temp = temp->next;
	}
	return NULL;
}

ContactNode* ContactList::searchContact(int index) {

		ContactNode* start = head;
		ContactNode* last = NULL;

	do
	{
		ContactNode* mid = middle(start, last);

		if (mid == NULL)
			return NULL;

		if (mid->index == index)
			return mid;

		else if (mid->index < index)
			start = mid->next;

		else
			last = mid;

	} while (last == NULL || last != start);

	return NULL;
}

void ContactList::deleteContact(string name) {

	ContactNode* temp = head;
	ContactNode* prev = NULL;

	while (temp->name != name)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
	{
		cout << "Key Not Found" << endl;
	}
	prev->next = temp->next;

	delete temp;

}
void ContactList::editContact(string name, string phone) {
	string a = "";
	if (head == NULL)
	{
		cout << "no contacts in list";
		return;
	}
	ContactNode* temp = head;

	if (name == "\0") {
		while (temp->phone != phone)
		{
			temp = temp->next;
		}
		cout << "input name and phone number:";
		cin >> temp->name >> temp->phone;
	}
	if (phone == "\0") {
		while (temp->name != name)
		{
			temp = temp->next;
		}
		cout << "input name and phone number:";
		cin >> temp->name >> temp->phone;
	}
	else {
		while (temp->name != name)
		{
			temp = temp->next;
		}
		cout << "input name and phone number:";
		cin >> temp->name >> temp->phone;
	}
}


ContactList::ContactList()
{
	head = NULL;
}
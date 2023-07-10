#include "ChatBox.h"
#include "ContactList.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>
#include "ContactNode.h"
using namespace std;

void gotoxy(int, int);
void arrowHere(int, int);
void DisplayTime();

ContactNode* ChatBox :: Login(ContactList Cl)
{
	int position = 1;
	int keyPressed = 0;

	while (!_kbhit())
	{
		DisplayTime();
	}

	while (keyPressed != 13) {

		system("cls");

		gotoxy(0, 2);

		cout << "\n\n--------MENU--------|\n\n";
		arrowHere(1, position); cout << " LOGIN" << endl;
		arrowHere(2, position); cout << " ADD CONTACT" << endl;
		arrowHere(3, position); cout << " POWER OFF" << endl;

		keyPressed = _getch();

		if (keyPressed == 80 && position != 3) {
			position++;
		}
		else if (keyPressed == 72 && position != 1) {
			position--;
		}
		else {
			position = position;
		}
	}

	string name, phone;

	switch (position) {

	case 1:
		system("cls");

		cout << "LOGIN" << endl << endl;

		cout << "Enter Name:";
		getline(cin, name);
		
		cout << "Enter Phone:";
		getline(cin, phone);

		break;

	case 2:
		system("cls");
		return NULL;
		break;

	case 3:
		exit(0);
		break;

	default:
		exit(0);
		break;
	}

	//From here

	ContactNode* temp = Cl.head;

	while (temp->next != NULL)
	{
		if (temp->name == name)
		{
			break;
		}
		temp = temp->next;
	}

	//TO here will be the use of search fun() binary Search

	if (name == temp->name)
	{
		cout << "Logged In" << endl;
		cout << "Welcome " << temp->name << endl;
	}
	else
	{
		system("cls");
		Login(Cl);
	}
	return temp;
}

void ChatBox::Messenger(ContactNode *logged, ContactList list)
{
	system("cls");

	gotoxy(0, 1);

	cout << "Welcome : " << logged->name << endl;
	cout << "\nWho do you want to chat to?" << endl;

	ContactNode* temp = list.head;
	int index = 1;

	while (temp != NULL)
	{
		cout << temp->index << ". " << temp->name << endl;
		temp = temp->next;
	}
	temp = list.head;

	int choice;

	cout << "\nEnter your choice:";
	cin >> choice;

	while (temp != NULL)
	{
		if (temp->index == choice)
		{
			Chat(logged, temp);
			break;
		}
		temp = temp->next;
	}
	Login(list);
}

void ChatBox::Chat(ContactNode *logged, ContactNode *contact)
{
	system("cls");

	int x = 0, y1 = 2, y2 = 1;
	fstream file_sender;
	fstream file_reciever;
	char task;
	string message;
	string readsender;
	string readreciever;
	
	string var1 = "F:\\Study Material\\Semester 3\\DS\\DS Project\\Smart Watch\\Contacts\\Chat" + logged->name + contact->name + ".txt";
	string var2 = "F:\\Study Material\\Semester 3\\DS\\DS Project\\Smart Watch\\Contacts\\Chat" + contact->name + logged->name + ".txt";

	while (1)
	{
		cout << contact->name << "(online)" << endl;

		file_sender.open(var1, ios::app | ios::out | ios::in);
		file_reciever.open(var2, ios::app | ios::out | ios::in);

		gotoxy(40, 2);
		
		while (!_kbhit())
		{
			while (!file_sender.eof())
			{
				gotoxy(5, y1++);
				getline(file_sender, readsender);
				cout << readsender;
			}
			while (!file_reciever.eof())
			{
				gotoxy(40, y2++);
				getline(file_reciever, readreciever);
				cout << readreciever;
			}
			y1 = 2;
			y2 = 1;

			gotoxy(20, 20);
			cout << "Press F1 to send a message.";
			gotoxy(20, 21);
			cout << "Press F2 to Return!";

			file_sender.close();
			file_reciever.close();

			file_sender.open(var1, ios::app | ios::out | ios::in);
			file_reciever.open(var2, ios::app | ios::out | ios::in);
		}

		task = _getche();

		if (task == 59)
		{
			gotoxy(20, 19);
			cout << "Chat:";
			cin.ignore();
			getline(cin, message);
			file_sender << message << endl;
			system("cls");
		}
		else if (task == 60)
		{
			return;
		}

		file_sender.close();
		file_reciever.close();
	}
}
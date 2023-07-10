#include <iostream>
#include "ChatBox.h"
#include "ContactList.h"
#include <conio.h>
#include <Windows.h>
#include "ContactNode.h"
#include <fstream>
#include <string>
using namespace std;

void gotoxy(int, int);
void arrowHere(int, int);
void DisplayTime();
ContactList ReadContacts(ContactList);
void WriteContacts(ContactList);

class Watch
{
	void Menu(ContactList, ChatBox, ContactNode*);
public:
	void Login();
};

// Maria (21K-3377) - ContactList
// Jawwad (21K-3461) - ContactList
// Faiq (21K-4665) - ChatBox

int main()
{
	Watch W;

	W.Login();
}

ContactList ReadContacts(ContactList Cl)
{
	ifstream offile("Contacts.txt", ios::out);

	string name;
	string phone;
	string conc;
	int i = 0;

	while (!offile.eof())
	{
		getline(offile, conc);

		if (conc != "")
		{
			if (conc[0] == '0')
			{
				phone = conc;
			}
			if (conc[0] > 'A' && conc[0] < 'z')
			{
				name = conc;
			}

			i++;

			if (i % 2 == 0)
			{
				Cl.addContact(name, phone);
			}
		}
	}

	offile.close();

	return Cl;
}

void WriteContacts(ContactList Cl)
{
	ofstream ifile("F:\\Study Material\\Semester 3\\DS\\DS Project\\Smart Watch\\Contacts\\Contacts.txt", ios::trunc);
	ifile.close();

	ofstream iffile("F:\\Study Material\\Semester 3\\DS\\DS Project\\Smart Watch\\Contacts\\Contacts.txt", ios::ate);

	ContactNode* temp = Cl.head;

	while (temp != NULL)
	{
		iffile << temp->name << endl;
		iffile << temp->phone << endl;
		temp = temp->next;
	}

	iffile.close();
}

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Watch::Login()
{
	ContactList Cl;
	ChatBox Cb;
	ContactNode *logged = NULL;

	Cl = ReadContacts(Cl);

	while (logged == NULL)
	{
		logged = Cb.Login(Cl);

		if (logged == NULL)
		{
			Cl.addContact();
			system("cls");
		}
	}
	Menu(Cl, Cb, logged);
	WriteContacts(Cl);
}

void Watch :: Menu(ContactList Cl, ChatBox Cb, ContactNode* logged)
{
	int position = 1;
	int keyPressed = 0;

	while (keyPressed != 13) {

		system("cls");

		cout << logged->name << " (online)" << endl;

		gotoxy(0, 2);

		cout << "\n--------MENU-------|\n\n";	
		arrowHere(1, position); cout << " MESSENGER" << endl;
		arrowHere(2, position); cout << " CONTACTS" << endl;
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

	switch (position) {

	case 1:
		Cb.Messenger(logged, Cl);
		break;

	case 2:
		system("cls");
		Cl = Cl.Menu(Cl);
		break;

	case 3:
		return;
		break;

	default:
		return;
		break;
	}
}

void arrowHere(int realPosition, int arrowPosition)
{
	if (realPosition == arrowPosition) {
		cout << " ----> ";
	}
	else {
		cout << "     ";
	}
}

void DisplayTime()
{
	time_t t = time(NULL);

	gotoxy(0, 5);

	cout << ctime(&t);
}
#pragma once
#include "ContactNode.h"
#include "ContactList.h"

class ChatBox
{
public:
	void Messenger(ContactNode*, ContactList);
	ContactNode* Login(ContactList);
private:
	void Chat(ContactNode*, ContactNode*);
};
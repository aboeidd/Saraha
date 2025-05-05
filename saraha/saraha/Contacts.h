#pragma once
#include "Contacts.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <windows.h>
#include "Message.h"
using namespace std;
class Contacts
{
public:
	int id;
	Contacts(int id) : id(id) {}
	bool operator==(const Contacts& other) const {
		return this->id == other.id;
	}

};

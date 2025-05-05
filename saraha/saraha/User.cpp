#include "User.h"
#include "Messages.h"
#include "Contacts.h"
#include <iostream>
#include "Message.h"
#include<algorithm>
#include <windows.h>
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
using namespace std;
#define el "\n"
User::User(string name, pair<string, string> account, string gender, int id) {
    this->name = name;
    this->account.first = account.first;
    this->account.second = account.second;
    this->gender = gender;
    this->id = id;
}
// placeholder
void User::setAccount(pair<string, string> accountPair) {
    account.first = accountPair.first;
    account.second = accountPair.second;
}
void User::setGender(string g) {
    if (g == "M" || g == "m")
        gender = "Male";
    else
        gender = "Female";
}
void User::setName(string n) {
    name = n;
}
void User::setId(int i) {
    id = i;
}
int User::getId()
{
    return id;
}
string User::getName() {
    return name;
}
void User::setContacts(vector<Contacts>& newContacts)
{
    contacts = newContacts;
}
vector<Contacts>& User::getContacts()
{
    return contacts;
}
void User::setblockUser(vector<int> newblockUser)
{
    blockUser = newblockUser;
}
vector<int>& User::getblockUser()
{
    return blockUser;
}
pair<string, string>& User::getAccount() {
    return account;
}

void User::displayUser() const {
    Sleep(100);
    system("cls");
    cout << "<-------------- my_Profile" << el;
    cout << "Username: " << name << el;
    cout << "Gender: " << gender << el;
    cout << "User ID: " << id << el;
    for (const auto& c : contacts)
        cout << "Contact ID: " << c.id<< el;
}

bool User::login(const string& email, const string& password) const {

    return account.first == email && account.second == hashPassword(password);
}

bool User::is_id_register(int id, vector<User*>& allUsers)
{
    for (const auto& u : allUsers) {
        if (u->getId() == id) {
            return true;
        }
    }
    return false;
}


void User::addContact(int contactID)
{
    if (id == contactID)
    {
        cout << "You can perform this action.\n";
        return;
    }
    if (!contactExists(contactID))
    {
        contacts.push_back(Contacts(contactID));
        cout << "Contact with ID " << contactID << " added for user: " << name << endl;
    }
    else {
        cout << "Contact with ID " << contactID << " already exists." << endl;
    }
}

void User::removeContact(int contactID)
{
    if (contactExists(contactID)) {
        contacts.erase(remove(contacts.begin(), contacts.end(), contactID), contacts.end());
        cout << "Contact \"" << contactID << "\" removed.\n";
    }
    else {
        cout << "Contact \"" << contactID << "\" not found.\n";
    }
}

void User::view_contact()
{
 
    if (contacts.empty()) {
        cout << "No contacts found.\n";
        return;
    }
    vector<pair<int, int>> sortedMessages;
    for (auto& pair : senderMessageCount) {
        sortedMessages.push_back(pair);
    }
    sort(sortedMessages.begin(), sortedMessages.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; 
        });

    for (auto& pair : sortedMessages) {
        cout << "Contact ID: " << pair.first << "  Messages: " << pair.second<< endl;
    }
    
}

bool User::contactExists(int contactID)
{
    for (auto& iterator : contacts) {
        if (iterator.id == contactID)
        {
            return true;
        }
    }

    return false;
}

bool User::isblock(int ID)
{
    for (auto found : blockUser)
        if (found == ID)
            return true;
    return false;
}

void User::doB_User(int Id)
{
    if (Id == id)
    {
        cout << "You can perform this action.\n";
        return;
    }
    if (!isblock(Id)) {
        blockUser.push_back(Id);
        string text = "done blocked the user : ";
        type(text);
        cout << Id << el;
      /*  cout << blockUser.size();*/
    }
    else
    {
        cout << "this user is already blocked before\n";
    }

}

void User::unBlock(int Id)
{

    for (auto it = blockUser.begin();it != blockUser.end();++it) {
        if (*it == Id) {
            blockUser.erase(it);
            type("UnBlock :");
            cout << Id << el;
            return;
        }
    }
    cout << "this User notBlocked " << Id << el;

}

void User::view_user_is_blocked()
{
    if (blockUser.empty()) {
        cout << "You have not blocked any users.\n";
        return;
    }

    cout << "Blocked Users:\n";
    for (int Id : blockUser) {
        cout << "- User ID: " << Id << endl;
    }
    
}



bool isStrongPassword(const string& password) {
    if (password.length() < 8) return false;

    bool hasLetter = false;
    bool hasDigit = false;

    for (char c : password) {
        if (isalpha(c)) hasLetter = true;
        else if (isdigit(c)) hasDigit = true;
    }

    return hasLetter && hasDigit;
}

string hashPassword(const string& password) {
    hash<string> hasher;
    return to_string(hasher(password));
}

bool isEmailValid(const string& email) {
    int atIndex = email.find('@');
    if (atIndex <= 0 || atIndex == email.length() - 1)
        return false;

    int dotIndex = email.find('.', atIndex);
    if (dotIndex == -1 || dotIndex == email.length() - 1)
        return false;

    string suffix = email.substr(email.length() - 3);
    if (suffix != "com") return false;

    if (email.size() <= 10)
        return false;

    return true;
}
void type(string text)
{
    setColor(10);
    for (int i = 0;i < text.size();i++) {
        cout << text[i];
        Sleep(100);
    }
    setColor(7);

}

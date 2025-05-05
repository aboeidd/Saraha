#pragma once
#include "Contacts.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <windows.h>
#include "Message.h"
#include <stack>
using namespace std;
class User {
private:
    pair<string, string> account; // email → hashed password
   
   /* map<int, vector<Contacts>>contacts;*/
    vector<Contacts> contacts;
    string gender;
    string name;
    int id;
    vector<int >blockUser;
public:
     map<int, int> senderMessageCount;
    User() = default;
    User(std::string name, std::pair<std::string, std::string> credentials, std::string gender, int id);
    void setAccount(pair<string, string> accountPair);
    void setGender(string g);
    void setName(string n);
    void setId(int i);
    int getId();
    string getName();
    void setContacts(vector<Contacts>& newContacts);
    vector<Contacts>& getContacts();
    void setblockUser(vector<int >newblockUser);
    vector<int>& getblockUser();

  
    pair<string, string>& getAccount();
    void displayUser() const;
    bool login(const string& email, const string& password) const;
    bool is_id_register(int id, vector<User*>& allUsers);              
    void addContact(int contactID);
    void removeContact(int contactID);
    void view_contact();
    bool contactExists(int contactID);
    bool isblock(int id);
    void doB_User(int id);
    void unBlock(int id);
    void view_user_is_blocked();


};
bool isStrongPassword(const string& password);
string hashPassword(const string& password);
bool isEmailValid(const string& email);
void type(string text);
void setColor(int color);

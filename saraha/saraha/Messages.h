#pragma once
#include "Message.h"
#include <vector>
#include <stack>
#include <map>
#include<queue>
#include<iostream>
using namespace std;
class User;

class Messages {
private:
    vector<Message> sentMessages;
    map<string, vector<Message>> receivedMessages;
    stack<Message> undoStack;
  
public:
    bool userExists = false;
    vector<string> registeredUsernames;

   
    void sendMessage(string& senderUsername, int sendrid, string& receiverUsername, string& content, vector<string>& registeredUsernames, vector<User*>& allUsers);
    bool undoLastSentMessage();
    bool is_username_regiter(string username, vector<User*>& allUsers);


    void viewSentMessages(string& currentUsername);

private:
   /* void viewReceivedMessagesFrom(string& viewerUsername, string& contactUsername);*/

public:
    void viewMyReceivedMessages(string& myUsername);

    vector<Message>& getSentMessages();
    void viewReceivedMessageFrom(int senderId, string& receiverUsername);

    map<string, vector<Message>>& getReceivedMessages();

};

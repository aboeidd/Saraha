#include "Messages.h"
#include <iostream>
#include <algorithm>
#include "User.h"
#include"Favorites.h"
using namespace std;


void Messages::sendMessage(string& senderUsername,int senderid, string& receiverUsername, string& content, vector<string>& registeredUsernames, vector<User*>& allUsers) {
    for (User* u : allUsers) {

        if (u->getName() == receiverUsername) {
            if (u->isblock(senderid))
            {
                cout << " is blocked him cannot send to the message \n";
                return;
            }
            u->senderMessageCount[senderid]++;
            u->addContact(senderid);
            break;
        }
    }

    Message msg(senderUsername, senderid,receiverUsername, content);
    sentMessages.push_back(msg);
    receivedMessages[receiverUsername].push_back(msg);
    undoStack.push(msg);
    cout << "Message sent successfully!\n";
    
}
bool Messages::undoLastSentMessage() {
    if (!undoStack.empty()) {
        Message last = undoStack.top();
        undoStack.pop();

        if (!sentMessages.empty() && sentMessages.back().getContent() == last.getContent()) {
            sentMessages.pop_back();
        }

        auto& msgs = receivedMessages[last.getReceiverUsername()];
        if (!msgs.empty() && msgs.back().getContent() == last.getContent()) {
            msgs.pop_back();
        }

        cout << "Last sent message undone.\n";
        return true;
    }
    else {
        cout << "No sent message to undo.\n";
        return false;
    }
}

bool Messages::is_username_regiter(string username, vector<User*>& allUsers)
{
    for (auto& pair1 : allUsers) {
        string name = pair1->getName();
        registeredUsernames.push_back(name);
        if (name == username) {
            return true;
              
        }
    }
    return false;

}



void Messages::viewSentMessages(string& currentUsername) {
    bool hasMessages = false;
    for (auto& msg : sentMessages) {
        if (msg.getSenderUsername() == currentUsername) {
            hasMessages = true;
            break;
        }
    }

    if (!hasMessages) {
        cout << "You haven't sent any messages yet.\n";
    }
    else {
        for (auto& msg : sentMessages) {
            if (msg.getSenderUsername() == currentUsername) {
                time_t timestamp = time(nullptr);
                char buffer[26];
                ctime_s(buffer, sizeof(buffer), &timestamp);
                string date(buffer);
                date.pop_back();
                cout << "[" << date << "] To "
                    << msg.getReceiverUsername() << ": "
                    << msg.getContent() << "\n";
            }
        }
    }
}

void Messages::viewReceivedMessageFrom(int senderId, string& receiverUsername) {
    auto it = receivedMessages.find(receiverUsername);
    if (it != receivedMessages.end()) {
        vector<Message>& msgs = it->second;
        bool found = false;
        for (Message& msg : msgs) {
            if (msg.senderId == senderId) {
                cout << "From: " << senderId << "\n";
                cout << "Message: " << msg.getContent() << "\n";
                cout << "Date: " << msg.date << "\n\n";
                found = true;
            }
        }
        if (!found)
            cout << "No messages from " << senderId << ".\n";
    }
    else {
        cout << "No messages received by " << receiverUsername << ".\n";
    }
}

void Messages::viewMyReceivedMessages(string& myUsername) {
    auto it = receivedMessages.find(myUsername);
    if (it != receivedMessages.end()) {
        cout << "Your received messages:\n";
        for (auto& msg : it->second) {
            time_t timestamp = time(nullptr);
            char buffer[26];
            ctime_s(buffer, sizeof(buffer), &timestamp);
            string date(buffer);
            date.pop_back();
            cout << "[" << date << "] " << ": " << msg.getContent() << "\n";

        }
    }
    else {
        cout << "You have not received any messages.\n";
    }
}

vector<Message>& Messages::getSentMessages() {
    return sentMessages;
}

map<string, vector<Message>>& Messages::getReceivedMessages() {
    return receivedMessages;
}

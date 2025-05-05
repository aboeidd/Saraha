#pragma once
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Message {
public:
    string senderUsername;
    int senderId;
    string date;
    string text;

private:
    string receiverUsername;
    string content;
    time_t timestamp;

public:

    Message(string sender,int sendrid, string receiver, string msg);

    string getSenderUsername() const;
    string getReceiverUsername() const;
    string getContent() const;
    time_t getTimestamp() const;
};

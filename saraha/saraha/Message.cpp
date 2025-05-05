#define _CRT_SECURE_NO_WARNINGS
#include "Message.h"
#include <ctime>

Message::Message(string sender, int sendrid, string receiver,  string msg)
    : senderUsername(sender), senderId(sendrid),receiverUsername(receiver), content(msg) {
    timestamp = time(nullptr);
    date = ctime(&timestamp);
    date.pop_back();
    text = msg;
}

string Message::getSenderUsername() const {
    return senderUsername;
}

string Message::getReceiverUsername() const {
    return receiverUsername;
}

string Message::getContent() const {
    return content;
}

time_t Message::getTimestamp() const {
    return timestamp;
}

#pragma once
#include <deque>
#include "Message.h"


class Favorites {
private:
    deque<Message> favoriteMessages;

public:
    void addToFavorites(Message& msg);
    void removeOldestFavorite();
    void viewAllFavorites();

};

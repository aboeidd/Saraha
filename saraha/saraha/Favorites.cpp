#include "Favorites.h"
#include <iostream>
#include <iomanip>
using namespace std;

void Favorites::addToFavorites(Message& msg) {
    favoriteMessages.push_back(msg);
    cout << "Message added to favorites.\n";
}

void Favorites::removeOldestFavorite() {
    if (favoriteMessages.empty()) {
        cout << "No favorite messages to remove.\n";
        return;
    }
    favoriteMessages.pop_front();
    cout << "Oldest favorite message removed.\n";
}

void Favorites::viewAllFavorites() {
    if (favoriteMessages.empty()) {
        cout << "No favorite messages yet.\n";
        return;
    }

    cout << "\n----- Favorite Messages -----\n";
    for (auto& msg : favoriteMessages) {
        time_t rawTime = msg.getTimestamp();
        struct tm timeInfo;
        localtime_s(&timeInfo, &rawTime);

        cout << " | Content: " << msg.getContent()
            << " | Timestamp: " << put_time(&timeInfo, "%Y-%m-%d %H:%M:%S") << "\n";
    }
    cout << "------------------------------\n";
}

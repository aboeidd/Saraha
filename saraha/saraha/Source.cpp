#include<iostream>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>
#include<deque>
#include<queue>
#include<set>
#include<stack>
#include<map>
#include<unordered_map>
#include <windows.h>'
#include"User.h"
#include "Messages.h"
#include "Message.h"
#include "Favorites.h"
#include <iomanip>
#include<iostream>
using namespace std;
Favorites favorites;

#define ll long long
#define Youssef ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define mod 1000000007 
#define el "\n"
using namespace std;
int currentId = 0;
/**************************************************************************************/
#define int long long
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

bool isPalindrome(string s) {
    string reversed = string(s.rbegin(), s.rend());
    return s == reversed;
}

bool checkEmailUnique(string email, unordered_map<int, User>& users) {             // that is check if the account is Already Exit
    for (auto& p : users) {
        int id = p.first;
        User& acc = p.second;
        if (acc.getAccount().first == email) {
            return false;
        }
    }
    return true;
}

User registerUser(int id, unordered_map<int, User>& users) {
    Sleep(100);
    system("cls");
    User newUser;
    string username, email, password, confirmPassword;
    cout << "<---------------registration page\n";
    cout << "Enter your username: ";
    getline(cin, username);
    newUser.setName(username);

    while (true) {
        // Password

        // Email
        while (true) {
            cout << "Enter email: ";
            cin >> email;
            if (!isEmailValid(email)) {
                cout << "Invalid email format.\n";
                continue;
            }
            break;
        }

        while (true) {
            cout << "Enter password: ";
            cin >> password;
            if (!isStrongPassword(password)) {
                cout << "Weak password. Must be at least 8 characters.\n";
                continue;
            }

            cout << "Re-enter password: ";
            cin >> confirmPassword;
            if (password != confirmPassword) {
                cout << "Passwords do not match. Try again.\n";
                continue;
            }
            break;
        }
        if (!checkEmailUnique(email, users)) {
            cout << "This account already exists.\n";
        }
        else {
            newUser.setAccount({ email, hashPassword(password) });
            break;
        }
    }

    string g;
    while (true) {
        cin.ignore();
        cout << "Enter gender (M/F): ";
        cin >> g;
        if (g == "M" || g == "F" || g == "m" || g == "f") { newUser.setGender(g); break; }
        cout << "Invalid input. Only M or F allowed.\n";
    }

    newUser.setGender(g);
    newUser.setId(id);
    setColor(10);
    string text = "Your account created successfully";
    for (int i = 0; i < text.size(); i++) {
        cout << text[i];
        Sleep(100);
    }
    setColor(7);
    cout << el;

    return newUser;
}

bool loginUser(unordered_map<int, User>& users) {
    string email, password;
    Sleep(100);
    system("cls");
    cout << "  ------------------>      Login page\n";
    while (true) {
        cout << "Enter email: ";
        getline(cin, email);
        // cin.ignore();
        if (!isEmailValid(email)) {
            cout << "Invalid email format.\n";
            continue;
        }
        break;
    }

    cout << "Password: ";
    getline(cin, password);

    for (auto& u : users) {

        const User& acc = u.second;
        if (acc.login(email, password)) {
            //setColor(2);
            string text = "Login successful.!";
            for (int i = 0; i < text.size(); i++) {
                cout << text[i];
                Sleep(100);
            }
            Sleep(300);
            system("cls");
            currentId = u.first;
            return true;
        }
    }
    setColor(10);
    string text = "Incorrect email or password.!";
    for (int i = 0; i < text.size(); i++) {
        cout << text[i];
        Sleep(100);
    }
    setColor(7);
    cout << el;
    while (true) {
        cout << "do you want try again  (Y,N)" << el;
        char choice; cin >> choice;
        choice = toupper(choice);
        if (choice == 'Y' || choice == 'N')
            if (choice == 'Y') {
                cin.ignore();
                loginUser(users);
            }
            else if (choice == 'N')
                return false;
            else
                cout << "Invalid choice" << el;

    }
    return false;
}

void showMenu() {
    Sleep(100);
    system("cls");
    cout << "\n===== Modified-Saraha =====\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    cout << "===========================\n";
}
int id = 0;

unordered_map<int, User> users;
void nextPage(int tempId)
{

    Sleep(100);
    system("cls");

    static Messages messages; // Ensure persistence
    User& currentUser = users[tempId];
    int ID;
    string choice;
    cout << "1. Profile\n";
    cout << "2. Send Message\n";
    cout << "3. Undo Last Sent Message\n";
    cout << "4. View Sent Messages\n";
    cout << "5. View All Received Messages\n";
    cout << "6. View Received Messages From Specific Contact\n";
    cout << "7. Remove Oldest Favorite Message\n";
    cout << "8. View Favorite Messages\n";
    cout << "9. remove contacts\n";
    cout << "10.search about contact\n";
    cout << "11. view contacts Users List \n";
    cout << "12. block user \n";
    cout << "13. unblock user\n";
    cout << "14. view Blocked Users List\n";
    cout << "15. Log Out\n";
    cout << "===========================\n";

    cin >> choice;
    cin.ignore();
    vector<User*> allUsers;
    for (auto it = users.begin(); it != users.end(); ++it) {
        allUsers.push_back(&(it->second));
    }


    if (choice == "1") {
        currentUser.displayUser();
        cout << "\nPress Enter to return to menu...";
        cin.get();
        nextPage(tempId);
    }
    else if (choice == "2") {
        
        string receiverUsername, content;
        cout << "Enter receiver's username: ";
        getline(cin, receiverUsername);

        if (messages.is_username_regiter(receiverUsername, allUsers)) {
            cout << "Enter your message: ";
            getline(cin, content);

            string senderUsername = currentUser.getName();
            int senderid = currentUser.getId();
            messages.sendMessage(senderUsername, senderid, receiverUsername, content, messages.registeredUsernames, allUsers);
        }
        else
        {
            cout << "This username isn't registered.\n";
        }   
            cout << "Press Enter to return to menu...\n";
            cin.get();
            nextPage(tempId);
        
    }


    else if (choice == "3") {
        messages.undoLastSentMessage();
        cout << "Press Enter to return to menu...";
        cin.get();
        nextPage(tempId);
    }

    else if (choice == "4") {
        string senderUsername = currentUser.getName();
        vector<Message>& allSent = messages.getSentMessages();
        vector< Message*> userSentMsgs;

        cout << "\nYour sent messages:\n";
        int index = 1;
        for (auto& msg : allSent) {
            if (msg.getSenderUsername() == senderUsername) {
                cout << index << ". To " << msg.getReceiverUsername()
                    << " | " << msg.getContent() << "\n";
                userSentMsgs.push_back(&msg);
                ++index;
            }
        }

        if (userSentMsgs.empty()) {
            cout << "You haven't sent any messages yet.\n";
        }
        else {
            int choice;
            cout << "\nEnter the number of the message to add to favorites (or 0 to skip): ";
            cin >> choice;
            cin.ignore();

            if (choice > 0 && choice <= userSentMsgs.size()) {
                favorites.addToFavorites(*userSentMsgs[choice - 1]);
            }
            else {
                cout << "No message added to favorites.\n";
            }
        }

        cout << "Press Enter to return to menu...";
        cin.get();
        nextPage(tempId);
    }

    else if (choice == "5") {
        string currentUsername = currentUser.getName();
        auto it = messages.getReceivedMessages().find(currentUsername);

        if (it != messages.getReceivedMessages().end() && !it->second.empty()) {
            vector<Message>& msgs = it->second;
            vector< Message*> userReceivedMsgs;

            cout << "\nYour received messages:\n";
            int index = 1;
            for (auto& msg : msgs) {
                cout << index << " | " << msg.getContent() << "\n";
                userReceivedMsgs.push_back(&msg);
                ++index;
            }

            int choice;
            cout << "\nEnter the number of the message to add to favorites (or 0 to skip): ";
            cin >> choice;
            cin.ignore();

            if (choice > 0 && choice <= userReceivedMsgs.size()) {
                favorites.addToFavorites(*userReceivedMsgs[choice - 1]);
            }
            else {
                cout << "No message added to favorites.\n";
            }
        }
        else {
            cout << "You have not received any messages.\n";
        }

        cout << "Press Enter to return to menu...";
        cin.get();
        nextPage(tempId);
    }

    else if (choice == "6") {
        int senderid;
        cout << "Enter sender id  to view received messages from: ";
        cin >> senderid;

        string currentUsername = currentUser.getName();
        messages.viewReceivedMessageFrom(senderid, currentUsername);
       
        cout << "Press Enter to return to menu...";
       
        cin.ignore();
        cin.get();
        nextPage(tempId);
    }

    else if (choice == "7") {
        favorites.removeOldestFavorite();
        cout << "Press Enter to return to menu...";
        cin.get();
        nextPage(tempId);
    }


    else if (choice == "8") {
        favorites.viewAllFavorites();
        cout << "Press Enter to return to menu...";
        cin.get();
        nextPage(tempId);
    }
    else if (choice == "9") {
        currentUser.view_contact();
        if (!currentUser.getContacts().empty())
        {
            
            cout << "enter the id want to remove him\n ";
            cin >> ID;

            if (currentUser.contactExists(ID))
            {
                currentUser.removeContact(ID);


            }
            cin.ignore();
        }
        cout << "Press Enter to return to menu...";
       
        cin.get();
        nextPage(tempId);
       
    }
    else if (choice == "10") {
        
        cout << " enter the contact is to want to search \n";
        cin >> ID;
        if (currentUser.contactExists(ID))
        {
            cout << "Contact with ID " << ID << " exists in your contact list." << endl;
        }
        else
            cout << "Contact with ID " << ID << " was not found in your contact list." << endl;
        cout << "Press Enter to return to menu...";
        cin.ignore();
        cin.get();
        nextPage(tempId);

    }
    else if (choice == "11") {
        currentUser.view_contact();
        cout << "Press Enter to return to menu...";
        cin.get();
        nextPage(tempId);

   }
    else if (choice == "12") {
        
        cout << "enter the id want to blocked him \n";
        cin >> ID;
        if (!currentUser.is_id_register(ID, allUsers))
        {
            cout << "This id isn't registered.\n";
        }
        else
        {
            currentUser.doB_User(ID);
           
        }

        cout << "Press Enter to return to menu...";
        cin.ignore();
        cin.get();
        nextPage(tempId);

    }   
    else if (choice == "13") {
        currentUser.view_user_is_blocked();
        if (!currentUser.getblockUser().empty())
        {
            
            cout << "enter the id want to unblocked him\n ";
            cin >> ID;
            currentUser.unBlock(ID);
            cin.ignore();
        }
       
        cout << "Press Enter to return to menu...";
        
        cin.get();
        nextPage(tempId);

    }
    else if (choice == "14"){
        currentUser.view_user_is_blocked();
        cout << "Press Enter to return to menu...";
        cin.get();
        nextPage(tempId);


    }
        
    else if (choice == "15") {
        cout << "Logging out...\n";
        return;

    }

    else {
      
        cout << "Invalid choice. Try again.\n";
        nextPage(tempId);
    }
}



signed main() {
    /* Welcome to my Home (*/   Youssef   /*)   */
        string choice;
    do {
        showMenu();
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == "1") {
            users[id] = registerUser(id, users);
            users[id].setId(id);
            currentId = id;
            id++;
            nextPage(currentId);

        }
        else if (choice == "2") {
            if (loginUser(users))
                nextPage(currentId);
        }
        else if (choice == "3") {
            setColor(10);
            string text = "BYE BYE!";
            for (int i = 0; i < text.size(); i++) {
                cout << text[i];
                Sleep(100);
            }
            setColor(7);

            return 0;
        }
        else {
            cout << "Invalid choice.\n";
        }
    } while (choice != "4");

    return 0;
}

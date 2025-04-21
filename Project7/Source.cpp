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
#include <windows.h>
#define ll long long
#define Youssef ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define mod 1000000007 
#define el "\n"
using namespace std;
int currentId = 0;
//
#define int long long

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

bool isPalindrome(string s) {
    string reversed = string(s.rbegin(), s.rend());
    return s == reversed;
}

// ===================== Utilities =====================   zenaib will modify on this 
bool isStrongPassword(string pass) {
    return pass.length() >= 8; // simple check
}

string hashPassword(string pass) {
    return "#" + pass + "#"; // dummy hash
}

bool isEmailValid(string email) {
    return email.find("@gmail.com") != string::npos && email.find('.') != string::npos;
}
//======================================================

//                           not Completed yet (Message)
struct Message {
    int sender;
    int receiver;
    string date;
    string text;
    
};


class User {
private:
    map<string, string> account; // email → hashed password
    vector<int> contacts;
    string gender;
    string name;
    int id = 0;
    vector<Message> messages;
    map<int, int> senderMessageCount;
public:
    bool contactExists(int contactID) {
        for (auto& iterator : contacts) {
            if (iterator== contactID)
            {
                return true;
            }
        }
          
        return false;
    }// placeholder

    void addContact(int contactID)
    {
        if (!contactExists(contactID))
            contacts.push_back(contactID);

    }
    void removeContact(int contactID) {
        if (contactExists(contactID)) {
            contacts.erase(remove(contacts.begin(), contacts.end(), contactID), contacts.end());
            cout << "Contact \"" << contactID << "\" removed.\n";
        }
        else {
            cout << "Contact \"" << contactID << "\" not found.\n";
        }
    }
    void view_contact() {
        for (auto& it : contacts)
            cout << "Contact ID: " << it << el;
        for (const auto& msg : messages) {
        if (msg.receiver == id) {
            senderMessageCount[msg.sender]++;
        }
    }
    
    
    vector<pair<int, int>> sortedSenders(senderMessageCount.begin(), senderMessageCount.end());

    sort(sortedSenders.begin(), sortedSenders.end(), [](auto& a, auto& b) {
        return a.second > b.second; 
    });

    
    cout << "Senders sorted by number of messages sent to user " << id << ":\n";
    for (const auto& entry : sortedSenders) {
        cout << "Sender ID: " << entry.first << ", Messages: " << entry.second << "\n";
    }

   
}

    
    User() = default;

    User(string name, pair<string, string> credentials, string gender, int id) {
        this->name = name;
        account.insert(credentials);
        this->gender = gender;
        this->id = id;
    }

    void setAccount(pair<string, string> accountPair) {
        account.insert(accountPair);
    }

    void setGender(string g) {
        if (g == "M" || g == "m")
            gender = "Male";
        else
            gender = "Female";
    }
    void setName(string n) { name = n; }
    void setId(int i) { id = i; }

    map<string, string>& getAccount() { return account; }

    void displayUser() const {
        cout << "Username: " << name << el;
        cout << "Gender: " << gender << el;
        cout << "User ID: " << id << el;
        for (auto& c : contacts)
            cout << "Contact ID: " << c << el;
    }

    bool login(const string& email, const string& password) const {
        auto it = account.find(email);
        return it != account.end() && it->second == hashPassword(password);
    }

    static void loadnextid() {} // placeholder
    static void savenextid() {} // placeholder
};

bool checkEmailUnique(string email, unordered_map<int, User>& users) {             // that is check if the account is Elready Exit
    for (auto& p : users) {
        int id = p.first;
        User& acc = p.second;
        if (acc.getAccount().find(email) != acc.getAccount().end()) {
            return false;
        }
    }
    return true;
}

User registerUser(int id, unordered_map<int, User>& users) {
    User newUser;
    string username, email, password, confirmPassword;

    cout << "Enter your username: ";
    getline(cin, username);
    newUser.setName(username);

    while (true) {
        // Password

        // Email
        while (true) {
            cout << "Enter email: ";
            getline(cin, email);
            if (!isEmailValid(email)) {
                cout << "Invalid email format.\n";
                continue;
            }
            break;
        }

        while (true) {
            cout << "Enter password: ";
            getline(cin, password);
            if (!isStrongPassword(password)) {
                cout << "Weak password. Must be at least 12 characters.\n";
                continue;
            }

            cout << "Re-enter password: ";
            getline(cin, confirmPassword);
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
        cout << "Enter gender (M/F): ";
        getline(cin, g);
        if (g == "M" || g == "F" || g == "m" || g == "f") { newUser.setGender(g); break; }
        cout << "Invalid input. Only M or F allowed.\n";
    }

    newUser.setGender(g);
    newUser.setId(id);

    return newUser;
}

bool loginUser(unordered_map<int, User>& users) {
    string email, password;
    cout << "                                                                                      Login page\n";
    while (true) {
        cout << "Enter email: ";
        getline(cin, email);
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
            cout << "Login successful.\n";
            currentId = u.first;
            return true;
        }
    }
    string text = "Incorrect email or password.!";
    for (int i = 0; i < text.size(); i++) {
        cout << text[i];
        Sleep(100);
    }

    return false;
}

void showMenu() {
    cout << "\n===== Modified-Saraha =====\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. logout\n";
    cout << "4. Exit\n";
    cout << "===========================\n";
}
int id = 0;
unordered_map<int, User> users;
void nextPage(int tempId)
{
    int choice;
    cout << "1. Profile\n";
    cout << "2. \n";
    cout << "3. \n";
    cout << "4. \n";
    cout << "===========================\n";

    cin >> choice;
    if (choice == 1) {
        User acc = users[tempId];
        acc.displayUser();
    }
    else {
        cout << "Invalid choice Please try again" << el;
        nextPage(tempId);
    }


}



signed main() {
    /* Welcome to my Home (/   Youssef   /)   */
    int choice;
    User::loadnextid();

    do {
        showMenu();
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            users[id] = registerUser(id, users);
            id++;
        }
        else if (choice == 2) {
            if (loginUser(users))
                nextPage(currentId);
        }
        else if (choice == 3) {
            main();
        }
        else if (choice == 4) {
            string text = "BYE BYE!";
            for (int i = 0; i < text.size(); i++) {
                cout << text[i];
                Sleep(100);
            }
            return 0;
        }
        else {
            cout << "Invalid choice.\n";
        }
    } while (choice != 3);

    User::savenextid();
    return 0;
}
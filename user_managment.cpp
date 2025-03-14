#include <iostream>
#include <string>
#include <vector>
#include <conio.h> 

#define MAX_USERS 10

struct User {
    std::string username;
    std::string password;
};

std::vector<User> users;

void registerUser();
int loginUser(); // returns the index of the user
void inputCredentials(std::string& username, std::string& password);
std::string maskedInput();

int main() {
    int option;
    while (true) {
        std::cout << "\nWelcome to User Management\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "3. Exit\n";
        std::cout << "Select an option: ";
        std::cin >> option;
        std::cin.ignore(); // Consume leftover newline

        switch (option) {
            case 1:
                registerUser();
                break;
            case 2: {
                int index = loginUser();
                if (index >= 0) {
                    std::cout << "\nLogin successful! Welcome, " << users[index].username << "!\n";
                } else {
                    std::cout << "\nLogin failed! Incorrect username or password.\n";
                }
                break;
            }
            case 3:
                std::cout << "\nExiting Program.\n";
                return 0;
            default:
                std::cout << "\nInvalid option. Please try again.\n";
                break;
        }
    }

    return 0;
}

void registerUser() {
    if (users.size() >= MAX_USERS) {
        std::cout << "\nMaximum " << MAX_USERS << " users are supported! No more registrations allowed.\n";
        return;
    }

    std::string username, password;
    std::cout << "\nRegister a new user\n";
    inputCredentials(username, password);

    // Check for duplicate username
    for (const auto& user : users) {
        if (user.username == username) {
            std::cout << "Username already taken. Please choose another.\n";
            return;
        }
    }

    users.push_back({username, password});
    std::cout << "\nRegistration successful!\n";
}

int loginUser() {
    std::string username, password;
    inputCredentials(username, password);

    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i].username == username && users[i].password == password) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

void inputCredentials(std::string& username, std::string& password) {
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    std::cout << "Enter password (masking enabled): ";
    password = maskedInput();
}

std::string maskedInput() {
    std::string password;
    char ch;
    while ((ch = _getch()) != '\r') { // '\r' is Enter key
        if (ch == 8) { // Backspace
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b";
            }
        } else {
            password += ch;
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return password;
}

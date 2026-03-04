#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to check if username already exists
bool usernameExists(string username) {
    ifstream file("users.txt");
    string user, pass;

    while (file >> user >> pass) {
        if (user == username) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// Registration Function
void registerUser() {
    string username, password;

    cout << "\n===== Registration =====\n";
    cout << "Enter Username: ";
    cin >> username;

    if (usernameExists(username)) {
        cout << "Error: Username already exists!\n";
        return;
    }

    cout << "Enter Password: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    file << username << " " << password << endl;
    file.close();

    cout << "Registration Successful!\n";
}

// Login Function
void loginUser() {
    string username, password;
    string user, pass;
    bool found = false;

    cout << "\n===== Login =====\n";
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    ifstream file("users.txt");

    while (file >> user >> pass) {
        if (user == username && pass == password) {
            found = true;
            break;
        }
    }

    file.close();

    if (found) {
        cout << "Login Successful! Welcome, " << username << "!\n";
    } else {
        cout << "Error: Invalid Username or Password!\n";
    }
}

int main() {
    int choice;

    do {
        cout << "\n==============================\n";
        cout << "   Login & Registration System\n";
        cout << "==============================\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "Exiting Program...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 3);

    return 0;
}
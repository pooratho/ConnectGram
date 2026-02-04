#include "Application.h"

void Application::run() {
    cout << "--- Welcome to ConnectGram ---" << endl;
    string line;

    while (isRunning) {
        if (currentUser)
            cout << "[" << currentUser->username << "] > ";
        else
            cout << "[Guest] > ";

        getline(cin, line);
        if (!line.empty())
            handleCommand(line);
    }
}

void Application::handleCommand(const string& input) {
    stringstream ss(input);
    string cmd;
    ss >> cmd;

    vector<string> args;
    string arg;
    while (ss >> arg)
        args.push_back(arg);

    if (cmd == "signup") handleSignup(args);
    else if (cmd == "login") handleLogin(args);
    else if (cmd == "logout") handleLogout();
    else if (cmd == "search_user") handleSearch(args);
    else if (cmd == "follow") handleFollow(args);
    else if (cmd == "unfollow") handleUnfollow(args);
    else if (cmd == "show_user") showCurrentUser();
    else if (cmd == "help") showHelp();
    else if (cmd == "exit") {
        isRunning = false;
        cout << "Exiting... Goodbye!" << endl;
    }
    else cout << "Unknown command. Type 'help' for instructions." << endl;
}

void Application::handleSignup(const vector<string>& args) {
    if (args.size() != 2) {
        cout << "Usage: signup <username> <password>" << endl;
        return;
    }
    if (userManager.signup(args[0], args[1]))
        cout << "Registration successful!" << endl;
    else
        cout << "Error: Username already exists." << endl;
}

void Application::handleLogin(const vector<string>& args) {
    if (args.size() != 2) {
        cout << "Usage: login <username> <password>" << endl;
        return;
    }
    if (currentUser) {
        cout << "Already logged in as " << currentUser->username << "!" << endl;
        return;
    }

    User* user = userManager.login(args[0], args[1]);
    if (user) {
        currentUser = user;
        cout << "Login successful. Welcome, " << currentUser->username << "!" << endl;
    }
    else {
        cout << "Invalid username or password." << endl;
    }
}

void Application::handleLogout() {
    if (!currentUser) {
        cout << "No user is currently logged in." << endl;
        return;
    }
    cout << "Logged out: " << currentUser->username << endl;
    currentUser = nullptr;
}

void Application::handleSearch(const vector<string>& args) {
    if (args.empty()) {
        cout << "Usage: search_user <prefix>" << endl;
        return;
    }
    string prefix = args[0];

    if (currentUser)
        currentUser->addSearchHistory(prefix);

    vector<string> results = userManager.searchUser(prefix);
    if (results.empty())
        cout << "No users found with this prefix." << endl;
    else {
        cout << "Results:" << endl;
        for (const string& name : results)
            cout << " - " << name << endl;
    }
}

void Application::handleFollow(const vector<string>& args) {
    if (!currentUser) {
        cout << "Please login first!" << endl;
        return;
    }
    if (args.empty()) {
        cout << "Usage: follow <username>" << endl;
        return;
    }
    if (userManager.follow(currentUser, args[0]))
        cout << "You are now following " << args[0] << "." << endl;
    else
        cout << "Failed to follow. User may not exist or already followed." << endl;
}

void Application::handleUnfollow(const vector<string>& args) {
    if (!currentUser) {
        cout << "Please login first!" << endl;
        return;
    }
    if (args.empty()) {
        cout << "Usage: unfollow <username>" << endl;
        return;
    }
    if (userManager.unfollow(currentUser, args[0]))
        cout << "You have unfollowed " << args[0] << "." << endl;
    else
        cout << "Failed to unfollow. User may not exist or not followed." << endl;
}

void Application::showCurrentUser() const {
    if (currentUser)
        currentUser->display();
    else
        cout << "No user logged in." << endl;
}

void Application::showHelp() const {
    cout << "\nAvailable commands:\n"
        << "signup <username> <password>\n"
        << "login <username> <password>\n"
        << "logout\n"
        << "search_user <prefix>\n"
        << "follow <username>\n"
        << "unfollow <username>\n"
        << "show_user\n"
        << "help\n"
        << "exit\n" << endl;
}

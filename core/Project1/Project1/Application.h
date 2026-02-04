#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "UserManager.h"

using namespace std;

class Application {
private:
    UserManager userManager;
    User* currentUser = nullptr;
    bool isRunning = true;

public:
    Application() = default;

    void run();
    void handleCommand(const string& input);

private:
    void handleSignup(const vector<string>& args);
    void handleLogin(const vector<string>& args);
    void handleLogout();
    void handleSearch(const vector<string>& args);
    void handleFollow(const vector<string>& args);
    void handleUnfollow(const vector<string>& args);
    void showCurrentUser() const;
    void showHelp() const;
};

#endif

#include "PostManager.h"
#include "UserManager.h"

class Application {
private:
    UserManager userManager;
    PostManager postManager;
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

    void handlePost(const vector<string>& args);
    void handleTrend(const vector<string>& args);
    void handleLike(const vector<string>& args);
    void handleShowPost(const vector<string>& args);

    void handleShowFeed(); 
    void handleSmartSearch(const vector<string>& args); 
    void handleShowHistory();
};

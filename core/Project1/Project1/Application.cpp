#include "Application.h"
#include "PostManager.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

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
    else if (cmd == "post") handlePost(args);
    else if (cmd == "trend") handleTrend(args);
    else if (cmd == "like") handleLike(args);
    else if (cmd == "show_post") handleShowPost(args);

    else if (cmd == "show_feed") handleShowFeed();
    else if (cmd == "smart_search") handleSmartSearch(args);

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
        << "post \"<content>\"\n"
        << "trend <hashtag>\n"
        << "like <post_id>\n"
        << "show_post <post_id>\n"
        << "show_feed\n"
        << "smart_search <hashtag>\n"
        << "help\n"
        << "exit\n" << endl;
}

void Application::handlePost(const vector<string>& args) {
    if (!currentUser) {
        cout << "Please login first!" << endl;
        return;
    }
    if (args.empty()) {
        cout << "Usage: post \"<content>\"" << endl;
        return;
    }

    string content;
    for (const auto& s : args) {
        if (!content.empty()) content += " ";
        content += s;
    }

    Post* p = new Post(currentUser, content);
    postManager.addPost(p);
    cout << "Post created with ID: " << p->getId() << endl;
}

void Application::handleTrend(const vector<string>& args) {
    if (args.empty()) {
        cout << "Usage: trend <hashtag>" << endl;
        return;
    }
    string hashtag = args[0];

    vector<Post*> posts = postManager.getPostsByHashtag(hashtag);

    if (posts.empty()) {
        cout << "No posts found for #" << hashtag << endl;
        return;
    }

    cout << "Top posts for #" << hashtag << ":\n";
    for (auto* p : posts)
        p->display();
}

void Application::handleLike(const vector<string>& args) {
    if (!currentUser) {
        cout << "Please login first!" << endl;
        return;
    }

    if (args.empty()) {
        cout << "Usage: like <post_id>" << endl;
        return;
    }

    int postId = stoi(args[0]);

    bool success = postManager.likePost(postId, currentUser);

    if (success) {
        cout << "Post " << postId << " liked successfully ❤️" << endl;
    }
    else {
        cout << "You already liked this post or post not found." << endl;
    }
}

void Application::handleShowPost(const vector<string>& args) {
    if (args.empty()) {
        cout << "Usage: show_post <post_id>" << endl;
        return;
    }
    int postId = stoi(args[0]);
    postManager.displayPost(postId);
}

void Application::handleShowFeed() {
    if (!currentUser) {
        cout << "Please login first.\n";
        return;
    }

    auto feedPosts = postManager.showFeed(currentUser);

    if (feedPosts.empty()) {
        cout << "Your feed is empty!\n";
        return;
    }

    cout << "Your feed:\n";
    for (auto* post : feedPosts) {
        post->display();
        cout << "-------------------\n";
    }
}

void Application::handleSmartSearch(const vector<string>& args) {
    if (args.empty()) {
        cout << "Usage: smart_search <term>" << endl;
        return;
    }
    string target = args[0];

    if (currentUser) currentUser->addSearchHistory(target);

    if (userManager.getUser(target)) {
        cout << "Exact match found: @" << target << endl;
    }
    else {
        vector<string> suggestions = userManager.getSmartSuggestions(target, 3);

        if (!suggestions.empty()) {
            cout << "User not found. Did you mean?" << endl;
            for (const string& s : suggestions)
                cout << " -> " << s << endl;
        }
        else {
            cout << "No matches or similar users found for '" << target << "'." << endl;
        }
    }
}

void Application::handleShowHistory() {
    if (!currentUser) {
        cout << "Error: You must be logged in to view your search history." << endl;
        return;
    }

    const auto& history = currentUser->getSearchHistory();

    if (history.empty()) {
        cout << "Your search history is empty. Try searching for something first!" << endl;
        return;
    }

    cout << "--- Your Recent Searches ---" << endl;

    int index = 1;
    for (const auto& term : history) {
        cout << index << ". " << term << endl;
        index++;
    }
    cout << "-----------------------------" << endl;
}

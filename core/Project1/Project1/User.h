#ifndef USER_H
#define USER_H

#include <string>
#include <set>
#include <deque>
#include <vector>
#include "Post.h"

using namespace std;

class Post;

class User {
private:
    string password;
    int followersCount = 0;
    deque<string> searchHistory;
    set<User*> following;
    vector<Post*> posts;

public:
    string username;

    User(const string& uname, const string& pwd);

    void setPassword(const string& pwd);
    bool checkPassword(const string& pwd) const;

    void addFollower();
    void removeFollower();
    int getFollowersCount() const;

    const set<User*>& getFollowings() const;
    void addFollowing(User* user);   
    void removeFollowing(User* user); 

    void addPost(Post* post);
    const vector<Post*>& getPosts() const;

    void addSearchHistory(const string& term);
    void showSearchHistory() const;

    void display() const;
};

#endif

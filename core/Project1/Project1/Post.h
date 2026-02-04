#ifndef POST_H
#define POST_H

#include <string>
#include <set>
#include <chrono>

class User;

class Post {
private:
    void parseHashtags();

public:
    int id;
    std::string content;
    User* author;
    int likeCount;
    std::set<std::string> hashtags;
    std::chrono::system_clock::time_point timestamp;

    Post(int id, const std::string& content, User* author);

    void addLike();

    const std::set<std::string>& getHashtags() const;

    void display() const;
};

#endif

#ifndef POST_H
#define POST_H

#include <string>
#include <set>
#include <chrono>

class User;

class Post {
private:
    int id;
    std::string content;
    User* author;
    int likeCount;
    std::set<std::string> hashtags;
    std::chrono::system_clock::time_point timestamp;

    static int nextId;
    void parseHashtags();

public:
    Post(User* author, const std::string& content);

    int getId() const { return id; }
    std::string getContent() const { return content; }
    User* getAuthor() const { return author; }
    int getLikeCount() const { return likeCount; }
    std::chrono::system_clock::time_point getTimestamp() const { return timestamp; }

    void addLike();
    const std::set<std::string>& getHashtags() const;
    double calculateScore() const;
    void display() const;
};

#endif

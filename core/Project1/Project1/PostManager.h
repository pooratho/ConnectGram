#ifndef POSTMANAGER_H
#define POSTMANAGER_H

#include <unordered_map>
#include <vector>
#include <string>
#include "Post.h"
#include "User.h"
#include "HashTable.h"

class PostManager {
private:
    std::unordered_map<int, Post*> allPosts;
    std::unordered_map<std::string, std::vector<Post*>> userPosts;
    HashTable hashtagTable;

public:
    PostManager() = default;
    ~PostManager();

    void addPost(Post* p);

    bool deletePost(int postId);

    std::vector<Post*> getPostsByUser(const std::string& username);

    std::vector<Post*> getPostsByHashtag(const std::string& hashtag);

    bool likePost(int postId);

    void displayPost(int postId);
};

#endif

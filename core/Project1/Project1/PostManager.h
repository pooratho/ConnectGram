#ifndef POSTMANAGER_H
#define POSTMANAGER_H

#include <unordered_map>
#include <vector>
#include <string>
#include "Post.h"
#include "User.h"
#include "HashTable.h"
#include "MaxHeap.h"

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
    std::vector<Post*> getTopPostsByHashtag(const std::string& hashtag, int topN = 10);

    bool likePost(int postId, User* user);
    void displayPost(int postId);

    std::vector<Post*> showFeed(User* currentUser);
};

#endif

#include "PostManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

PostManager::~PostManager() {
    for (auto& pair : allPosts) {
        delete pair.second;
    }
}

void PostManager::addPost(Post* p) {
    allPosts[p->id] = p;
    userPosts[p->author->username].push_back(p);

    for (const auto& tag : p->getHashtags()) {
        hashtagIndex[tag].insert(p);
    }
}

bool PostManager::deletePost(int postId) {
    if (!allPosts.count(postId)) return false;

    Post* p = allPosts[postId];
    allPosts.erase(postId);

    auto& postsVec = userPosts[p->author->username];
    postsVec.erase(std::remove(postsVec.begin(), postsVec.end(), p), postsVec.end());

    for (const auto& tag : p->getHashtags()) {
        hashtagIndex[tag].erase(p);
        if (hashtagIndex[tag].empty())
            hashtagIndex.erase(tag);
    }

    delete p;
    return true;
}

std::vector<Post*> PostManager::getPostsByUser(const std::string& username) {
    if (userPosts.count(username))
        return userPosts[username];
    return {};
}

std::vector<Post*> PostManager::getPostsByHashtag(const std::string& hashtag) {
    std::vector<Post*> result;
    if (hashtagIndex.count(hashtag)) {
        result.assign(hashtagIndex[hashtag].begin(), hashtagIndex[hashtag].end());
    }

    std::sort(result.begin(), result.end(), [](Post* a, Post* b) {
        return a->timestamp > b->timestamp;
        });

    if (result.size() > 10)
        result.resize(10);

    return result;
}

bool PostManager::likePost(int postId) {
    if (!allPosts.count(postId)) return false;
    allPosts[postId]->addLike();
    return true;
}

void PostManager::displayPost(int postId) {
    if (allPosts.count(postId))
        allPosts[postId]->display();
    else
        std::cout << "Post not found.\n";
}

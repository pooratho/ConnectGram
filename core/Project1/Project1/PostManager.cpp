#include "PostManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

PostManager::~PostManager() {
    for (auto& pair : allPosts) {
        delete pair.second;
    }
}

void PostManager::addPost(Post* p) {
    if (!p) return;

    allPosts[p->getId()] = p;
    userPosts[p->getAuthor()->username].push_back(p);

    for (const auto& tag : p->getHashtags()) {
        hashtagTable.insert(tag, p);
    }
}

bool PostManager::deletePost(int postId) {
    if (!allPosts.count(postId)) return false;

    Post* p = allPosts[postId];

    allPosts.erase(postId);

    auto& postsVec = userPosts[p->getAuthor()->username];
    postsVec.erase(
        std::remove(postsVec.begin(), postsVec.end(), p),
        postsVec.end()
    );

    for (const auto& tag : p->getHashtags()) {
        hashtagTable.remove(tag, p);
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

    std::vector<Post*> result = hashtagTable.get(hashtag);

    std::sort(result.begin(), result.end(),
        [](Post* a, Post* b) {
            return a->getTimestamp() > b->getTimestamp();
        }
    );

    if (result.size() > 10)
        result.resize(10);

    return result;
}

std::vector<Post*> PostManager::getTopPostsByHashtag(const std::string& hashtag, int topN) {
    std::vector<Post*> result;

    std::vector<Post*> posts = hashtagTable.get(hashtag);
    if (posts.empty())
        return result;

    MaxHeap heap;
    for (Post* post : posts) {
        heap.insert({ post->calculateScore(), post });
    }

    while (!heap.isEmpty() && result.size() < topN) {
        result.push_back(heap.extractMax());
    }

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

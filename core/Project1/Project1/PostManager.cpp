#include "PostManager.h"
#include <algorithm>
#include <iostream>

PostManager::~PostManager() {
    for (auto& pair : allPosts)
        delete pair.second;
}

void PostManager::addPost(Post* p) {
    if (!p) return;

    allPosts[p->getId()] = p;
    userPosts[p->getAuthor()->username].push_back(p);

    for (const auto& tag : p->getHashtags())
        hashtagTable.insert(tag, p);
}

bool PostManager::deletePost(int postId) {
    if (!allPosts.count(postId)) return false;

    Post* p = allPosts[postId];
    allPosts.erase(postId);

    auto& postsVec = userPosts[p->getAuthor()->username];
    postsVec.erase(std::remove(postsVec.begin(), postsVec.end(), p), postsVec.end());

    for (const auto& tag : p->getHashtags())
        hashtagTable.remove(tag, p);

    delete p;
    return true;
}

std::vector<Post*> PostManager::getPostsByUser(const std::string& username) {
    if (userPosts.count(username))
        return userPosts[username];
    return {};
}

std::vector<Post*> PostManager::getPostsByHashtag(const std::string& hashtag) {
    auto result = hashtagTable.get(hashtag);

    std::sort(result.begin(), result.end(),
        [](Post* a, Post* b) { return a->getTimestamp() > b->getTimestamp(); }
    );

    if (result.size() > 10)
        result.resize(10);

    return result;
}

std::vector<Post*> PostManager::getTopPostsByHashtag(const std::string& hashtag, int topN) {
    std::vector<Post*> result;
    if (!hashtagTable.contains(hashtag))
        return result;

    MaxHeap heap;
    for (auto* post : hashtagTable.get(hashtag))
        heap.insert({ post->calculateScore(), post });

    while (!heap.isEmpty() && result.size() < topN)
        result.push_back(heap.extractMax());

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

std::vector<Post*> PostManager::showFeed(User* currentUser) {
    if (!currentUser) return {};

    MaxHeap heap;
    const auto& followings = currentUser->getFollowings();

    for (User* following : followings) {
        const auto& posts = userPosts[following->username];
        for (Post* p : posts)
            heap.insert({ p->calculateScore(), p });
    }

    std::vector<Post*> feed;
    int count = 0;
    while (!heap.isEmpty() && count < 10) {
        feed.push_back(heap.extractMax());
        count++;
    }

    return feed;
}

#include "Post.h"
#include "User.h"
#include <iostream>

int Post::nextId = 1;

Post::Post(User* author, const std::string& content)
    : id(nextId++), content(content), author(author), likeCount(0)
{
    timestamp = std::chrono::system_clock::now();
    parseHashtags();
}

void Post::addLike() {
    likeCount++;
}

const std::set<std::string>& Post::getHashtags() const {
    return hashtags;
}

void Post::parseHashtags() {
    hashtags.clear();
    size_t pos = 0;
    while ((pos = content.find('#', pos)) != std::string::npos) {
        size_t end = content.find_first_of(" \t\n", pos + 1);
        std::string tag = content.substr(pos + 1, end - pos - 1);
        if (!tag.empty())
            hashtags.insert(tag);
        pos = (end == std::string::npos) ? content.size() : end;
    }
}

void Post::display() const {
    std::cout << "Post ID: " << id << "\n";
    std::cout << "Author: " << author->username << "\n";
    std::cout << "Content: " << content << "\n";
    std::cout << "Likes: " << likeCount << "\n";
    std::cout << "Hashtags: ";
    for (const auto& tag : hashtags)
        std::cout << "#" << tag << " ";
    std::cout << "\n";
}

#include "SearchManager.h"
#include <algorithm>
#include <cctype> 

bool compareCharIgnoreCase(char a, char b) {
    return std::tolower(static_cast<unsigned char>(a)) ==
        std::tolower(static_cast<unsigned char>(b));
}

int SearchManager::calculateHamming(const std::string& s1, const std::string& s2) {
    if (s1.length() != s2.length()) return -1;
    int distance = 0;
    for (size_t i = 0; i < s1.length(); ++i) {
        if (!compareCharIgnoreCase(s1[i], s2[i])) distance++;
    }
    return distance;
}

std::vector<std::string> SearchManager::getSuggestions(
    const std::string& target,
    const std::vector<std::string>& sourceList,
    int threshold
) {
    std::vector<std::string> suggestions;
    for (const auto& item : sourceList) {
        if (item.length() == target.length()) {
            int dist = calculateHamming(target, item);
            if (dist >= 0 && dist < threshold) {
                suggestions.push_back(item);
            }
        }
    }
    return suggestions;
}

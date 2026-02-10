#ifndef SEARCH_MANAGER_H
#define SEARCH_MANAGER_H

#include <string>
#include <vector>

class SearchManager {
public:
    static int calculateHamming(const std::string& s1, const std::string& s2);

    static std::vector<std::string> getSuggestions(
        const std::string& target,
        const std::vector<std::string>& sourceList,
        int threshold = 3
    );
};

#endif

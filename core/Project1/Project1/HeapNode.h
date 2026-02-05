#ifndef HEAPNODE_H
#define HEAPNODE_H

#include "Post.h"

struct HeapNode {
    double score;
    Post* post;

    bool operator>(const HeapNode& other) const {
        return score > other.score;
    }
};

#endif

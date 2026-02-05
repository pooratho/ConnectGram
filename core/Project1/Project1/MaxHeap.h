#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <vector>
#include "HeapNode.h"

class MaxHeap {
private:
    std::vector<HeapNode> heap;

    int parent(int i) const;
    int left(int i) const;
    int right(int i) const;

    void heapifyUp(int i);
    void heapifyDown(int i);

public:
    void insert(const HeapNode& node);
    Post* extractMax();
    bool isEmpty() const;
};

#endif

#include "MaxHeap.h"
#include <algorithm>
#include <stdexcept>

int MaxHeap::parent(int i) const {
    return (i - 1) / 2;
}

int MaxHeap::left(int i) const {
    return 2 * i + 1;
}

int MaxHeap::right(int i) const {
    return 2 * i + 2;
}

void MaxHeap::heapifyUp(int i) {
    while (i > 0) {
        int p = parent(i);
        if (!(heap[i] > heap[p]))
            break;

        std::swap(heap[i], heap[p]);
        i = p;
    }
}

void MaxHeap::heapifyDown(int i) {
    int size = heap.size();

    while (true) {
        int l = left(i);
        int r = right(i);
        int largest = i;

        if (l < size && heap[l] > heap[largest])
            largest = l;

        if (r < size && heap[r] > heap[largest])
            largest = r;

        if (largest == i)
            break;

        std::swap(heap[i], heap[largest]);
        i = largest;
    }
}

void MaxHeap::insert(const HeapNode& node) {
    if (!node.post)
        throw std::invalid_argument("Cannot insert null Post into heap");

    heap.push_back(node);
    heapifyUp(heap.size() - 1);
}

Post* MaxHeap::extractMax() {
    if (heap.empty())
        throw std::runtime_error("Heap is empty");

    Post* maxPost = heap.front().post;

    heap.front() = heap.back();
    heap.pop_back();

    if (!heap.empty())
        heapifyDown(0);

    return maxPost;
}

bool MaxHeap::isEmpty() const {
    return heap.empty();
}

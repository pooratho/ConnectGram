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
    while (i != 0 && heap[i] > heap[parent(i)]) {
        std::swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

void MaxHeap::heapifyDown(int i) {
    int l = left(i);
    int r = right(i);
    int largest = i;

    if (l < heap.size() && heap[l] > heap[largest])
        largest = l;

    if (r < heap.size() && heap[r] > heap[largest])
        largest = r;

    if (largest != i) {
        std::swap(heap[i], heap[largest]);
        heapifyDown(largest);
    }
}

void MaxHeap::insert(const HeapNode& node) {
    heap.push_back(node);
    heapifyUp(heap.size() - 1);
}

Post* MaxHeap::extractMax() {
    if (heap.empty())
        throw std::runtime_error("Heap is empty");

    Post* maxPost = heap[0].post;
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty())
        heapifyDown(0);

    return maxPost;
}

bool MaxHeap::isEmpty() const {
    return heap.empty();
}

#pragma once
#include<string>
using namespace std;

//heap :D

class HeapNode {
public:
    int ranking;
    string schoolName;

    HeapNode(int rank = 420, string school = "") : ranking(rank), schoolName(school) {}
};

class MaxHeap {

    void swap() {}

    void maxHeapify() {}

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return (2 * i + 1); }
    int rightChild(int i) { return (2 * i + 2); }

public:
    HeapNode** heapArray;
    int capacity;
    int size;

    MaxHeap(){}

    MaxHeap(int cap) : capacity(cap), size(0) {
        heapArray = new HeapNode * [capacity];
        for (int i = 0; i < capacity; i++) {
            heapArray[i] = nullptr;
        }
    }

    void insert(int stopId, int distance) {

    }

    HeapNode* extractMin() {
        return nullptr;
    }

    void decreaseKey(int stopId, int newDist) {

    }

    bool isEmpty() {
        return size == 0;
    }

    // Destructor
    ~MaxHeap() {
        for (int i = 0; i < size; ++i) {
            delete heapArray[i];
        }
        delete[] heapArray;
    }
};
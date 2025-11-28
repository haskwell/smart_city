#pragma once
#include<iostream>
#include<string>
using namespace std;

class HeapNode {
public:
    string hospitalId;
    int bedNumber;

    HeapNode(string id, int bed) : hospitalId(id), bedNumber(bed) {}
};

class MaxHeap {

    void swap(int i, int j) {
        HeapNode* temp = heapArray[i];
        heapArray[i] = heapArray[j];
        heapArray[j] = temp;
    }

    void maxHeapify(int i) {
        int l = leftChild(i);
        int r = rightChild(i);
        int largest = i;
    
        if (l < size && heapArray[l]->bedNumber > heapArray[largest]->bedNumber) {
            largest = l;
        }
        if (r < size && heapArray[r]->bedNumber > heapArray[largest]->bedNumber) {
            largest = r;
        }

        if (largest != i) {
            swap(i, largest);
            maxHeapify(largest);
        }

    }

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return (2 * i + 1); }
    int rightChild(int i) { return (2 * i + 2); }

    void resize() {
        int newCap = capacity * 2;
        HeapNode** newArray = new HeapNode * [newCap];

        for (int i = 0; i < newCap; ++i) {
            newArray[i] = nullptr;
        }

        for (int i = 0; i < size; ++i) {
            newArray[i] = heapArray[i];
        }

        for (int i = 0; i < size; ++i) {
            delete heapArray[i];
        }
        delete[] heapArray;

        heapArray = newArray;
        capacity = newCap;
    }

public:
    HeapNode** heapArray;
    int capacity;
    int size;

    MaxHeap() : capacity(0), size(0), heapArray(nullptr) {}

    void setTable(int cap) {
        capacity = cap;
        size = 0;
        heapArray = new HeapNode * [capacity];
        for (int i = 0; i < capacity; i++) {
            heapArray[i] = nullptr;
        }
    }

    void insert(string hospitalId, int bedNumber) {
        if (size == capacity) {
            resize();
        }
        size++;
        int i = size - 1;
        heapArray[i] = new HeapNode(hospitalId, bedNumber);

        while (i != 0 && heapArray[parent(i)]->bedNumber < heapArray[i]->bedNumber) {
            swap(i, parent(i));
            i = parent(i);
        }
    }

    HeapNode* getMax() const {
        if (size > 0) {
            return heapArray[0];
        }
        return nullptr;
    }

    void updateBedCount(int bedsRequired, string& hospitalId) {
        int oldBedNumber = heapArray[0]->bedNumber;
        if (bedsRequired > oldBedNumber) {
            return;
        }
        int newBedNumber = oldBedNumber - bedsRequired;
        hospitalId = heapArray[0]->hospitalId;
        heapArray[0]->bedNumber = newBedNumber;
        maxHeapify(0);
    }

    bool isEmpty() const {
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
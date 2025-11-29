#pragma once
#include<iostream>
#include<string>
using namespace std;

class HospitalHeapNode {
public:
    string hospitalId;
    int bedNumber;

    HospitalHeapNode(string id, int bed) : hospitalId(id), bedNumber(bed) {}
};

class HospitalMaxHeap {

    void swap(int i, int j) {
        HospitalHeapNode* temp = heapArray[i];
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
        HospitalHeapNode** newArray = new HospitalHeapNode * [newCap];

        for (int i = 0; i < newCap; ++i) {
            newArray[i] = nullptr;
        }

        for (int i = 0; i < size; ++i) {
            newArray[i] = heapArray[i];
        }

        delete[] heapArray;

        heapArray = newArray;
        capacity = newCap;
    }

public:
    HospitalHeapNode** heapArray;
    int capacity;
    int size;

    HospitalMaxHeap(int cap = 10) : capacity(cap), size(0) {
        heapArray = new HospitalHeapNode * [capacity];
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
        heapArray[i] = new HospitalHeapNode(hospitalId, bedNumber);

        while (i != 0 && heapArray[parent(i)]->bedNumber < heapArray[i]->bedNumber) {
            swap(i, parent(i));
            i = parent(i);
        }
    }

    string getMax() const {
        if (size > 0) {
            return heapArray[0]->hospitalId;
        }
        return "";
    }

    bool updateBedCount(int bedsRequired, string& hospitalId) {
        int oldBedNumber = heapArray[0]->bedNumber;
        if (bedsRequired > oldBedNumber) {
            return false;
        }
        int newBedNumber = oldBedNumber - bedsRequired;
        hospitalId = heapArray[0]->hospitalId;
        heapArray[0]->bedNumber = newBedNumber;
        maxHeapify(0);
        return true;
    }

    bool isEmpty() const {
        return size == 0;
    }

    ~HospitalMaxHeap() {
        for (int i = 0; i < size; ++i) {
            delete heapArray[i];
        }
        delete[] heapArray;
    }
};
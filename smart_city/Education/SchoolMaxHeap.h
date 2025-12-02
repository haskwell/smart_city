#pragma once
#include<string>
using namespace std;

//heap :D

class HeapNode {
public:
    float rating;
    string schoolID;
    HeapNode(int rank = 0, string school = "") : rating(rank), schoolName(school) {}
};

class MaxHeap {

    void swap(int i, int j) {
        HeapNode* temp = heapArray[i];
        heapArray[i] = heapArray[j];
        heapArray[j] = temp;
    }

    void maxHeapify(int i)
    {
        int l = leftChild(i);
        int r = rightChild(i);
        int largest = i;

        if (l < size && heapArray[l]->rating > heapArray[largest]->rating) {
            largest = l; 
        }
        if (r < size && heapArray[r]->rating > heapArray[largest]->rating) {
            largest = r;
        }

        if (largest != i) {
            swap(i, largest);
            maxHeapify(largest);
        }
    }

    void resize() {
        int newCap = capacity * 2;
        HeapNode** newArray = new HeapNode * [newCap];

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

    void insert(string schoolId, float rating) {
        if (size == capacity) {
            resize();
        }
        size++;
        int i = size - 1;
        heapArray[i] = new HeapNode();
        heapArray[i]->rating = rating;
        heapArray[i]->rating = rating;


        while (i != 0 && heapArray[parent(i)]->rating < heapArray[i]->rating) {
            swap(i, parent(i));
            i = parent(i);
        }
    }

    string getMax() const {
        if (size > 0) {
            return heapArray[0]->schoolID;
        }
        return "";
    }
    void decreaseKey(int stopId, int newDist) {

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

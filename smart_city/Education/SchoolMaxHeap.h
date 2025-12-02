#pragma once
#include<string>
using namespace std;

//heap :D

class HeapNode {
public:
    float rating;
    string schoolID;
    HeapNode(int rank = 0, string school = "") : rating(rank), schoolID(school) {}
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

    MaxHeap(int cap = 10) {
        size = 0;
		capacity = cap;
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

    string* getTop3()
    {

    }

    string getMax() const {
        if (size > 0) {
            return heapArray[0]->schoolID;
        }
        return "";
    }

    bool isEmpty() const {
        return size == 0;
    }

    string* getTop3()
    {
        string* result = new string[3];

        if (size == 0) {
            result[0] = result[1] = result[2] = "";
            return result;
        }

        // Top 1 is always the root
        result[0] = heapArray[0]->schoolID;

        if (size == 1) {
            result[1] = result[2] = "";
            return result;
        }

        if (size == 2) {
            result[1] = heapArray[1]->schoolID;
            result[2] = "";
            return result;
        }

        // size >= 3
        // children of root = index 1 and index 2
        if (heapArray[1]->rating >= heapArray[2]->rating) {
            result[1] = heapArray[1]->schoolID;
            result[2] = heapArray[2]->schoolID;
        }
        else {
            result[1] = heapArray[2]->schoolID;
            result[2] = heapArray[1]->schoolID;
        }

        return result;
    }

    // Destructor
    ~MaxHeap() {
        for (int i = 0; i < size; ++i) {
            delete heapArray[i];
        }
        delete[] heapArray;
    }
};
#pragma once
#include<iostream>
#include<string>
#include"CityGraph.h"

using namespace std;

class ManualStack
{
	string* array;
	int topindex;
	int capacity;

public:
	ManualStack(int size = 100)
	{
		array = new string[size];
		capacity = size;
		topindex = -1;
	}

	~ManualStack()
	{
		delete[] array;
	}

	void push(string value)
	{
		if (topindex < capacity - 1)
		{
			array[++topindex] = value;
		}
	}

	void pop()
	{
		if (topindex >= 0)
		{
			topindex--;
		}
	}

	string top()
	{
		if (topindex >= 0)
		{
			return array[topindex];
		}
		return "";
	}

	bool isEmpty()
	{
		return topindex == -1;
	}

};

class GraphMinHeap
{
	GraphNode** heapArray;
	int capacity;
	int currentSize;

	void swapNodes(int index1, int index2)
	{
		GraphNode* temp = heapArray[index1];
		heapArray[index1] = heapArray[index2];
		heapArray[index2] = temp;
	}

	void heapifyUp(int index)
	{
		while (index > 0)
		{
			int parentIndex = (index - 1) / 2;
			if (heapArray[index]->minDistance < heapArray[parentIndex]->minDistance)
			{
				swapNodes(index, parentIndex);
				index = parentIndex;
			}
			else
			{
				break;
			}
		}
	}

	void HeapifyDown(int index)
	{
		while (1)
		{
			int leftChildIndex = 2 * index + 1;
			int rightChildIndex = 2 * index + 2;
			int smallestIndex = index;
			if (leftChildIndex < currentSize && heapArray[leftChildIndex]->minDistance < heapArray[smallestIndex]->minDistance)
			{
				smallestIndex = leftChildIndex;
			}
			if (rightChildIndex < currentSize && heapArray[rightChildIndex]->minDistance < heapArray[smallestIndex]->minDistance)
			{
				smallestIndex = rightChildIndex;
			}
			if (smallestIndex != index)
			{
				swapNodes(index, smallestIndex);
				index = smallestIndex;
			}
			else
			{
				break;
			}
		}
	}

public:

	GraphMinHeap(int cap = 2000)
	{
		capacity = cap;
		currentSize = 0;
		heapArray = new GraphNode * [capacity];
	}

	~GraphMinHeap()
	{
		delete[] heapArray;
	}

	bool isEmpty()
	{
		return currentSize == 0;
	}

	void insert(GraphNode* node)
	{
		if (currentSize < capacity)
		{
			heapArray[currentSize] = node;
			heapifyUp(currentSize);
			currentSize++;
		}
	}

	GraphNode* extractMin()
	{
		if (isEmpty())
		{
			return nullptr;
		}

		GraphNode* minNode = heapArray[0];

		heapArray[0] = heapArray[currentSize - 1];

		currentSize--;
		HeapifyDown(0);
		return minNode;
	}


};

class CityPathFinder
{
	GraphManager* graphManager;
	const double infinityValue = 1000000000.0;

	void resetGraphState()
	{
		if (graphManager->adjacencyList == nullptr)
		{
			return;
		}

		GraphNode* typeHead = graphManager->adjacencyList;

		while (typeHead != nullptr)
		{
			GraphNode* node = typeHead;

			while (node != nullptr)
			{
				node->minDistance = infinityValue;
				node->previous = nullptr;
				node->isVisited = false;
				node = node->nextType;
			}
			typeHead = typeHead->next;
		}
	}

	GraphNode* findNodeByID(string id)
	{
		if (graphManager->adjacencyList == nullptr)
		{
			return nullptr;
		}

		GraphNode* typeHead = graphManager->adjacencyList;

		while (typeHead != nullptr)
		{
			GraphNode* node = typeHead;

			while (node != nullptr)
			{
				if (node->ID == id)
				{
					return node;
				}
				node = node->nextType;
			}
			typeHead = typeHead->next;
		}
		return nullptr;
	}


public:
	CityPathFinder(GraphManager* gm) : graphManager(gm) {}

	void findShortestDistance(string startID, string endID)
	{
		resetGraphState();

		GraphNode* startNode = findNodeByID(startID);
		GraphNode* endNode = findNodeByID(endID);

		if (startNode == nullptr || endNode == nullptr)
		{
			return;
		}

		GraphMinHeap pq(2000);


		startNode->minDistance = 0.0;
		pq.insert(startNode);

		while (!pq.isEmpty())
		{
			GraphNode* current = pq.extractMin();

			if (current == endNode)
			{
				break;
			}

			if (current->isVisited == true)
			{
				continue;
			}

			current->isVisited = true;

			EdgeNode* edge = current->edgeHead;

			while (edge != nullptr)
			{
				GraphNode* neighbor = edge->to;
				double newDist = current->minDistance + edge->weight;

				if (newDist < neighbor->minDistance)
				{
					neighbor->minDistance = newDist;
					neighbor->previous = current;
					pq.insert(neighbor);
				}

				edge = edge->nextEdge;
			}
		}
		printPath(endNode);
	}

	void printPath(GraphNode* endNode)
	{
		// If distance is still "Infinity", no path was found
		if (endNode->minDistance >= infinityValue) {
			cout << "No path exists to " << endNode->ID << endl;
			return;
		}

		cout << "Shortest Path to " << endNode->ID << " (Total Distance: " << endNode->minDistance << " units):" << endl;

		// Use ManualStack to reverse the path (End -> Start becomes Start -> End)
		ManualStack pathStack(100);
		GraphNode* curr = endNode;

		while (curr != nullptr) {
			pathStack.push(curr->ID);
			curr = curr->previous;
		}

		// Pop from stack to print in correct order
		while (!pathStack.isEmpty()) {
			cout << pathStack.top();
			pathStack.pop();
			if (!pathStack.isEmpty()) cout << " -> ";
		}
		cout << endl << endl;
	}

};
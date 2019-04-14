#pragma once

#include <iostream>

using namespace std;

template <class T>
class Queue {
private:
	T* data = nullptr;
	int count;
	int size;
public:
	Queue() {
		data = new T[10];
		count = 0;
		size = 10;
	}
	//copy constructor
	Queue(Queue* otherQueue) {
		T* otherQueueData = otherQueue->GetData();
		size = otherQueue->GetSize();
		count = otherQueue->GetCount();
		data = new T[size];
		for (size_t i = 0; i < size; i++)
		{
			data[i] = otherQueueData[i];
		}
	}
	//equal assignment operator for queue
	Queue& operator= (Queue& otherQueue) {
		if (this != &otherQueue)
			delete[] data;
		T* otherQueueData = otherQueue.GetData();
		size = otherQueue.GetSize();
		count = otherQueue.GetCount();
		data = new T[size];
		for (size_t i = 0; i < size; i++)
		{
			data[i] = otherQueueData[i];
		}
		return *this;
	}
	//pops the first value off the front of the queue, shifts all entries down
	void Pop() {
		if (count > 0) {
			T poppedData = data[0];
			if (count > 1) {
				for (size_t i = 1; i < count; i++)
				{
					data[i - 1] = data[i];
				}
			}
			count--;
		}
	}
	//pushes a value onto back of queue, doubles size of array if the count exceeds the limit
	void Push(T newData) {
		if (count == size) {
			T* newDataArray = new T[size * 2];
			size *= 2;
			for (size_t i = 0; i < count; i++)
			{
				newDataArray[i] = data[i];
			}
			delete[] data;
			data = newDataArray;
		}
		count++;
		data[count-1] = newData;
	}
	//prints out all of the entries in the queue
	void Print() {
		cout << "Count: " << count << endl << "Size: " << size << endl;
		for (size_t i = 0; i < count; i++)
		{
			cout << data[i] << endl;
		}
	}
	//gets a pointer to the array of data in queue
	T* GetData() {
		return data;
	}
	//gets the number of entries in queue
	int GetCount() {
		return count;
	}
	//gets the max amount of entries the queue can currently hold
	int GetSize() {
		return size;
	}
	//checks if the queue is empty or not
	bool IsEmpty() {
		return count <= 0;
	}
	~Queue() {
		delete[] data;
	}
};
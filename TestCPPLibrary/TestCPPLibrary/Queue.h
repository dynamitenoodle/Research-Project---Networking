#pragma once

#include <iostream>
#include <mutex>

using namespace std;

template <class T>
class Queue {
private:
	T* data = nullptr;
	int count;
	int size;
	int maxSize = -1;
	mutex m;
public:
	Queue(int initS = 10, int mS = INT_MAX) {
		if (initS > mS) initS = mS;
		if (initS < 1) initS = 1;
		data = new T[initS];
		count = 0;
		size = initS;
		maxSize = mS;
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
	T Pop() {
		m.lock();
		if (count > 0) {
			T poppedData = data[0];
			if (count > 1) {
				for (size_t i = 1; i < count; i++)
				{
					data[i - 1] = data[i];
				}
			}
			count--;
			m.unlock();
			return poppedData;
		}
		m.unlock();
		throw std::runtime_error("There is no data to pop in queue.");
	}
	//pushes a value onto back of queue, doubles size of array if the count exceeds the limit
	void Push(T newData) {
		m.lock();
		if (count == size && count < maxSize) {
			int newSizeOfArray = size * 2;
			if (newSizeOfArray > maxSize) newSizeOfArray = maxSize;
			T* newDataArray = new T[newSizeOfArray];
			size = newSizeOfArray;
			for (size_t i = 0; i < count; i++)
			{
				newDataArray[i] = data[i];
			}
			delete[] data;
			data = newDataArray;
		}
		if (count != maxSize) {
			count++;
			data[count - 1] = newData;
		}
		m.unlock();
	}
	//prints out all of the entries in the queue
	void Print() {
		cout << "Count: " << count << endl << "Size: " << size << endl;
		for (size_t i = 0; i < count; i++)
		{
			cout << data[i] << endl;
		}
	}

	T Peek() {
		if (count > 0) {
			return data[0];
		}
		throw std::runtime_error("There is no data to peek at in queue.");
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
	bool IsFull() {
		return count == maxSize;
	}
	~Queue() {
		delete[] data;
	}
};
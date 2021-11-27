#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

template <class T>
class QueueManager
{
	std::mutex lock;
	std::queue<T> queue;
	std::condition_variable event;

public:
	QueueManager() {};
	~QueueManager() {};

	void push(T element);
	T pop();
	int size();	
};


template <class T>
void QueueManager<T>::push(T element)
{
	std::lock_guard<std::mutex> lk(this->lock);
	this->queue.push(element);
	this->event.notify_one();
}

template <class T>
T QueueManager<T>::pop()
{
	std::unique_lock<std::mutex> lk(this->lock);
	this->event.wait(lk, [this] {return !this->queue.empty(); });
	T result = this->queue.front();
	this->queue.pop();
	return result;
}

template <class T>
int QueueManager<T>::size()
{
	std::lock_guard<std::mutex> lk(this->lock);
	return this->queue.size();
}
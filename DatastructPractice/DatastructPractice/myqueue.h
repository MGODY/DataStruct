#ifndef MYQUEUE_H
#define MYQUEUE_H



#include"Vector.h"
#include"list.h"
#include"mystd.h"
#include<initializer_list>

MYSTD_BEGIN
template<typename T>
class Queue:protected mystd::List<T>
{
public:
	Queue(std::initializer_list<T> lst) :List<T>(lst)
	{
	}
	Queue() :List<T>()
	{
	}
	const T&front()const 
	{
		return mystd::List<T>::front();
	}
	void push(const T& t_elem)
	{
		this->pushback(t_elem);
	}
	void pop()
	{
		this->popfront();
	}
	size_t size()
	{
		return mystd::List<T>::size();
	}
	bool empty()
	{
		return mystd::List<T>::empty();
	}
};


MYSTD_END
#endif // !MYQUEUE_H


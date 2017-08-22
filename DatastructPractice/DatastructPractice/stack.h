#ifndef  STACK_H
#define  STACK_H

#include"mystd.h"
#include"Vector.h"

MYSTD_BEGIN

template <typename T>
class Stack :private  mystd::Vector<T>
{
public:
	void  push(const T& t_elem)
	{
		this->pushback(t_elem);
	}
	void pop()
	{
		this->popback();
	}
	T& top()
	{
		return this->back();
	}
	const T& top() const
	{
		return this->back();
	}
	bool empty() const
	{
		return mystd::Vector<T>::empty();
	}
	size_t size()const
	{
		return mystd::Vector<T>::size();
	}
};






MYSTD_END



#endif // ! STACK_H

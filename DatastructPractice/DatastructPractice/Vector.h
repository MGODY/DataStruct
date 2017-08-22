#ifndef VECTOR_H
#define VECTOR_H
#include <random>
#include <initializer_list>
#include "mystd.h"
#include <functional>



MYSTD_BEGIN

typedef size_t rank;
template<typename T>
class Vector
{
	#define default_capacity 5
private:
	T* ptr_data_;
	size_t size_;
	size_t capable_;
public: //容器操作方法
	Vector (std::initializer_list<T> lst ):
		ptr_data_(new T[lst.size()*2]),size_(0),capable_(lst.size()*2)
	{
		for (const auto &elem:lst)
		{
			ptr_data_[size_++] = elem;
		}
	}
	Vector(const Vector<T> &V):
		ptr_data_(new T[V.size()*2]),size_(0),capable_(V.size() * 2)
	{
		copyfrom(V.ptr_data_,0,V.size()-1);
	}
	Vector(const Vector<T>&V, rank li, rank lo):
		ptr_data_(new T[V.size() * 2]), size_(0), capable_(V.size() * 2)
	{
		copyfrom(V.ptr_data_, li, lo);
	}
	Vector() :
		ptr_data_(new T[default_capacity]), size_(0), capable_(default_capacity)
	{
	}
	~Vector()
	{
		delete[] ptr_data_;
	}
	void pushback(const T &elem)
	{
		insert(size_, elem);
	}
	void popback()
	{
		erase(size_-1);
	}
	
	const T& front()const
	{
		return ptr_data_[0];
	}
	const T& back()const
	{
		return ptr_data_[size_-1];
	}

	T& front()
	{
		return ptr_data_[0];
	}
	T& back()
	{
		return ptr_data_[size_ - 1];
	}
	void clear()
	{
		delete[] ptr_data_;
		size_ = 0;
		capable_ = 0;
	}
	void insert(rank,const T& );
	void erase(rank );
	bool empty() const
	{
		return size_ <= 0;
	}
	size_t size() const
	{
		return size_;
	}
	const Vector<T> & operator=(const Vector<T> &V)
	{//todo 增加右值引用
		
		if (size_ < V.size())
		{
			delete[] ptr_data_;
			ptr_data_ = new T[V.size() * 2];
		}
		copyfrom(V.ptr_data_, 0, V.size() - 1);
		return *this;
	}
	T& operator[](rank i)const
	{
		return ptr_data_[i];
	}
public: //查找，排序等算法
	void unsort()
	{
		unsort(0, size_ - 1);
	}
	void unsort(rank lo, rank li);	//向量置乱算法
	int deduplicate(); //无序去重
	int uniquify(); //有序去重
	int find(const T&)const; //无序查找
	int find(const T& ,rank  ,rank  )const ;//无序查找
	
	bool isSorted()const;


	void sort(rank lo, rank li);
	void sort()
	{
		sort(0, size_ - 1);
	}
	void bubblesort(rank lo,rank li) //冒泡排序;
	{
		while (!bubble(lo, li--));
	}
	void mergesort(rank lo, rank li); //归并排序;

	int search(const T&)const//有序查找
	{
		search(T, 0, size_ - 1);
	}
	
	int search(const T&, rank lo, rank li)const ;

	//二分查找，在闭区间[a,b]内查找
	int binSearch(const T& ,rank ,rank )const ;
	
	int binSearch(const T& t_elem)const//二分查找
	{
		return binSearch(t_elem, 0, size_ - 1);
	}
	template<typename F>
	void tranverse(  F &);
	void quickSort(rank beg ,rank end)
	{
		if ((end-beg)<2 )
			return;
		rank mid = patition(beg, end);
		quickSort(beg, mid );
		quickSort(mid + 1, end);
		 
	}
private:
	rank patition(rank beg ,rank end )
	{
		swap(ptr_data_[beg], ptr_data_[beg+rand() % (end - beg)]);
		T pivot = ptr_data_[beg];
		rank i = beg,
			j = end-1;
		while(i != j)
		{ 
			while (i != j && ptr_data_[j] >= pivot)
				j--;
			ptr_data_[i] = ptr_data_[j];           //如果i=j 这句话也当然是没问题的。
			while (i != j && ptr_data_[i] <= pivot)
				i++;
			ptr_data_[j] = ptr_data_[i];
		}
		ptr_data_[i] = pivot;
		return i;
	}
	void expand();
	void shrink();
	void copyfrom(const T* const, rank, rank);
	bool bubble(rank lo, rank li);
	void merge(rank lo, rank lm, rank li);
};
template<typename T>
inline void Vector<T>::insert(rank r_ins,const T & t_ins)
{
	expand();

	for (rank i = size_; i != r_ins; i--)
	{
		ptr_data_[i] = ptr_data_[i - 1];
	}
	size_++;
	ptr_data_[r_ins] = t_ins;
	
}

template<typename T>
inline void Vector<T>::erase(rank r_era)
{
	for (rank i = r_era; i != size_ - 1; i++)
	{
		ptr_data_[i] = ptr_data_[i + 1];
	}
	size_--;
	shrink();
}


template<typename T>
inline void Vector<T>::unsort(rank lo, rank li)
{
	static std::default_random_engine e;
	static std::uniform_int_distribution<unsigned> u(0, size_-1);

	for (; lo != li; lo++)
	{
		swap(ptr_data_[lo],ptr_data_[u(e) % (li - lo + 1) + lo]);
	}
}

template<typename T>
inline int Vector<T>::deduplicate()
{
	int old_size = size_;
	int i(1);
	while (i < size_)
	{
		int j = find(ptr_data_[i], 0, i - 1);
		(j == -1) ? i++ : erase(i);
	}
	return old_size - size_;
}

template<typename T>
inline int Vector<T>::uniquify()
{
	size_t oldsize = size_;
	size_t i = 0;
	size_t j = 1;
	while (i!=size_)
	{
		while (ptr_data_[i]==ptr_data_[j])
		{
			j++;
			size_--;
		}
		ptr_data_[i++] = ptr_data_[j++];
	}

}

template<typename T>
inline void Vector<T>::sort(rank lo, rank li)
{

}

template<typename T>
inline int Vector<T>::search(const T&, rank lo, rank li)const
{
	return 0;
}

template<typename T>
inline int Vector<T>::binSearch(const T& t_search,rank lo,rank hi)const 
{
	if (static_cast<int>(lo) > static_cast<int>(hi))
		return -1;
	rank mi = (lo + hi) >> 1;
	if (t_search < ptr_data_[mi])
		binSearch(t_search, lo, mi-1);
	else if (t_search > ptr_data_[mi])
		binSearch(t_search, mi + 1, hi);
	else
		return mi;
}

template<typename T>
int Vector<T>::find(const T& t_elem)const
{
	return find(t_elem, 0, size_ - 1);
}
template<typename T>
inline int Vector<T>::find
	(const T & t_elem,rank lo ,rank li ) const
{//无序查找,查找失败返回-1
	li++;
	while ((lo != li--) && (ptr_data_[li] != t_elem));
	if (li == lo - 1)
		return -1;
	return li;
 }

template<typename T>
inline bool Vector<T>::isSorted() const
{
	for (size_t i = 0; i != size_-1; i++)
	{
		if (ptr_data_[i] > ptr_data_[i + 1])
			return false;
	}
	return true;
}

template<typename T>
template< typename F>
inline void Vector<T>::tranverse( F & f)
{//遍历
	for (size_t i = 0; i != size_; i++)
		f(ptr_data_[i]);
}





template<typename T>
inline void Vector<T>::expand()
{
	if (size_ < (capable_-1))
		return;
	else
	{
		T *ptr_data_t = new T[capable_ * 2];
		for (rank i = 0; i != size_; i++)
		{
			ptr_data_t[i] = ptr_data_[i];
		}
		T*temp = ptr_data_;
		ptr_data_ = ptr_data_t;
		delete[]temp;
		capable_ = capable_ * 2;
	}
}

template<typename T>
inline void Vector<T>::shrink()
{
}

template<typename T>
inline void Vector<T>::copyfrom(const T * const t, rank lo, rank li)
{
	size_ = 0;
	while (lo <= li)
	{
		ptr_data_[size_++] = t[lo++];
	}
}

template<typename T>
inline bool Vector<T>::bubble(rank lo, rank li)
{
	bool is_sorted = true;
	while (lo < li)
	{
		if (ptr_data_[lo] > ptr_data_[lo+1])
		{
			is_sorted = false;
			swap(ptr_data_[lo], ptr_data_[lo+1]);
		}
		lo++;
	}
	return is_sorted;
}

template<typename T>
inline void Vector<T>::mergesort(rank lo, rank li)
{
	if (lo == li)
		return;
	size_t	mi = (lo + li) >> 1;
	mergesort(lo, mi);
	mergesort(mi + 1, li);
	merge(lo, mi, li);
}

template<typename T>
inline void Vector<T>::merge(rank lo, rank lm, rank li)
{
	T * temp = new T[lm - lo+1];
	for (int i = 0; i != lm - lo + 1; i++)
	{
		temp[i] = ptr_data_[lo + i];
	}
	size_t i(0); //指向前半部分
	size_t j(lm+1); //指向后半部分
	size_t k(lo); //
	while ((i!=lm-lo+1)&&(j!=li+1))
	{
		while ((temp[i] <= ptr_data_[j])&&(i!=lm-lo+1))
		{
			ptr_data_[k++] = temp[i++];
		}
		while ((temp[i]>ptr_data_[j])&&(j!=li+1))
		{
			ptr_data_[k++] = ptr_data_[j++];
		}
	}
	while (i!=lm-lo+1)
	{
		ptr_data_[k++] = temp[i++];
	}
	delete[] temp;

}


MYSTD_END
#endif // !VECTOR_H


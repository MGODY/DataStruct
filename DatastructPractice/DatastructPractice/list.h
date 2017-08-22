#ifndef LIST_H
#define LIST_H
#include "mystd.h"
#include<initializer_list>
#include <functional>
MYSTD_BEGIN
template<typename T>
class List;

template<typename T>
class ListNode
{
	friend class List<T>;
	typedef  ListNode<T>* LIST_NODE_PTR_; 
	typedef  ListNode<T>*const  LIST_NODE_CONST_PTR_;
public:
	LIST_NODE_PTR_ ptr_pre_;
	LIST_NODE_PTR_ ptr_suc_;
	T data_;

public:
	ListNode():data_(NULL),
		ptr_pre_(nullptr),
		ptr_suc_(nullptr){}

	ListNode(const T&t_elem, LIST_NODE_PTR_ pre, LIST_NODE_PTR_ suc):
		data_(t_elem),
		ptr_pre_(pre),
		ptr_suc_(suc){}
private:
	LIST_NODE_PTR_ insertAsPred(const T& t_elem)
	{
		LIST_NODE_PTR_ ptr_new_node = new ListNode<T>(t_elem,ptr_pre_,this);
		ptr_pre_->ptr_suc_ = ptr_new_node;
		ptr_pre_ = ptr_new_node;
		return ptr_new_node;
	}
	LIST_NODE_PTR_ insertAsSucc(const T& t_elem)
	{
		LIST_NODE_PTR_ ptr_new_node = new ListNode<T>(t_elem, this,ptr_suc_);
		ptr_suc_->ptr_pre_ = ptr_new_node;
		ptr_suc_ = ptr_new_node;
		return ptr_new_node;
	}
};
template <typename T>
class List
{
public :
	typedef  ListNode<T>* LIST_NODE_PTR_;
	typedef  ListNode<T>*const  LIST_NODE_CONST_PTR_;
	typedef const ListNode<T> *const CONST_LIST_NODE_CONST_PTR_;
	typedef const ListNode<T>* CONST_LIST_NODE_PTR;
public:
	List():first_node_(new ListNode<T>),
		last_node_(new ListNode<T>),
		size_(0)
	{
		first_node_->ptr_suc_ = last_node_;
		last_node_->ptr_pre_ = first_node_;
	}
	List(std::initializer_list<T> elem_list):List<T>()
	{
		LIST_NODE_PTR_ p = first_node_;
		for (const auto &elem : elem_list)
		{
			pushback(elem);
		}
	}
	List(const List<T> &lst) :List<T>()
	{
		CONST_LIST_NODE_PTR ptr_copy = lst.begin();
		clear();
		for (ptr_copy = lst.begin();ptr_copy != lst.end();
			ptr_copy=ptr_copy->ptr_suc_)
		{
			pushback(ptr_copy->data_);
		}
	}
	~List()
	{
		clear();
		delete first_node_;
		delete last_node_;
	}
	size_t size() const
	{
		return size_;
	}
	bool empty()const
	{
		return (size_ > 0) ? false : true;
	}
	void pushback(const T& t_push)
	{
		last_node_->insertAsPred(t_push);
		++size_;
	}
	void pushfront(const T& t_push)
	{
		first_node_->insertAsSucc(t_push);
		++size_;
	}
	void popback()
	{
		erase(last_node_->ptr_pre_);
	}
	void popfront()
	{
		erase(first_node_->ptr_suc_);
	}
	LIST_NODE_PTR_ begin()
	{
		return first_node_->ptr_suc_;
	}
	LIST_NODE_PTR_ end()
	{
		return last_node_;
	}
	CONST_LIST_NODE_CONST_PTR_ begin()const
	{
		return first_node_->ptr_suc_;
	}
	CONST_LIST_NODE_CONST_PTR_ end()const
	{
		return last_node_;
	}
	T& front()
	{
		return first_node_->ptr_suc_->data_;
	}
	T& back()
	{
		return last_node_->ptr_pre_->data_;
	}
	const T& front()const
	{
		return first_node_->ptr_suc_->data_;
	}
	const T& back()const
	{
		return last_node_->ptr_pre_->data_;
	}
	LIST_NODE_PTR_ insert(const T&t,LIST_NODE_PTR_ p)
	{
		LIST_NODE_PTR_ p_temp= p->insertAsSucc(t);
		++size_;
		return p_temp;
	}
	LIST_NODE_PTR_ insertBefore(const T&t, LIST_NODE_PTR_ p)
	{
		LIST_NODE_PTR_ p_temp = p->insertAsPred(t);
		++size_;
		return p_temp;
	}
	void clear()
	{
		LIST_NODE_PTR_ p = first_node_->ptr_suc_ ;
		while ( p != last_node_)
		{
			p = erase(p);
		}
	}
	LIST_NODE_PTR_ erase(LIST_NODE_PTR_ p)
	{
		LIST_NODE_PTR_ temp_ptr(p->ptr_suc_);
		p->ptr_pre_->ptr_suc_ = p->ptr_suc_;
		p->ptr_suc_->ptr_pre_ = p->ptr_pre_;
		delete p;
		p = nullptr;
		--size_;
		return temp_ptr;
	}

	List<T> & operator=(const List<T>& lst)
	{
		if (this != &lst)
		{
			List<T> lst_temp(lst);
			swap(first_node_ , lst_temp.first_node_);
			swap(last_node_ , lst_temp.last_node_);
			size_ = lst_temp.size();
		}
		return *this;
	}
	template<typename F>
	void tranverse(F & f)
	{
		for (LIST_NODE_PTR_ ptr = begin(); ptr != last_node_; ptr = ptr->ptr_suc_)
		{
			f(ptr->data_);
		}
	}
public://����������㷨��

	//��������Ψһ��
	size_t deduplicate() 
	{
		size_t n = 0;
		LIST_NODE_PTR_ p = first_node_->ptr_suc_;
		while (p != last_node_)
		{
			if (findReverse(p->data_,begin(),p)!= begin()->ptr_pre_)
			{
				p=erase(p);
				++n;
			}else
			{
				p = p->ptr_suc_;
			}
		}
		return n;
	}
	//��������Ψһ��
	size_t uniquify() 
	{
		size_t n(0);
		LIST_NODE_PTR_ p = begin()->ptr_suc_;
		while ( p != last_node_)
		{
			if (p->data_ == p->ptr_pre_->data_)
			{
				p = erase(p);
				++n;
			}else
			{
				p = p->ptr_suc_;
			}
		}
		return n;
	}

	//��������㷨,����������˵������Ҫ��λ��ȷ����ǰ��λ�ã����Ը��Ӷ�Ϊn^2;
	void unsort() 
	{
		static std::default_random_engine e;
		static std::uniform_int_distribution<unsigned> u(0, size_ - 1);
		size_t n(size_);
		LIST_NODE_PTR_ p_swap;
		LIST_NODE_PTR_ p = begin();
		size_t i(0);
		while (p != end()->ptr_pre_)
		{
			i = u(e) % n;
			p_swap = p;
			while (i--)
			{
				p_swap = p_swap->ptr_suc_;
			}
			swap(p, p_swap);
			p = p->ptr_suc_;
			--n;
		}
	}

	//ͨ�����������ڵ��λ�����������ݡ�
	void swap(LIST_NODE_PTR_ &p, LIST_NODE_PTR_ &p2)
	{
		if (p == p2)
			return;

		//��p��p2 ���ڵ�ʱ������֮��û�������Ľڵ���Ҫ���⴦��
		if(p->ptr_suc_ == p2)
		{
			swapNeighbor(p, p2);
			return;
		}
		if (p2->ptr_suc_ == p)
		{
			swapNeighbor(p2, p);
			return;
		}

		//��p ��p2 ������ʱ��ֱ�ӽ������ǵ�ǰ������Լ� �������Ƿֱ��ǰ����̽ڵ�����ݡ�
		p->ptr_pre_->ptr_suc_ = p2;
		p->ptr_suc_->ptr_pre_ = p2;

		p2->ptr_pre_->ptr_suc_ = p;
		p2->ptr_suc_->ptr_pre_ = p;

		LIST_NODE_PTR_ temp = p->ptr_pre_;

		p->ptr_pre_ = p2->ptr_pre_;
		p2->ptr_pre_ = temp;

		temp = p->ptr_suc_;
		p->ptr_suc_ = p2->ptr_suc_;
		p2->ptr_suc_ = temp;

		temp = p;
		p = p2;
		p2 = temp;
	}

	//�������ж�
	bool issorted()const 
	{
		for (LIST_NODE_PTR_ p = begin(); p != end()->ptr_pre_; p = p->ptr_suc_)
		{
			if (p->data_ > p->ptr_suc_->data_)
			{
				return false;
			}
		}
		return true;
	}

	//�������(����������ң����Ӷ�n)
	//beg ��ָ���һ��Ԫ�أ�end��ָ�����һ��Ԫ�صĺ�һ��Ԫ��,��[beg,end)
	LIST_NODE_PTR_ findReverse(const T& elem , LIST_NODE_PTR_ beg, LIST_NODE_PTR_ end)const// �������
	{
		
		LIST_NODE_PTR_ ptr = end->ptr_pre_;
		for (; ptr != beg->ptr_pre_; ptr = ptr->ptr_pre_)
		{
			if (ptr->data_ == elem)
			{
				return ptr;
			}
		}
		return beg->ptr_pre_;
	} 

	//˳�����(����������ң����Ӷ�n)
	//beg ��ָ���һ��Ԫ�أ�end��ָ�����һ��Ԫ�صĺ�һ��Ԫ��,��[beg,end)
	LIST_NODE_PTR_ findPositiveOrder(const T& elem, LIST_NODE_PTR_ beg, LIST_NODE_PTR_ end)const// �������
	{
		for (LIST_NODE_PTR_ ptr = beg; ptr != end; ptr = ptr->ptr_suc_)
		{
			if (ptr->data_ == elem)
			{
				break;
			}
		}
		return ptr;
	}
	//��������������ң����ز����ڲ���ֵ�ĵ�һ��Ԫ��
	LIST_NODE_PTR_ search(const T&elem, LIST_NODE_PTR_ beg_ptr, LIST_NODE_PTR_ end_ptr) const //�������
	{
		LIST_NODE_PTR_ p = end_ptr;
		while (p != beg_ptr->ptr_pre_)
		{
			p = p->ptr_pre_;
			if (elem >= p->data_)
			{
				break;
			}
		}
		return p;
	}
	//�������򣬸��Ӷ�n^2
	void insertSort( LIST_NODE_PTR_ beg_ptr, LIST_NODE_PTR_ end_ptr)
	{
		LIST_NODE_PTR_ header = beg_ptr->ptr_pre_;
		LIST_NODE_PTR_ p = beg_ptr->ptr_suc_;

		while (p != end_ptr)
		{
			insert(p->data_, search(p->data_, header->ptr_suc_, p));
			p = erase(p);
		}
	}
	void selectSort(LIST_NODE_PTR_ beg_ptr, LIST_NODE_PTR_ end_ptr)
	{
		LIST_NODE_PTR_ header = beg_ptr->ptr_pre_;
		LIST_NODE_PTR_ front_of_sorted = end_ptr;
		LIST_NODE_PTR_ finded_max;
		while (front_of_sorted != header->ptr_suc_)
		{
			finded_max = findMax(header->ptr_suc_, front_of_sorted);
			front_of_sorted = insertBefore(finded_max->data_, front_of_sorted);
			erase(finded_max);
		}
	}
	//�鲢����
	void mergeSort(LIST_NODE_PTR_ beg_ptr, LIST_NODE_PTR_ end_ptr)
	{
		size_t n(0);
		LIST_NODE_PTR_  ptr = beg_ptr;
		while (ptr != end_ptr)
		{
			++n;
			ptr = ptr->ptr_suc_;
		}
		mergeSort(beg_ptr, end_ptr, n);
	}
	//�������������ֵ.
	LIST_NODE_PTR_ findMax(LIST_NODE_PTR_ beg_ptr, LIST_NODE_PTR_ end_ptr)
	{
		LIST_NODE_PTR_ bigger = beg_ptr;
		LIST_NODE_PTR_ p = beg_ptr;
		while (p != end_ptr)
		{
			if (p->data_ > bigger->data_)
			{
				bigger = p;
			}
			p = p->ptr_suc_;
		}
		return bigger;
	}
protected:
	void swapNeighbor(LIST_NODE_PTR_ &p, LIST_NODE_PTR_ &p2)
	{
		p->ptr_pre_->ptr_suc_ = p2;
		p2->ptr_suc_->ptr_pre_ = p;

		p->ptr_suc_ = p2->ptr_suc_;
		p2->ptr_pre_ = p->ptr_pre_;
		p->ptr_pre_ = p2;
		p2->ptr_suc_ = p;

		LIST_NODE_PTR_ temp_ptr(p);
		p = p2;
		p2 = temp_ptr;
	}
	//�鲢�������
	void mergeSort(LIST_NODE_PTR_ &beg_ptr, LIST_NODE_PTR_ end_ptr,size_t n)
	{
		if (n < 2)
			return;
		size_t mid = n >> 1;
		LIST_NODE_PTR_ mid_ptr = beg_ptr;
		size_t mid_temp= mid;
		while (mid_temp--)
			mid_ptr = mid_ptr->ptr_suc_;
		mergeSort(beg_ptr,mid_ptr,mid);
		mergeSort(mid_ptr, end_ptr, n - mid);
		merge(beg_ptr, mid_ptr, end_ptr);
	}
	//��·����鲢
	void merge(LIST_NODE_PTR_ &beg_ptr, LIST_NODE_PTR_ &mid_ptr, LIST_NODE_PTR_ &end_ptr)
	{
		LIST_NODE_PTR_ header = beg_ptr->ptr_pre_;
		LIST_NODE_PTR_ sorted_ptr = beg_ptr->ptr_pre_;
		LIST_NODE_PTR_ end_of_first_ptr = mid_ptr->ptr_pre_;
		LIST_NODE_PTR_ second_ptr = mid_ptr;
		while (sorted_ptr != end_of_first_ptr && second_ptr != end_ptr)
		{
			while (sorted_ptr->ptr_suc_->data_ <= second_ptr->data_ &&
				sorted_ptr != end_of_first_ptr)
			{
				sorted_ptr = sorted_ptr->ptr_suc_;
			}
			if (sorted_ptr == end_of_first_ptr)
				break;
			while (second_ptr->data_ <= sorted_ptr->ptr_suc_->data_ &&
				second_ptr != end_ptr)
			{
				mid_ptr = mid_ptr->ptr_pre_;
				insert(second_ptr->data_, sorted_ptr);
				second_ptr = erase(second_ptr);
				
			}	
		}
		beg_ptr = header->ptr_suc_;

	}
private:
	LIST_NODE_PTR_ first_node_;
	LIST_NODE_PTR_ last_node_;
	size_t size_;

};













MYSTD_END
#endif // !LIST_H


#ifndef BINSEARCHTREE_H
#define BINSEARCHTREE_H
#include "mystd.h"
#include "BinTree.h"
MYSTD_BEGIN

template<typename K,typename V>
class Entry
{
public:
	K key;
	V value;
	Entry(const K &k,cosnt V &v):key(k),value(v){}
	Entry(const Entry<K,V> &entry):key(entry.key),value(entry.value){}
	bool operator<(const  Entry<K, V> &entry)
	{
		return key < entry.key;
	}
	bool operator>(const  Entry<K, V> &entry)
	{
		return key > entry.key;
	}
	bool operator==(const Entry<K, V>&entry)
	{
		return key == entry.key;
	}
	bool operator!=(const Entry<K, V>&entry)
	{
		return !(*this == entry);
	}
	bool operator<=(const  Entry<K, V> &entry)
	{
		return key <= entry.key;
	}
	bool operator>=(const  Entry<K, V> &entry)
	{
		return key >= entry.key;
	}
};

template<typename T>
class BST:public mystd::BinTree<T>
{
public:
	BST():BinTree<T>()
	{

	}


private:

};



MYSTD_END

#endif // !BINSEARCHTREE_H

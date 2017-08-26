#ifndef BINTREE_H
#define BINTREE_H
#include"mystd.h"
#include"myexception.h"
#include"myqueue.h"
#include<functional>
#include<initializer_list>
MYSTD_BEGIN

template <typename T>
class BinTree;
template <typename T>
class BinNode;

#define isRchild(x) ((!x ||!(x->ptr_parent_))?false:(x->ptr_parent_->ptr_Rchild_==x)?true:false)
#define isLchild(x) ((!x ||!(x->ptr_parent_))?false:(x->ptr_parent_->ptr_Lchild_==x)?true:false)

template <typename T>
inline BinNode<T> *& fromParentTo(BinNode<T> *t)
{

	if (t == nullptr)
	{
		throw BinNodePtrError("BinNodePtrError, ptr is nullptr");
	}
	else
	{
		if (t->parent()->Lchild() == t || t->parent()->Rchild() == t)
		{
			return t->parent()->Lchild() == t ? t->parent()->Lchild() : t->parent()->Rchild();
		}
		throw BinNodePtrError("BinNodePtrError,  no match Lchild or Rchild ");
	}	
}

enum class RBcolor
{
	RED,
	BLACK
};
enum class TraverseType
{
	RECURSIVE,
	ITERATION
};

template <typename T>
class BinNode
{

public:
	friend class BinTree<T>;
	typedef BinNode<T>*  node_position;
	BinNode(const T& data, node_position p = nullptr,
		node_position l = nullptr, node_position r = nullptr,
		size_t h = 0, RBcolor color = RBcolor::RED) :
		data_(data),
		ptr_parent_(p),
		ptr_Lchild_(l),
		ptr_Rchild_(r),
		height_(h),
		color_(color)
	{}
	T & data()
	{
		return data_;
	}
	const T& data()const
	{
		return data_;
	}
	node_position& parent()
	{
		return ptr_parent_;
	}
	node_position& Lchild()
	{
		return ptr_Lchild_;
	}
	node_position& Rchild()
	{
		return ptr_Rchild_;
	}
	const node_position& parent() const
	{
		return ptr_parent_;
	}
	const node_position& Lchild() const
	{
		return ptr_Lchild_;
	}
	const node_position& Rchild() const
	{
		return ptr_Rchild_;
	}

public:
	//�����Ըýڵ�Ϊ�����Ľڵ�������
	size_t size()
	{
		return 1 + (ptr_Lchild_ == nullptr ? 0 : ptr_Lchild_->size() +
			ptr_Rchild_ == nullptr ? 0 : ptr_Rchild_->size());
	}

	//������
	template <typename F>
	void traversePre(F &f, TraverseType traverse = TraverseType::RECURSIVE)
	{
		switch (traverse)
		{
		case TraverseType::RECURSIVE:
			traversePrewithRec(this, f);
			break;
		case TraverseType::ITERATION:
			traversePrewithIter(this, f);
			break;
		default:
			break;
		}
	}
	template <typename F>
	void traverseMid(F &f, TraverseType traverse = TraverseType::RECURSIVE)
	{
		switch (traverse)
		{
		case TraverseType::RECURSIVE:
			traverseMidWithRec(this, f);
			break;
		case TraverseType::ITERATION:
			traverseMidWithIter(this, f);
			break;
		default:
			break;
		}
	}
	template <typename F>
	void traverseBack(F &f, TraverseType traverse = TraverseType::RECURSIVE)
	{
		switch (traverse)
		{
		case TraverseType::RECURSIVE:
			traverseBackWithRec(this, f);
			break;
		case TraverseType::ITERATION:
			traverseBackWithIter(this, f);
			break;
		default:
			break;
		}
	}
	template <typename F>
	void traverseLevel(F &f, TraverseType traverse = TraverseType::RECURSIVE)
	{
		switch (traverse)
		{
		case TraverseType::RECURSIVE:
			traverseLevelWithRec(this, f);
			break;
		case TraverseType::ITERATION:
			traverseLevelWithIter(this, f);
			break;
		default:
			break;
		}
	}

public://����������
	bool operator==(const BinNode<T> &node) const
	{
		return data_ == node.data_;
	}
	bool operator!=(const BinNode<T> &node)const
	{
		return !(*this == node);
	}
	bool operator<(const BinNode<T> &node)const
	{
		return data_ < node.data_;
	}
	bool operator>(const BinNode<T> &node)const
	{
		return !(*this < node);
	}
	bool operator>=(const BinNode<T> &node)const
	{
		return data_ >= node.data_;
	}
	bool operator <=(const BinNode<T> &node)const
	{
		return data_ <= node.data_;
	}
private:
	T data_;
	node_position ptr_parent_;
	node_position ptr_Lchild_;
	node_position ptr_Rchild_;
	size_t height_;
	RBcolor color_;

protected:
	template<typename F>
	void traversePrewithRec(node_position p_node, F&f)
	{
		if (!p_node)
			return;
		f(p_node->data_);
		traversePrewithRec(p_node->ptr_Lchild_, f);
		traversePrewithRec(p_node->ptr_Rchild_, f);
	}
	template<typename F>
	void traversePrewithIter(node_position p_node, F&f)
	{//todo
		mystd::Stack<node_position> p_s;
		while (true)
		{
			goLeftAlong(&p_s, p_node, f);
			if (p_s.empty())
				break;
			p_node = p_s.top();
			p_s.pop();
		}
	}
	template<typename F>
	void goLeftAlong(mystd::Stack<node_position> * p_s, node_position p_node, F&f)
	{
		while (p_node)
		{
			f(p_node->data_);
			if (p_node->Rchild())
			{
				p_s->push(p_node->Rchild());
			}
			p_node = p_node->Lchild();
		}
	}
	template<typename F>
	void traverseMidWithRec(node_position p_node, F&f)
	{
		if (!p_node)
			return;
		traverseMidWithRec(p_node->ptr_Lchild_, f);
		f(p_node->data_);
		traverseMidWithRec(p_node->ptr_Rchild_, f);
	}
	template<typename F>
	void traverseMidWithIter(node_position p_node, F&f)
	{
		mystd::Stack<node_position> node_stack;
		while (true)
		{
			goLeftEnd(&node_stack, p_node);
			if (node_stack.empty())
				break;
			f((p_node = node_stack.top())->data_);
			node_stack.pop();
			p_node = p_node->ptr_Rchild_;
		}
	}
	void goLeftEnd(mystd::Stack<node_position> *p_stack, node_position p_node)
	{
		while (p_node)
		{
			p_stack->push(p_node);
			p_node = p_node->ptr_Lchild_;
		}
	}
	template<typename F>
	void traverseBackWithRec(node_position p_node, F&f)
	{
		if (!p_node)
			return;
		traverseBackWithRec(p_node->ptr_Lchild_, f);
		traverseBackWithRec(p_node->ptr_Rchild_, f);
		f(p_node->data_);
	}
	template<typename F>
	void traverseBackWithIter(node_position p_node, F&f)
	{
		mystd::Stack<node_position> s_node;
		s_node.push(p_node);
		//node_position p;
		while (!s_node.empty())
		{
			if (s_node.top() != p_node->ptr_parent_)
				goHighestOfLeft(&s_node);
			f((p_node =  s_node.top())->data_);
			s_node.pop();
		}
	}
	void goHighestOfLeft(mystd::Stack<node_position> * sp_node)
	{
		node_position p_node;
		while (p_node =sp_node->top())
		{
			if (p_node->ptr_Lchild_)
			{
				if (p_node->ptr_Rchild_)
					sp_node->push(p_node->ptr_Rchild_);
				sp_node->push(p_node->ptr_Lchild_);
			}else
			{
				sp_node->push(p_node->ptr_Rchild_);
			}
		}
		sp_node->pop();
	}
	template<typename F>
	void traverseLevelWithRec(node_position p_node, F&f)
	{
		if (p_node)
		{
			int i = 0;
			while (traverseLevelWithRec_loop(p_node, i, f))
			{
				++i;
			}
		}
	}
	template<typename F>
	bool traverseLevelWithRec_loop(node_position p_node, int depth, F&f)
	{
		if (!p_node)
			return false;

		if (depth < 0)
		{//���˸ô���˵����p_node �� depth=0ʱ�� node�� Lchild���� Rchild�����Ҳ�Ϊ�ա�
			return true;
		}
		if (depth == 0)
		{
			f(p_node->data_);
		}
		bool l = traverseLevelWithRec_loop(p_node->ptr_Lchild_, depth - 1, f);
		bool r = traverseLevelWithRec_loop(p_node->ptr_Rchild_, depth - 1, f);
		return l || r;
	}
	template<typename F>
	void traverseLevelWithIter(node_position p_node, F&f)
	{
		traverseLevelRetLast(f);
	}
public:
	//���ظýڵ��ֱ�Ӻ��
	node_position suc()
	{
		node_position p_node = this;
		if (ptr_Rchild_)
		{
			p_node = ptr_Rchild_;
			while (p_node->ptr_Lchild_)
				p_node = p_node->ptr_Lchild_;
			return p_node;
		}else
		{
			while (isRchild(p_node))
				p_node = p_node->ptr_parent_;
			return p_node->ptr_parent_;
		}
	}
	node_position pre()
	{
		node_position p_node = this;
		if (ptr_Lchild_)
		{
			p_node = ptr_Lchild_;
			while (p_node->ptr_Rchild_)
				p_node = p_node->ptr_Rchild_;
			return p_node;
		}
		else
		{
			while (isLchild(p_node))
				p_node = p_node->ptr_parent_;
			return p_node->ptr_parent_;
		}
	}
	template<typename F>
	node_position traverseLevelRetLast(F&f)
	{
		mystd::Queue<node_position> que_node;
		que_node.push(this);
		while (!que_node.empty())
		{
			que_node.front()->ptr_Lchild_ ? (que_node.push(que_node.front()->ptr_Lchild_)) : (void)true;
			que_node.front()->ptr_Rchild_ ? (que_node.push(que_node.front()->ptr_Rchild_)) : (void)true;
			if (que_node.size() == 1)
			{
				f(que_node.front()->data_);
				return que_node.front();
			}
			f(que_node.front()->data_);
			que_node.pop();
		}
	}
protected:

	node_position insertAsLchild(const T& t_elem)
	{
		if (!ptr_Lchild_)
		{
			ptr_Lchild_ = new BinNode<T>(t_elem, this);
			return ptr_Lchild_;
		}else
		{
			return nullptr;
		}
	}
	node_position insertAsRchild(const T& t_elem)
	{
		if (!ptr_Rchild_)
		{
			ptr_Rchild_ = new BinNode<T>(t_elem, this);
			return ptr_Rchild_;
		}
		else
		{
			return nullptr;
		}
	}
};


template<typename T>
std::function<void(const T&) > fun_ = [](const T& t) {};

template <typename T>
class BinTree
{
public:
	typedef typename BinNode<T>* node_position;

	//��һ��Ԫ�س�ʼ��
	BinTree():root_(nullptr),size_(0)
	{

	}
	BinTree(const T& t_elem):root_(new  BinNode<T>(t_elem)),size_(1)
	{

	}
	//ʹ��һ���Ѿ����ڵĽڵ㹹����(�����߱�֤�ýڵ��Ѿ����Ѿ����ڵ�����ժ������)
	//���ýڵ���Ϊ��
	BinTree(node_position p)
	{
		root_ = p;
		size_ = p->size();
	}
	//Ϊ�˲��Է��� Ĭ�ϲ��뷽ʽΪ������ʵķ�ʽ
	BinTree(std::initializer_list<T> lst)
	{
		mystd::Queue<node_position> que_node;
		for (const auto &elem : lst)
		{
			if (!size_)
			{
				insertAsRoot(elem);
				que_node.push(root_);
			}else
			{
				if (size_ & 1)
				{
					que_node.push(insertAsLChild(que_node.front(),elem));
				}else
				{
					que_node.push(insertAsRChild(que_node.front(), elem));
					que_node.pop();
				}
			}
		}
	}
	~BinTree()
	{
		clear();
	}
	node_position  root()const
	{
		return root_;
	}
	size_t size()const
	{
		return size_;
	}
	bool empty()const
	{
		return size_ > 0 ? false : true;
	}
	void clear()
	{
		deleteChildTree(root_);
		size_ = 0;
		root_ = nullptr;
	}

	//ɾ������
	//template <typename F  = fun_<T> >
	void deleteChildTree(node_position p , std::function<void(const T&)> & freee = fun_<T> )
	{
		if (!p)
			return;
		deleteChildTree(p->ptr_Lchild_, freee);
		deleteChildTree(p->ptr_Rchild_, freee);
		freee(p->data_);
		--size_;
		delete p;
		p = nullptr;
	}

	node_position insertAsRoot(const T& t_elem)
	{
		if (!root_)
		{
			size_ = 1;
			root_ = new BinNode<T>(t_elem);
		}
		return root_;
	}
	//�ڸ�����һ���ڵ��ϲ�������(���ýڵ��Ƿ��������Ҫ�ķ�n���Ӷȵ�ʱ�䣬���� \
	�����߱�֤�ýڵ��Ѿ��������С�����ֻ���ýڵ��Ƿ��пյ�λ��������.
	node_position insertAsLChild(node_position p ,const T& t_elem)
	{
		if (p == nullptr)
			throw BinNodePtrError("BinNodePtrError, insert Lchild to a nullptr");
		if( p->Lchild())
			throw BinNodePtrError("BinNodePtrError, insert Lchild to a exsist_Lchild ptr");

		p->insertAsLchild(t_elem);
		++size_;
		updataHeightAbove(p);
		return p->Lchild();
	}
	//�ڸ�����һ���ڵ��ϲ����Һ���(���ýڵ��Ƿ��������Ҫ�ķ�n���Ӷȵ�ʱ�䣬���� \
		�����߱�֤�ýڵ��Ѿ��������С�����ֻ���ýڵ��Ƿ��пյ�λ��������.
	node_position insertAsRChild(node_position p, const T& t_elem)
	{
		if (p == nullptr)
			throw BinNodePtrError("BinNodePtrError, insert Rchild to a nullptr");
		if (p->Rchild())
			throw BinNodePtrError("BinNodePtrError, insert Rchild to a exsist_Rchild ptr");
		p->insertAsRchild(t_elem);
		++size_;
		updataHeightAbove(p);
		return p->Rchild();
	}

	//��������
	node_position insertAsLTree(node_position p_node , BinTree * p_tree)
	{
		if(p_node == nullptr)
			throw BinNodePtrError("BinNodePtrError, insert LTree to a nullptr");
		if (p_node->Lchild())
			throw BinNodePtrError("BinNodePtrError, insert LTree to a exsist_Lchild ptr");
		p_node->ptr_Lchild_ = p_tree->root_;
		if (p_node->ptr_Lchild_)
			p_node->ptr_Lchild_->ptr_parent_ = p_node;
		size_ += p_tree->size_;
		updataHeightAbove(p_node);
		//����p_tree
		p_tree->size_ = 0;
		p_tree->root_ = nullptr;
		return p_node->ptr_Lchild_;
	}

	//��������
	node_position insertAsRTree(node_position p_node, BinTree * p_tree)
	{
		if (p_node == nullptr)
			throw BinNodePtrError("BinNodePtrError, insert RTree to a nullptr");
		if (p_node->Rchild())
			throw BinNodePtrError("BinNodePtrError, insert RTree to a exsist_Rchild ptr");

		p_node->ptr_Rchild_ = p_tree->root_;
		if (p_node->ptr_Rchild_)
			p_node->ptr_Rchild_->ptr_parent_ = p_node;
		size_ += p_tree->size_;
		updataHeightAbove(p_node);

		p_tree->size_ = 0;
		p_tree->root_ = 0;
		return p_node->ptr_Rchild_;

	}
	//���½ڵ㼰�����ȵ�����
	virtual void updataHeightAbove(node_position p)
	{
		while (p != nullptr)
		{
			p->height_ = 1 + (height_of(p->ptr_Lchild_) > height_of(p->ptr_Rchild_) ?   \
				height_of(p->ptr_Lchild_) : height_of(p->ptr_Rchild_));
			p = p->ptr_parent_;
		}
	}
	//�������������
	BinTree<T>* secede(BinNode<T>* p_node)
	{
		if (!p_node)
		{
			return new BinTree<T>;
		}
		size_ -= p_node->size();
		fromParentTo(p_node) = nullptr;
		updataHeightAbove(p_node->ptr_parent_);
		p_node->ptr_parent_ = nullptr;
		return new BinTree<T>(p_node);
	}

	//��������������
	template <typename F>
	void traversePre(F &f, TraverseType traverse = TraverseType::RECURSIVE)
	{
		root_->traversePre(f, traverse);
	}
	template <typename F>
	void traverseMid(F &f, TraverseType traverse = TraverseType::RECURSIVE)
	{
		root_->traverseMid(f, traverse);
	}
	template <typename F>
	void traverseBack(F &f, TraverseType traverse = TraverseType::RECURSIVE)
	{
		root_->traverseBack(f, traverse);
	}
	template <typename F>
	void traverseLevel(F &f, TraverseType traverse = TraverseType::RECURSIVE)
	{
		root_->traverseLevel(f, traverse);
	}
	node_position fir_of_mid()
	{
		if (!root_)
			return nullptr;
		node_position p_node = root_;
		while (p_node->ptr_Lchild_)
			p_node = p_node->ptr_Lchild_;
		return p_node;
	}
private:
	//�յĽڵ�ĸ߶�Ϊ-1��
	int height_of(node_position p_node)
	{
		return p_node ? p_node->height_ : -1;
	}
	node_position root_;
	size_t size_;
};














MYSTD_END

#endif
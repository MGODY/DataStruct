#include"recursive_practic.h"
#include<iostream>
#include<windows.h>
#include<time.h>
#include"matrix.h"
#include"Vector.h"
#include<algorithm>
#include<list>    
#include<deque>
#include"list.h"
#include"trajectory.h"
#include"trajectory_test.h"
#include"stack_practice.h"
#include"BinTree.h"
#include <set>
#include<stack>
using namespace std;
void expFuntionTest();
void fibnacciTest(size_t);
void hanoiTest(size_t );
void myListTest();
void myVectorTest();
template<typename T>
void showVector(const std::vector<T> & V);
template<typename T>
void showVector(const mystd::Vector<T> &V);

struct PrintInt
{
	int n = 0;
	void operator()(int i)
	{
		cout << i  <<" ";
		n++;
	}
};
void print_f(int i)
{
	cout << i << " ";
}
template<typename T>
void showList(const mystd::List<T> & lst)
{
	cout << "lst size为：" << lst.size() << endl << "lst 内容为： " << endl;
	for (auto ptr = lst.begin(); ptr != lst.end(); ptr = ptr->ptr_suc_)
	{
		cout << ptr->data_ << " ";
	}
	cout << endl;
}
void print_point(const VehicleState &t)
{
	cout << "the target's state is " << endl <<
		"v = " << t.v << " omege = " << t.omege
		<< " theta = " << t.theta << " xr = " << t.x
		<< " yr = " << t.y << endl;

}
template <typename T>
void printStack(const mystd::Stack<T> &s1)
{
	mystd::Stack<T> s(s1);
	while (!s.empty())
	{
		cout << s.top() <<" ";
		s.pop();
	}
	cout << endl;
}
template<typename T>
void printBinTree(mystd::BinTree<T>* tree)
{
	tree->traverseLevel([](const T&t_elem) {std::cout << t_elem << " "; });
	cout << endl;
}
void myBinTreeTest();
class SearchFlag
{
public:
	SearchFlag(int a):count(0),begin(a)
	{

	}
	int count = 0;
	int begin;
	std::vector<std::string> solution;
};
int  findMatch(std::stack<SearchFlag>*stack, 
	const set<string>& dict, const string& str, std::stack<std::string> &result,
	std::stack<std::string>& best_result,
	int position)
{
	SearchFlag search_flag(position);
	for (auto element : dict)
	{
		if (element.size() >( str.size() - position))
			continue;
		int i = 0;
		while ( i != element.size())
		{
			if (str[position + i] != element[i])
				break;
			i++;
		}
		if (i == element.size())
		{
			if (str.size() == (position + element.size()))
			{
				if (result.size() < best_result.size())
					best_result = result;
			}
			search_flag.count = search_flag.count + 1;
			search_flag.solution.push_back(element);
		}
	}
	if (search_flag.count == 0)
	{
		if (!stack->empty())
		{
			while (!stack->empty())
			{
				if (stack->top().count < 0)
				{
					stack->pop();
					result.pop();
					
				}else
				{
					stack->top().count--;
					result.pop();
					int s = stack->top().solution[stack->top().count].size();
					result.push(stack->top().solution[stack->top().count]);
					return stack->top().begin + s;
				}
			}
			if (stack->empty())
				return 0;
		}
	}
	else
	{
		stack->push(search_flag);
		int s = stack->top().solution[stack->top().count].size();
		result.push(stack->top().solution[stack->top().count]);
		return stack->top().begin + s;
	}


}
std::stack<std::string> mincut(const string& str, const set<string>& dict)
{
	std::stack<std::string> result;
	std::stack<std::string> best_result;
	std::stack<SearchFlag> search_stack;
	int position = 0;
	do {
		position =findMatch(&search_stack, dict, str,result, best_result,position);
	} while (!search_stack.empty());
	return best_result;
}
int main()
{
	string strS;
	string dictStr;
	int nDict;
	set<string> dict;
	std::stack<std::string> solution;
	cin >> strS;
	cin >> nDict;
	for (int i = 0; i < nDict; i++)
	{
		cin >> dictStr;
		dict.insert(dictStr);
	}
	solution = mincut(strS, dict);

	std::deque<string> s;

	while (!solution.empty())
	{
		s.push_front(solution.top());
		cout << solution.top();
	}
	/////
	system("pause");
}
void myBinTreeTest()
{
	//二叉树层次构建和遍历打印测试；
	/*
	1
	2         3
	4     5    6   7
	8  9  10 11
	*/
	mystd::BinTree<int> bintree1{ 1,2,3,4,5,6,7,8,9,10,11 };
	cout << "bintree1 的内容为： " << endl;
	printBinTree(&bintree1);

	/*
	100
	101     102
	103   104
	*/
	mystd::BinTree<int> bintree2{ 100,101,102,103,104 };
	cout << "bintree2 的内容为： " << endl;
	printBinTree(&bintree2);

	//二叉树子树接入测试
	auto fun_ = [](int a) {cout << a << " "; };
	auto last_of_bintree1 = bintree1.root()->traverseLevelRetLast(fun_);
	cout << endl;
	bintree1.insertAsLTree(last_of_bintree1, new mystd::BinTree<int>{ 12,13,14,15,16 });
	cout << "左插入一个树 后bintree1 的内容为： " << endl;
	last_of_bintree1 = bintree1.root()->traverseLevelRetLast(fun_);
	cout << endl;

	bintree1.insertAsRTree(last_of_bintree1, new mystd::BinTree<int>{ 17,18,19,20,21,22 });
	cout << "右插入一个树 后bintree1 的内容为： " << endl;
	last_of_bintree1 = bintree1.root()->traverseLevelRetLast(fun_);
	cout << endl;

	//二叉树节点接入测试

	bintree1.insertAsLChild(last_of_bintree1, 23);
	cout << "左插入一个节点 后bintree1 的内容为： " << endl;
	last_of_bintree1 = bintree1.root()->traverseLevelRetLast(fun_);
	cout << endl;

	bintree1.insertAsRChild(last_of_bintree1, 24);
	cout << "右插入一个节点 后bintree1 的内容为： " << endl;
	last_of_bintree1 = bintree1.root()->traverseLevelRetLast(fun_);
	cout << endl;

	//二叉树剥离子树测试
	bintree1.insertAsLTree(last_of_bintree1, bintree2.secede(bintree2.root()->Lchild()));
	cout << "左插入bintree2.root()->Lchild() 后bintree1 的内容为： " << endl;
	last_of_bintree1 = bintree1.root()->traverseLevelRetLast(fun_);
	cout << endl;

	//二叉树递归版遍历测试
	cout << "二叉树递归版遍历测试 : 先序遍历：" << endl;
	bintree1.traversePre(fun_);
	cout << endl;
	cout << "二叉树递归版遍历测试 : 中序遍历：" << endl;
	bintree1.traverseMid(fun_);
	cout << endl;
	cout << "二叉树递归版遍历测试 : 后序遍历：" << endl;
	bintree1.traverseBack(fun_);
	cout << endl;

	cout << "二叉树迭代版遍历测试：先序遍历：" << endl;
	bintree1.traversePre(fun_, mystd::TraverseType::ITERATION);
	cout << endl;

	cout << "二叉树迭代版遍历测试： 中序遍历: " << endl;
	bintree1.traverseMid(fun_, mystd::TraverseType::ITERATION);
	cout << endl;

	//等效的一种无栈的中序遍历
	cout << "二叉树 后继查找测试：顺序输出:" << endl;
	auto p_f = bintree1.fir_of_mid();
	while (true)
	{//todo
		cout << p_f->data() << " ";
		if (!p_f->suc())
			break;
		p_f = p_f->suc();
	}
	cout << endl;
	cout << "二叉树前驱查找测试：逆序输出:" << endl;
	while (p_f)
	{
		cout << p_f->data() << " ";
		p_f = p_f->pre();
	}
	cout << endl;

	cout << "二叉树迭代版遍历测试： 后序遍历: " << endl;
	bintree1.traverseBack(fun_, mystd::TraverseType::ITERATION);
	cout << endl;

}
void myListTest()
{
	mystd::List<int> lst{ 1,2,3,4,4,5,6,7,7,8,8,8,8,9 };
	showList(lst);
	cout << "pushback测试: 输入一个数字" << endl;
	int push_test;
	while (cin >> push_test)
	{
		lst.pushback(push_test);
		lst.pushfront(push_test);
		showList(lst);
	}

	cout << "pop 测试： 输入pop的次数" << endl;
	int pop_test(5);
	cin >> pop_test;
	while (pop_test--)
	{
		lst.popback();
		lst.popfront();
		showList(lst);
	}

	cout << "赋值运算符测试：" << endl;

	mystd::List<int> lst_b{ 9,8,7,6,5,4,3,2,1 };

	lst = lst_b;

	showList(lst);

	//双向链表遍历函数测试：
	cout << "双向链表遍历函数测试： " << endl;
	lst.tranverse(print_f);

	cout << "链表去重测试" << endl;
	lst.deduplicate();
	showList(lst);

	int32_t a_search;
	cout << "search 函数测试 ,输入一个数：" << endl;
	while (cin >> a_search)
	{
		cout << "search 函数测试 " << endl
			<< "查找到的数据为" <<
			lst.search(a_search, lst.begin(), lst.end())->data_ <<
			endl;
	}

	cout << "插入函数测试测试，输入一个数，找到不大于这个数的最后一个数，并在之后插入 " << endl;
	int32_t a_insert;
	while (cin >> a_insert)
	{
		auto temp = lst.insert(a_insert, lst.search(a_insert, lst.begin(), lst.end()));
		cout << "插入函数测试, 插入的数据为: " <<
			temp->data_ << endl;

		showList(lst);

		cout << " 删除该数据，返回删除节点之后的数据为：" << lst.erase(temp)->data_ <<
			endl;
		showList(lst);

	}

	size_t a;
	while (cin >> a)
	{
		while (a--)
		{
			cout << "随机打乱测试" << endl;
			lst.unsort();
			showList(lst);
			cout << "归并排序测试" << endl;
			lst.mergeSort(lst.begin(), lst.end());
			showList(lst);
		}
	}

}
void myVectorTest()
{
	mystd::Vector<int> v_test{ 1,2,3,4,4,5,5,5,6 };
	showVector(v_test);
	cout << "输入一个插入的数 和 位置" << endl;
	int insert, insert_n;
	cin >> insert >> insert_n;
	v_test.insert(insert_n, insert);
	showVector(v_test);

	cout << "输入一个的删除的位置" << endl;
	int delete_n;
	cin >> delete_n;
	v_test.erase(delete_n);
	showVector(v_test);

	cout << "重新创建一个数组，并让之前的数组等于这个数组" << endl;
	int input_i;
	mystd::Vector<int> V_test_b;
	while (cin >> input_i)
	{
		V_test_b.pushback(input_i);
	}
	cout << "输入数组为：" << endl;
	showVector(V_test_b);
	cout << "赋值给之前的输入" << endl;
	v_test = V_test_b;
	showVector(v_test);

	cout << "以当前数组作为新数组的构造函数输入" << endl;
	mystd::Vector<int> v_test_c(v_test);
	showVector(v_test_c);


	cout << "向量的首 末 分别为: " << endl;
	cout << v_test.front() << " " << v_test.back() << endl;

	const mystd::Vector<int> v_test_d = v_test;
	cout << "向量的首 末 分别为: " << endl;
	cout << v_test_d.front() << " " << v_test_d.back() << endl;

	for (int i = 0; i != 100; i++)
	{
		cout << "向量重排算法测试：" << endl;
		v_test.unsort();
		showVector(v_test);
	}

	cout << "无序向量查找测试: " << endl;
	cout << v_test.find(5) << endl;

	cout << "重复元素剔除测试:" << endl;
	cout << "剔除的元素个数为: " <<
		v_test.deduplicate() << endl;
	showVector(v_test);



	//lambda 测试
	cout << "遍历的function用法测试：" << endl;
	auto f = [](int a) {cout << a << " "; };
	v_test.tranverse(f);
	cout << endl;

	//函数指针测试
	v_test.tranverse(print_f);
	cout << endl;

	//函数对象测试
	PrintInt myprint_int;
	myprint_int.n = 0;
	v_test.tranverse(myprint_int);
	cout << endl << "the print number is :"
		<< myprint_int.n << endl;



	//向量有序性测试
	cout << "向量有序性为(1:有序 0：无序): " << v_test.isSorted() << endl;

	//冒泡排序测试：
	cout << "冒泡排序测试::" << endl << "随机打乱数组： " << endl;;
	v_test.unsort();
	showVector(v_test);
	v_test.bubblesort(0, v_test.size() - 1);
	showVector(v_test);
	cout << "归并排序测试::" << endl << "随机打乱数组： " << endl;;
	v_test.unsort();
	showVector(v_test);
	v_test.mergesort(0, v_test.size() - 1);
	showVector(v_test);


	//二分查找测试:
	cout << "二分查找测试： (输入一个查找的数，返回-1为查找失败)" << endl;
	size_t binsearch_n;
	while (cin >> binsearch_n)
	{
		cout << "查找结果为：" << v_test.binSearch(binsearch_n)
			<< endl;
	}
}
template<typename T>
void showVector(const std::vector<T> & V)
{
	for (const auto &elem : V)
	{
		std::cout << elem << " ";
	}
}
template<typename T>
void showVector(const mystd::Vector<T>& V)
{
	cout << "Vector 内容为：" << endl;
	for (int i = 0; i != V.size(); i++)
	{
		cout << V[i] << " ";
	}
	cout << endl;
}
//the 2^n funtion test: the linear complexity and logn complexity

void expFuntionTest()
{
	int count = 10000;
	unsigned long long  re1;
	unsigned long long  re2;
	clock_t start_time1 = clock();
	while (count--)
		re1 = power2_1(1000);
	clock_t end_time1 = clock();

	count = 10000;
	clock_t start_time2 = clock();
	while (count--)
		re2 = power2_2(1000);
	clock_t end_time2 = clock();
	//clock_t runtime = end_time - start_time;
	cout << re1 << endl << " power2_1 runtime is " <<
		static_cast<double>(end_time1 - start_time1) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

	cout << re2 << endl << " power2_2 runtime is " <<
		static_cast<double>(end_time2 - start_time2) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

}

//测试的n可以设的特别大，虽然得到的fibonacci数字无法存储在long long 中，结果是错误的。
//但是可以用来测试算法的时间。
void fibnacciTest(size_t n)
 {

	long long int re1;
	long long int re2;
	int count = 10;

	//线性迭代算法
	clock_t start_time1 = clock();
	while (count--)
		re1 = fib_2(n);
	clock_t end_time1 = clock();
	cout << re1 << endl << " fib_2 runtime is " <<
		static_cast<double>(end_time1 - start_time1) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

	//通过矩阵幂来计算，logn复杂度算法。
	count = 10;
	clock_t start_time2 = clock();
	while (count--)
		re2 = fib_5(n);
	clock_t end_time2 = clock();

	cout << re2 << endl << " fib_5 runtime is " <<
		static_cast<double>(end_time2 - start_time2) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

}

//hanoi塔问题的复杂度为指数级别，因而随着n的增大求解时间会爆炸式增长。
/***** n = 20 的运行结果：**************************

before:
A: 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
B:
C:
after:
A:
B:
C: 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
hanoi runtime is 6949ms

****************************************************/
void hanoiTest(size_t n)
{
	std::vector<int> A;
	for (int i = n; i != 0; i--)
	{
		A.push_back(i);
	}
	std::vector<int> B;
	std::vector<int> C;
	cout << "before:" << endl << "A: ";
	showVector(A);
	cout << endl << "B: ";
	showVector(B);
	cout << endl << "C: ";
	showVector(C);
	cout << endl;

	clock_t start_time2 = clock();
	hanoi(A, B, C, A.size());
	clock_t end_time2 = clock();

	cout << "after: " << endl << "A: ";
	showVector(A);
	cout << endl << "B: ";
	showVector(B);
	cout << endl << "C: ";
	showVector(C);
	cout << endl;

	cout  << " hanoi runtime is " <<
		static_cast<double>(end_time2 - start_time2) / CLOCKS_PER_SEC * 1000 << "ms" << endl;

}
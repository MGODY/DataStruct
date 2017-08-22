#pragma once
#ifndef RECURSIVE_PRACTICE
#define RECURSIVE_PRACTICE
#include<vector>
#include<map>
#include"matrix.h"

size_t sumInt(const std::vector<int> &a);
long long sumInt(const std::vector<int> a, size_t begin, size_t end);
unsigned long long power2_1(size_t a);
unsigned long long power2_2(size_t a);

//fibonacci 指数递归。
long long fib_1(size_t n);

//fibonacci 线性迭代。
long long fib_2(size_t n);

//fibonacci 线性递归
long long fib_3(size_t n);

//fibonacci 线性递归
long long fib_4(size_t n);

//fibonacci logn递归 （通过矩阵运算,在n特别大的时候，算法时间是远小于线性递归的）
long long fib_5(size_t n);

//hanoi塔问题的递归解法；

template<typename T>
void hanoi(std::vector<T> &A, std::vector<T> &B, std::vector<T> &C, size_t n)
{
	if (n == 1)
	{
		C.push_back(A.back());
		A.pop_back();
	}
	else
	{
		hanoi(A, C, B, n - 1);
		C.push_back(A.back());
		A.pop_back();
		hanoi(B, A, C, n - 1);
	}

}
#endif // 

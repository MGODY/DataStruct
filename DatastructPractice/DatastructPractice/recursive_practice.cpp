#include "recursive_practic.h"
size_t sumInt(const std::vector<int> &a, int num);
long long fib_3_1(size_t n, long long  &pre);

template<typename T>
Matrix<T> Mpower(const Matrix<T> &M, size_t n);

template<typename T>
inline  Matrix<T> sqrtM(const Matrix<T> &M)
{
	return M*M;
}
template<typename T>
Matrix<T> unit_Matrix(const Matrix<T> &M);
//to result the sum of a vector of int.
size_t sumInt(const std::vector<int> &a)
{
	if (a.size() == 0)
		return 0;
	else
		return sumInt(a, a.size());
}
size_t sumInt(const std::vector<int> &a ,int num)
{	
	if (num == 0)
		return 0;
	else
		return   sumInt(a, num - 1)+ a[num - 1] ;
}

//practice 1: to result  3^n with recursive funtion
/****2017.7.16 ******/

//Linear complexity version
unsigned long long power2_1(size_t a)
{
	if (a == 0)
		return 1;
	else
		return power2_1(a - 1) << 1;
}

//log complexity version

unsigned long long power2_2(size_t a)
{
	auto sqr = [](size_t n) {return n*n; };
	if (a == 0)
	{ 
		return 1;
	}
	else if (a & 1)
	{
		return sqr(power2_2(a >> 1)) << 1;
	}
	else
	{
		return sqr(power2_2(a >> 1));
	}
}

//two divide recursive funtion. 
//In every recursive cut the vector into two parts, so as to decrease the use of space.
//����ʹ�ö��ֵݹ��ǰ���� ������Ա��ֳ�����������ɵĲ��֣����ֽ�����֮��û�������
//��Ȼ���ǵ��������ĸ��Ӷ�����������fibonacci���⡣��
long long sumInt(const std::vector<int> a, size_t begin, size_t end)
{
	if (begin == end)
		return a[begin];
	else
	{
		int mid = (begin + end)>>1;
		return sumInt(a, begin, mid ) + sumInt(a, mid + 1, end);
	}
}

//�Ʋ����������������ַ���,���Ӷȸ��в�ͬ��
//fibonacci �Ļ�����������Ϊ 
// fib(n) =| fib(n-1)+fib(n-1) n>1
//         | n                 n<=1 


//ָ�������Ӷ�,����n�����󣬼���ʱ�䱬ըʽ������
//����fib(n) ������fib(n-1) ��fib��n-2���Ľ�������Ǻ����ķ���ֵ��ֱ�ӵ���  fib_1(n - 1) + fib_1(n - 2)
//��͵����ˣ�������ÿ���ֵ�з���չ���������м����������㡣ÿһ����fib��������𼶵���
//�ʵȱ����У�������帴�Ӷ�Ϊָ������

//���д�0�ʼ��
long long fib_1(size_t n)
{
	if (n < 2)
		return n;
	else
		return fib_1(n - 1) + fib_1(n - 2);
}

long long fib_2(size_t n)
{
	if (n < 2)
		return n;
	else
	{
		long long sum = 0;
		long long temp1 = 1;
		long long temp2 = 0;
		while (n--)
		{
			sum = temp1 + temp2;
			temp1 = temp2;
			temp2 = sum;
		}
		return sum;

	}
}
		
long long fib_3(size_t n  )
{
	if (n <= 1)
		return n;
	else

	{
		long long  pre;
		return fib_3_1(n, pre);
	}

}
long long fib_3_1(size_t n, long long  &pre)
{
	/*
		�˴���Ϊ�и���ں���fib_3(size_t n  )�����n==0����������Եݹ������ʹ��n==1;
		����˴��͵�ʹ�õݹ��n==0��
		����дΪ��
		if(n == 0 )
		{
			pre = 1;
			return 0;
		}
	*/
	if (n == 1)
	{
		pre = 0;
		return 1;
	}
	else
	{
		long long  pre_t;
		pre = fib_3_1(n - 1, pre_t);
		return pre + pre_t;
	}
}


// ���Ӷ�?��fibonacci����
// ���л����д����ļ������ࡣ �������帴�Ӷ�����ڵ�����ʽ��Ҫ�ߡ� ����ʹ�ö�̬�滮���Ž����
long long fib_4(size_t n)
{
	auto sqr = [](size_t a) {return a*a; };
	if (n <= 1)
		return n;
	else 
	{
		if (n & 1)
		{
			return  sqr(fib_4(n >> 1)) + sqr(fib_4((n >> 1) + 1) );
		}
		else
		{
			auto temp = fib_4(n >> 1);
			return ((fib_4((n >> 1) - 1)*temp)<<1) + temp*temp;
		}
	}

}

long long fib_5(size_t n)
{
	Matrix< long long > base(2,2);
	base.data[0][0] = 1;
	base.data[0][1] = 1;
	base.data[1][0] = 1;
	base.data[1][1] = 0;

	return Mpower(base,n).data[0][1];
}

template<typename T>
Matrix<T> Mpower(const Matrix<T> &M,size_t n)
{
	if (n == 0)
		return unit_Matrix(M);
	else
	{
		if (n & 1)
		{
			return sqrtM(Mpower(M, n >> 1)) * M;
		}
		else
		{
			return sqrtM(Mpower(M, n >> 1));
		}
	}
}


template<typename T>
Matrix<T> unit_Matrix(const Matrix<T> &M)
{
	Matrix<T> M_temp(M.data.size(),M.data.size());
	for (int i = 0; i != M.data.size(); i++)
	{
		M_temp.data[i][i] = 1;
	}
	return M_temp;
}





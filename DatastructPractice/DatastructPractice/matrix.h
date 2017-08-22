#ifndef MATRIXH
#define MATRIXH
#include<vector>
#include<iostream>
template <typename T>
class Matrix;

//对于模板类来说，重载运算符的友元函数要在类内部定义。
template <typename T>
class Matrix
{
public:
	std::vector<std::vector<T>> data;

	Matrix(size_t line  = 2,size_t row =2) :data(line,std::vector<T>(row))
	{
	}
	friend Matrix operator+(const Matrix &M1, const Matrix &M2)
	{
		if (M1.data.size() != M2.data.size() || M1.data[0].size() != M2.data[0].size())
			return Matrix<T>();

		Matrix<T> re(M1.data.size(), M1.data[0].size());
		for (int l = 0; l != M1.data.size(); l++)
		{
			for (int r = 0; r != M1.data[0].size(); r++)
			{
				re.data[l][r] = M1.data[l][r] + M2.data[l][r];
			}
		}
		return re;
	}

	friend Matrix operator-(const Matrix &M1, const Matrix &M2)
	{
		if (M1.data.size() != M2.data.size() || M1.data[0].size() != M2.data[0].size())
			return Matrix<T>();

		Matrix<T> re(M1.data.size(), M1.data[0].size());
		for (int l = 0; l != M1.data.size(); l++)
		{
			for (int r = 0; r != M1.data[0].size(); r++)
			{
				re.data[l][r] = M1.data[l][r] - M2.data[l][r];
			}
		}
		return re;
	}

	friend Matrix operator*(const Matrix &M1,const Matrix &M2)
	{
		if (M1.data[0].size() != M2.data.size())
			return Matrix<T>();
		Matrix<T> re(M1.data.size(), M2.data[0].size());
		for (int l = 0; l != re.data.size(); l++)
		{
			for (int r = 0; r != re.data[0].size(); r++)
			{
				for (int a = 0; a != re.data[0].size(); a++)
				{
					re.data[l][r] += M1.data[l][a] * M2.data[a][r];
				}
			}
		}
		return re;
	}

	void print()
	{
		for (auto &line : data)
		{ 
			for (auto &elem : line)
			{
				std::cout << elem << " ";
			}
			std::cout << endl;
		}
	}

};






#endif

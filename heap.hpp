#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <assert.h>
//小堆
template<class T>
struct Less
{
	bool operator() (const T& l, const T& r)
	{
		return l < r;
	}
};

template<class T>
struct Greater
{
	bool operator() (const T& l, const T& r)
	{
		return l > r;
	}
};

template<class T,class Compare=Less<T>>
class Heap
{
public:
	Heap() {}

	Heap(const T*a ,size_t size)
	{
		for (size_t i = 0; i < size; ++i)
		{
			_arrays.push_back(a[i]);
		}

		//建堆
		for (int i = (_arrays.size() - 2) / 2; i >= 0; --i)
		{
			AdjustDown(i);
		}
	}

		void Push(const T& x)
		{
			_arrays.push_back(x);
			AdjustUp(_arrays.size() - 1);
		}

		void Pop()
		{
			assert(_arrays.size() > 0);
			swap(_arrays[0], _arrays[_arrays.size() - 1]);
			_arrays.pop_back();

			AdjustDown(0);
		}

		T& Top()
		{
			assert(_arrays.size() > 0);
			return _arrays[0];
		}

		bool Empty()
		{
			return _arrays.empty();
		}

		bool Size()
		{
			return _arrays.Size();
		}

		void AdjustDown(int root)
		{
			int child = root * 2 + 1;

			Compare com;
			while (child < _arrays.size())
			{
				// 比较出左右孩子中小(大)的那个
				if (child + 1 < _arrays.size() &&
					com(_arrays[child + 1], _arrays[child]))
				{
					++child;
				}

				if (com(_arrays[child], _arrays[root]))
				{
					std::swap(_arrays[child], _arrays[root]);
					root = child;
					child = 2 * root + 1;
				}
				else
				{
					break;
				}
			}
		}

		void AdjustUp(int child)
		{
			int parent = (child - 1) / 2;
			while (child > 0)
			{
				if (Compare()(_arrays[child], _arrays[parent]))
				{
					std::swap(_arrays[child], _arrays[parent] );
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}

		void Print()
		{
			for (size_t i = 0; i < _arrays.size(); ++i)
				cout << _arrays[i] << " ";
			cout << endl;
		}

private:
	vector<T> _arrays;
};


template<class T, class Compare = Less<T>>
class PriorityQueue
{
public:
	void Push(const T& x)
	{
		_hp.Push(x);
	}
	void Pop()
	{
		_hp.Pop();
	}
	T& Top()
	{
		return _hp.Top();
	}
public:
	Heap<T, Compare> _hp;
};

/**************************************************************************/
//堆排
void AdjustDown(int* a, size_t size, int root)
{
	int child = root * 2 + 1;

	while (child < size)
	{
		if (child + 1 < size && a[child + 1] > a[child])
			++child;

		if (a[child]>a[root])
		{
			swap(a[child], a[root]);
			root = child;
			child = root * 2 + 1;
		}
		else
			break;
	}
	for (int i = 0; i < 10; ++i)
		cout << a[i] << " ";
	cout << endl;
}
/*
	1.建立最大堆
	2.交换 0位置，end位置的元素，保证把最大元素放在数组的最后面，--end
	3.调整堆
	4.重复 2，3动作
*/
void HeapSort(int* a, size_t size)
{
	if (a == NULL || size <= 0) return;
	//建堆
	for (int i = (size - 2) / 2; i >= 0; --i)
		AdjustDown(a,size,i);

	cout << "建堆完成" << endl;
	//排序
	for (size_t i = 0; i < size; ++i)
	{
		swap(a[0],a[size-i-1]);
		AdjustDown(a, size - i - 1, 0);
	}
}


void TestHeapSort()
{
	int a[10] = { 5, 9, 2, 3, 0, 1, 7, 8, 4, 6 };
	for (int i = 0; i < 10; ++i)
		cout << a[i] << " ";
	cout << endl << endl;

	HeapSort(a, 10);

	cout << endl;
	for (int i = 0; i < 10; ++i)
		cout << a[i] << " ";
	cout << endl;
}

void TestPriorityQueue()
{
	PriorityQueue<int,Greater<int> > _pq;

	_pq.Push(10);
	cout << _pq.Top() << endl;

	_pq.Push(7);
	cout << _pq.Top() << endl;

	_pq.Push(8);
	cout << _pq.Top() << endl;

	_pq.Push(5);
	cout << _pq.Top() << endl;

	_pq.Push(3);
	cout << _pq.Top() << endl;

	_pq.Push(1);
	cout << _pq.Top() << endl;

	_pq.Push(2);
	cout << _pq.Top() << endl;
}
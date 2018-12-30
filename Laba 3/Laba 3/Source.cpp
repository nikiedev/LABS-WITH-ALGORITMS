#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

using namespace std;

int d;


int Parent(int i)//батько і-го вузла
{
	return (i - 1) / d;
}

int Son(int parent, int k)//к-й син
{
	return parent * d + k;
}

void Max_Heapify(vector<int> &A, int i)//підтримка властивості незростання піраміди
{
	int largest = i;
	for (int j = 1; j <= d; ++j)
	{
		int child = Son(i, j);
		if (child < A.size() && A[child] > A[largest])
		{
			largest = child;
		}
	}
	if (largest != i)
	{
		swap(A[i], A[largest]);
		Max_Heapify(A, largest);
	}
}

int Heap_Extract_Max(vector<int> &A)//повертає максимум
{
	if (A.size() < 1)
	{
		cout << "Error" << endl;
		return -1;
	}
	int Max = A[0];
	A[0] = A[A.size() - 1];
	A.pop_back();
	Max_Heapify(A, 0);
	return Max;
}

void Heap_Increase_Key(vector<int> &A, int i, int key)//збільшує ключ і-го вузла(ставить його рівним key)
{
	if (key < A[i])
	{
		cout << "Key is less then current" << endl;
		return;
	}
	A[i] = key;
	while (i > 0 && A[Parent(i)] < A[i])
	{
		swap(A[i], A[Parent(i)]);
		i = Parent(i);
	}
}

void Max_Heap_Insert(vector<int> &A, int key)//вставляє елемент key у піраміду
{
	A.push_back(-1000);
	Heap_Increase_Key(A, A.size() - 1, key);

}

int main()
{
	d = 3;
	vector<int> A = { 36, 80, 41, 72, 28,10, 15, 40, 37, 11, 10, 18, 63, 13 };
	Max_Heapify(A, 0);
	for (int i = 0; i <A.size(); ++i)
	{
		cout << A[i] << " ";
	}
	cout << endl;
	Heap_Increase_Key(A, 6, 42);
	for (int i = 0; i <A.size(); ++i)
	{
		cout << A[i] << " ";
	}
	cout << endl;
	Max_Heap_Insert(A, 31);
	for (int i = 0; i <A.size(); ++i)
	{
		cout << A[i] << " ";
	}
	cin.get();
	return 0;
}

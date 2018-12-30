
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

//��� ������ O(n), �������� ������
void sort1(vector<int> &A)
{
	vector<int> B(A.size());
	int x = -1; //�������� ������� ���� � �����
	for (int i = 0; i < A.size(); ++i)
	{
		if (A[i] == 0) x++;
	}
	int y = A.size() - 1;
	for (int i = A.size() - 1; i >= 0; --i)
	{
		if (A[i] == 0)
		{
			B[x] = A[i];
			x--;
		}
		else
		{
			B[y] = A[i];
			y--;
		}
	}
	A = B;
}

//��� ������ O(n), ���������� ����������� �� ����
void sort2(vector<int> &A)
{
	int c = 0;
	for (int i = 0; i < A.size(); ++i)
	{
		if (A[i] == 0)
		{
			swap(A[i], A[c]);
			c++;
		}
	}
}

//�������� ������, ���������� �� ����
void sort3(vector<int> &A)
{
	int i = -1; //����� ���������� ���� � ��� ����������� �����������
	for (int j = 0; j < A.size(); ++j)
	{
		if (A[j] == 0)
		{
			for (int k = j; (k - i - 1) > 0; k--)
			{
				swap(A[k], A[k - 1]);
			}
			i++;
		}
	}
}

void show(vector<int> A)
{
	for (int i = 0; i < A.size(); ++i)
	{
		cout << A[i] << " ";
	}
	cout << endl;
}

int main()
{
	vector<int> A = { 1,0,1,0,1,0,1 };
	sort1(A);
	show(A);
	cin.get();
	return 0;
}

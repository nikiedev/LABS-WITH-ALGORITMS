#include <iostream>
#include <fstream>

using namespace std;

const int MAX = 1000; //максимальний розмір матриці
int buffer[MAX];

void Merge(int *arr, int start11, int end11, int start22, int end22);

void MergeSort(int *arr, int first, int last)
{
	if (first < last)
	{
		int mid = (first + last) / 2;
		MergeSort(arr, first, mid); //сортування лівої частини
		MergeSort(arr, (first + last) / 2 + 1, last); //сортування правої частини
		Merge(arr, first, (first + last) / 2, (first + last) / 2 + 1, last); //злиття двох частин
	}
}

void Merge(int *arr, int start11, int end11, int start22, int end22)
{
	int start1 = start11, start2 = start22, end1 = end11, end2 = end22;

	int count = 0;
	while ((start1 <= end1) && (start2 <= end2))
	{
		if (arr[start1] < arr[start2])
		{
			buffer[count] = arr[start1];
			start1++;
		}
		else
		{
			buffer[count] = arr[start2];
			start2++;
		}
		count++;
	}

	if (start1 <= end1)
	{
		for (int i = start1; i <= end1; i++)
		{
			buffer[count] = arr[i];
			count++;
		}
	}
	else
	{
		for (int i = start2; i <= end2; i++)
		{
			buffer[count] = arr[i];
			count++;
		}
	}


	count = 0;
	for (int i = start11; i <= end22; i++)
	{
		arr[i] = buffer[count];
		count++;
	}
}


int main()
{
	ifstream array1("c:\\Users\\Виталий\\source\\repos\\лабы по алгоритмам\\massiv.txt");
	ofstream array2("c:\\Users\\Виталий\\source\\repos\\лабы по алгоритмам\\massiv1.txt");


	int mas[10];

	for (int i = 0; i < 10; i++)
	{
		array1 >> mas[i];
	}


	MergeSort(mas, 0, 9);


	for (int i = 0; i < 10; i++)
	{
		array2 << mas[i] << " ";
	}

	system("pause");

	return 0;
}
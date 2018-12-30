#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string.h>

using namespace std;


bool endOfFile(FILE *f)
{
	fpos_t curPos, endPos;
	fgetpos(f, &curPos);
	fseek(f, 0, SEEK_END);
	fgetpos(f, &endPos);
	fsetpos(f, &curPos);
	if (curPos == endPos) return true;
	return false;
}

void readFromFile(const char fname[], vector<int> &A, vector<int> &B)//зчитуємо послідовності  з файла
{
	FILE *f = fopen(fname, "rt");
	char c, str[4];
	int i = 0;
	bool a = true; //считуємо дані у вектор А
	while (!endOfFile(f))
	{
		fread(&c, sizeof(char), 1, f);
		if (isdigit(c))
		{
			str[i] = c;
			i++;
		}
		else
		{
			str[i] = '\0';
			int n = atoi(str);
			i = 0;
			if (a)
			{
				A.push_back(n);
			}
			else
			{
				B.push_back(n);
			}
			if (c == '\n')
			{
				a = false;
			}
		}
	}

	fclose(f);
}

void findPair(vector<int> &A, vector<int> &B, vector<int> &C) //підбираємо пари
{
	for (int i = 0; i < A.size(); ++i)
	{
		for (int j = 0; j < B.size(); ++j)
		{
			if (B[j] != 0 && A[i] == B[j])
			{
				C.push_back(B[j]);
				A[i] = 0;
				B[j] = 0;
				break;
			}
		}
	}
}

void Tail(vector<int> &A, vector<int> &Arest) //визначаємо тих хто залишився без пари
{
	for (int i = 0; i < A.size(); ++i)
	{
		if (A[i] != 0)
		{
			Arest.push_back(A[i]);
			A[i] = 0;
		}
	}
}

void show(vector<int> A)//вивід інформації на екран
{
	for (int i = 0; i < A.size(); ++i)
	{
		cout << A[i] << " ";
	}
	cout << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	vector <int> A; //гайки
	vector <int> B; //болти
	vector <int> C; //пари гайка-болт
	vector <int> Arest; //гайки які залишилися без пари
	vector <int> Brest; //болти які залишилися без пари
						//readFromFile("Input1.txt", A, B);
						//readFromFile("Input2.txt", A, B);
	readFromFile("Input2.txt", A, B);
	findPair(A, B, C);
	Tail(A, Arest);
	Tail(B, Brest);
	cout << "Пары: ";
	show(C);
	cout << "Гайки без пары: ";
	show(Arest);
	cout << "Болты без пары: ";
	show(Brest);
	cin.get();
	return 0;
}

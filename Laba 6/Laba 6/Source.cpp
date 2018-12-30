#include <iostream>
#include <fstream>

using namespace std;

const int length = 4;

bool is_good(int i, char *ln1, char *ln2)
{
	for (int j = 0; j<length; j++)
	{
		if (ln2[j] != ln1[(i + j) % length]) return false;
	}
	return true;
}

bool is_cyclic(char *ln1, char *ln2)
{
	for (int i = 0; i<length; i++)
	{
		if (is_good(i, ln1, ln2)) return true;
	}
	return false;
}


int main()
{
	ifstream line1("C:\\Users\\Виталий\\source\\repos\\лабы по алгоритмам");
	char ln1[4];
	char ln2[4];
	for (int i = 0; i < 4; i++)
	{
		line1 >> ln1[i];
	}
	for (int i = 0; i < 4; i++)
	{
		line1 >> ln2[i];
	}


	//must be YES
	cout << "First case: ";
	if (is_cyclic(ln1, ln2))
	{
		cout << "YES";
	}
	else {
		cout << "NO";
	}

	//must be NO
	cout << endl;
	ifstream line2("C:\\Users\\Виталий\\source\\repos\\лабы по алгоритмам");
	char ln3[4];
	char ln4[4];
	for (int i = 0; i < 4; i++)
	{
		line2 >> ln3[i];
	}
	for (int i = 0; i < 4; i++)
	{
		line2 >> ln4[i];
	}

	cout << "Second case: ";
	if (is_cyclic(ln3, ln4))
	{
		cout << "YES";
	}
	else {
		cout << "NO";
	}
	system("pause");
	return 0;
}

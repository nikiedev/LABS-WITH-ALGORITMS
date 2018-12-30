#define _CRT_SECURE_NO_WARNINGS;

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <conio.h>
#define ALPHABET 256;

using namespace std;

int MAX = 10000;

int Rabina_Karpa(string t, string s)
{
	int  max;
	int min;
	const int p = 31;
	vector<long long> p_pow(max(s.length(), t.length()));
	p_pow[0] = 1;
	for (size_t i = 1; i<p_pow.size(); ++i)
		p_pow[i] = p_pow[i - 1] * p;

	// рахуємо хеші від всіх префіксів строки Т
	vector<long long> h(t.length());
	for (size_t i = 0; i<t.length(); ++i)
	{
		h[i] = (t[i] - 'a' + 1) * p_pow[i];
		if (i)  h[i] += h[i - 1];
	}

	// рахуємо хеш від строки S
	long long h_s = 0;
	for (size_t i = 0; i<s.length(); ++i)
		h_s += (s[i] - 'a' + 1) * p_pow[i];

	// перебираємо всі підстроки T довжини |S| і порівнюємо їх
	for (size_t i = 0; i + s.length() - 1 < t.length(); ++i)
	{
		long long cur_h = h[i + s.length() - 1];
		if (i)  cur_h -= h[i - 1];
		// приводим хеші до одної степені і порівнюємо
		if (cur_h == h_s * p_pow[i])
			//cout << i << ' ';
			return i;
	}
}

vector<int> naive(string p, string t)
{
	size_t m = p.size() - 1;
	size_t n = t.size();
	vector<int> result;

	for (size_t i = 0, j = 0; i < n; i++)
	{
		while (i < n && j != m && t[i] == p[j])
		{
			i++;
			j++;
		}
		if (j == m)
		{
			result.push_back(i - m);
			j = 0;
		}
	}
	return result;
}

bool compare(string::const_iterator a, const string::const_iterator b, int num) {
	for (auto i = a, j = b; i < a + num; i++, j++) {
		if (*i != *j) return false;
	}
	return true;
}

int Boyer_Moore(const string &t, const string &s) {
	//зсув хорошого суфікса
	vector<int> good_shift(s.size() + 1, s.size());
	//зсув поганого символа
	vector<int> bad_char(ALPHABET, s.size());

	//масив Z, кожен елемент якого Z[i] дорівеює довжині найбільш довгого префікса суфікса підстроки,
	//який починається з позиції i в строці S, який одночасно являється і префіксом всієї строки S
	vector<int> z(s.size(), 0);
	for (int j = 1, maxZidx = 0, maxZ = 0; j < s.size(); ++j) {
		if (j <= maxZ) z[j] = min(maxZ - j + 1, z[j - maxZidx]);
		while (j + z[j] < s.size() && t[s.size() - 1 - z[j]] == t[s.size() - 1 - (j + z[j])]) z[j]++;
		if (j + z[j] - 1 > maxZ) {
			maxZidx = j;
			maxZ = j + z[j] - 1;
		}
	}
	for (int j = s.size() - 1; j > 0; j--) good_shift[s.size() - z[j]] = j; //цикл №1
	for (int j = 1, r = 0; j <= s.size() - 1; j++) //цикл №2
		if (j + z[j] == s.size())
			for (; r <= j; r++)
				if (good_shift[r] == s.size()) good_shift[r] = j;

	for (int j = 0; j < s.size() - 1; j++) bad_char[(int)s[j]] = s.size() - j - 1;

	int i = 0;
	while (i <= s.size() - t.size()) {
		int j = 0;
		for (j = s.size() - 1; j >= 0 && s[j] == t[i + j]; --j);
		if (j < 0) {
			return i;
		}
		else i += max((good_shift[j + 1]), (int)(bad_char[(int)t[i + j]] - s.size() + j + 1));
	}
	return -1;
}

int Horspool(const string &where, const string &what) {
	unsigned int skip_table[ALPHABET];
	int i;


	/**попередня обробка */
	//заповнюємо таблицю максимальним значенням стрибка
	for (i = 0; i < ALPHABET; i++)
		skip_table[i] = what.size();

	//потім вичисляємо для кожного символа шаблона стрибок
	for (i = 0; i < what.size() - 1; i++)
		skip_table[(int)what[i]] = what.size() - i - 1;

	/** пошук */
	i = 0;
	while (i <= where.size() - what.size()) {
		if (where[i + what.size() - 1] == what[what.size() - 1])
			if (compare(where.begin() + i, what.begin(), what.size() - 2) == true)
				return i;

		//якщо два символи відрізняються,
		//стрибаємо, користуючись значеннями таблиці переходу
		//в індекс символа текста
		i += skip_table[(int)where[i + what.size() - 1]];
	}
	return -1;
}

int KMP(const string &t, const string s) {
	vector<int> z;
	//рахуєм з-функцію
	z.resize(s.size());
	z[0] = 0;
	for (int i = 1; i<z.size(); ++i) {
		int pos = z[i - 1];
		while (pos > 0 && s[pos] != s[i])
			pos = z[pos - 1];
		z[i] = pos + (s[pos] == s[i] ? 1 : 0);
	}
	//порахували

	int pos = 0;
	for (int i = 0; i<t.size(); ++i) {
		while (pos > 0 && (pos >= s.size() || s[pos] != t[i]))
			pos = z[pos - 1];
		if (t[i] == s[pos]) pos++;
		if (pos == s.size())
			return (i - pos + 1);
	}
	return -1;
}

int main() {
	ifstream text("C:\\Users\\Виталий\\source\\repos\\лабы по алгоритмам\LABA 7\\");
	string n;
	getline(text, n);
	cout << n << endl;
	string s = "friends";


	auto time = chrono::high_resolution_clock::now();

	cout << "Rabina-Karpa Search" << endl;
	time = chrono::high_resolution_clock::now();
	cout << "first position: " << Rabina_Karpa(n, s) << endl;
	cout << "time: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - time).count() << " ns" << endl;
	cout << endl;

	cout << "Naive Search" << endl;
	time = chrono::high_resolution_clock::now();
	cout << "first position: " << naive(s, n)[0] << endl;
	cout << "time: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - time).count() << " ns" << endl;
	cout << endl;

	cout << "Horspool Search" << endl;
	time = chrono::high_resolution_clock::now();
	cout << "first position: " << Horspool(n, s) << endl;
	cout << "time: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - time).count() << " ns" << endl;
	cout << endl;

	cout << "Boyer-Moore Search" << endl;
	time = chrono::high_resolution_clock::now();
	cout << "first position: " << Boyer_Moore(n, s) << endl;
	cout << "time: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - time).count() << " ns" << endl;
	cout << endl;

	cout << "Knuth-Morris-Pratt Search" << endl;
	time = chrono::high_resolution_clock::now();
	cout << "first position: " << KMP(n, s) << endl;
	cout << "time: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - time).count() << " ns" << endl;
	cout << endl;

	return 0;
}
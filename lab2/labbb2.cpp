#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cmath>
using namespace std;


void NewMemoryForMatr(double**& a, int n, int m)
{

	a = new double* [n];
	for (int i = 0; i < n; i++)
		a[i] = new double[m];
}
void DelMatrMemory(double**& a, int n, int m)
{

	for (int i = 0; i < n; i++)
		delete[]a[i];
	delete[]a;
}
int GetNumber()
{
	float n;
	do {
		cout << "Размерность: ";
		cin >> n;
		if (n <= 0 || (n - (int)n))
			cout << "Ошибка!" << endl;
	} while (n <= 0 || (n - (int)n));

	return n;
}

void Out(double** a, int n, int m)
{
	cout << endl << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << setw(15) << a[i][j];
		cout << endl;
	}
}
bool GetFileMatr(double** a, int n, int m) {

	ifstream f;
	f.open("file.txt");
	if (f) {
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				f >> a[i][j];
			}
		}
	}
	f.close();
	return true;
}

void PrintVect(double* x, int n) {
	cout << endl;
	cout << "Вектор решений " << endl;
	for (int j = 0; j < n; j++)
		cout << setw(15) << x[j];
	cout << endl;
}
void reshuffle(double**& M, int n, int m, int k, double& Det)
{
	for (int i = k + 1; i < n; i++)
	{
		if (M[i][k] != 0)
		{
			double temp;
			for (int i1 = 0; i1 < m; i1++)
			{
				temp = M[k][i1];
				M[k][i1] = M[i][i1];
				M[i][i1] = temp;
			}
			Det *= -1;
			break;
		}
	}
}
bool minor(double**& M, int n, int m, double& Det)
{
	for (int i = 0; i < n; i++)
	{
		if (M[i][i] == 0) reshuffle(M, n, m, i, Det);
		if (M[i][i] == 0) return false;
		for (int i1 = i + 1; i1 < n; i1++)
			for (int i2 = i + 1; i2 < m; i2++)
				M[i1][i2] = M[i][i] * M[i1][i2] - M[i][i2] * M[i1][i];
		for (int j = i + 1; j < n; j++)
		{
			M[j][i] = 0;
		}
	}
	return true;
}
bool Solve(double**& M, double* x, int n, int m, double& Det)
{
	double res = 0;
	if (!minor(M, n, m, Det)) return false;
	for (int i = n - 1; i >= 0; i--)
	{
		res = 0;
		for (int j = i + 1; j <= n - 1; j++)
			res = res - x[j] * M[i][j];
		res += M[i][n];
		x[i] = res / M[i][i];
	}
	return true;
}
double det(double** M, int n, int m)
{
	double det = 1;
	for (int i = 0; i < n; i++)
	{
		if (M[i][i] == 0) return 0;
		det *= M[i][i] / pow(M[i][i], n - 1 - i);
	}
	return det;
}
void copy(double**& M, int n, int m, double** M1)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			M1[i][j] = M[i][j];
}
bool inver(double** M, int n, int m, double& Det, double**& rev)
{
	double* x = new double[n];
	bool metka = true;
	for (int i = 0; i < n; i++)
	{
		double** buff;
		NewMemoryForMatr(buff, n, m);
		copy(M, n, m, buff);
		for (int j = 0; j < n; j++)
		{
			if (i == j) buff[j][m - 1] = 1;
			else buff[j][m - 1] = 0;
		}
		if (!Solve(buff, x, n, m, Det)) metka = false;
		for (int j = 0; j < n; j++)
			rev[j][i] = x[j];
		DelMatrMemory(buff, n, m);
	}
	delete[] x;
	x = NULL;
	return metka;
}
void test(double**& A, int n, int m)
{
	int s;
	cout << "Задание (1-5): "; cin >> s;
	switch (s)
	{
	case 1:
	{
		GetFileMatr(A, n, m);
		break;
	}
	case 2:
	{
		double a, b;
		srand(time(0));
		a = -10;
		b = 10;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
			{
				A[i][j] = a + ((double)rand() / RAND_MAX) * (b - a);
			}
		break;
	}
	case 3:
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (i == j) A[i][j] = 1;
				else A[i][j] = 0;
		break;
	}
	case 4:
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				A[i][j] = 0;
		break;
	}
	case 5:
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				A[i][j] = 1. / (i + j + 1);
		break;
	}
	}
}
double accuracy(double** M1, int n, int m, double* x)
{
	double epsilon = 0;
	double s;
	for (int i = 0; i < n; i++)
	{
		s = 0;
		for (int k = 0; k < m - 1; k++)
			s += M1[i][k] * x[k];
		if (fabs(M1[i][m - 1] - s) > epsilon) epsilon = fabs(M1[i][m - 1] - s);
	}
	return epsilon;
}
void correctness(double** a, double** b, int n1, int m1, int n2, int m2)
{
	cout << endl << "Обратная матрица" << endl;
	double** buff;
	NewMemoryForMatr(buff, n1, m2);
	double S;
	if (m1 != n2)
	{
		cout << "Ошибка!" << endl;
		DelMatrMemory(buff, n1, m2);
	}
	for (int i = 0; i < n1; i++)
		for (int j = 0; j < m2; j++)
		{
			S = 0;
			for (int k = 0; k < m1; k++)
				S += a[i][k] * b[k][j];
			buff[i][j] = S;
		}
	Out(buff, n1, m2);
	DelMatrMemory(buff, n1, m2);
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int n = GetNumber();
	int m = n + 1;
	double** a;
	double** copya;
	double** re;
	double* x = new double[n];
	double op = 1;
	NewMemoryForMatr(a, n, m);
	test(a, n, m);
	NewMemoryForMatr(copya, n, m);
	copy(a, n, m, copya);
	NewMemoryForMatr(re, n, m);
	Out(a, n, m);
	if (Solve(a, x, n, m, op))
	{
		PrintVect(x, n);
		cout << "Эпсилон: " << accuracy(copya, n, m, x) << endl;
	}
	else cout << "Нет решений!" << endl;
	cout << "Определитель :" << op * det(a, n, m) << endl;;
	if (inver(copya, n, m, op, re))
	{
		Out(re, n, m);
		correctness(copya, re, n, m - 1, n, n);
	}
	else cout << "Нет решений!" << endl;
	DelMatrMemory(a, n, m);
	DelMatrMemory(copya, n, m);
	DelMatrMemory(re, n, m);

	delete[]x;
	x = NULL;
	return 0;
}

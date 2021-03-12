#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cmath>

using namespace std;


void NewMatr(double**& array, int n, int m)
{
    array = new double* [n];
    for (int i = 0; i < n; i++)
        array[i] = new double[m];
}

void GetMatr(double** array, int n, int m)
{

    int y;
    cout << "Введите задание: ";
    cin >> y;
    switch (y) {
    case 1: {
        ifstream file;
        file.open("file.txt");
        if (file) {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    file >> array[i][j];
                }
            }
        }
        file.close();
        break;
    }
    case 2: {
        double a, b;
        srand(time(0));
        a = -10;
        b = 10;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                array[i][j] = a + ((double)rand() / RAND_MAX) * (b - a);
            }
        }
        break;
    }
    case 3: {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (i == j) array[i][j] = 1;
                else array[i][j] = 0;
            }
        }
        break;
    }
    case 4: {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                array[i][j] = 0;
            }
        }
        break;
    }
    case 5: {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                array[i][j] = 1. / (i + j + 1);
            }
        }
        break;
    }
    default: {
        cout << "Ошибка, задания не существует!\n";
        break;
    }
    }


}


void OutMatr(double** array, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << setw(15) << array[i][j];
        cout << endl;
    }
}

void PrintDet(double** array) {
    cout << endl << "Det: " << array[0][0] * array[1][1] * array[2][2] << endl;
}

void triangMatr(double** A, double** B, int n) {
    double koef;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            B[i][j] = A[i][j];
        }
    }
    for (int k = 0; k < n; k++) {
        for (int i = k + 1; i < n; i++) {
            koef = -1. * B[i][k] / B[k][k];
            for (int j = k; j < n + 1; j++) {
                B[i][j] = B[i][j] + B[k][j] * koef;
            }
        }
    }
    OutMatr(B, n, n + 1);
    PrintDet(B);
}
void PrintVect(double* x, int n) {
    cout << "x: " << endl;

    for (int j = 0; j < n; j++)
        cout << setw(5) << x[j];
}

void DelMatr(double**& array, int n, int m)
{
    for (int i = 0; i < n; i++)
        delete[] array[i];
    delete[] array;
    array = NULL;
}

void Solve(double** A, double* x, int n) {
    double res = 0;
    double** B;
    NewMatr(B, n, n + 1);
    cout << "triangle: " << endl;
    triangMatr(A, B, n);
    for (int i = n - 1; i >= 0; i--) {
        res = 0;
        for (int j = i + 1; j <= n - 1; j++) {
            res = res - x[j] * B[i][j];
        }
        res += B[i][n];
        x[i] = res / B[i][i];
    }

    DelMatr(B, n, n + 1);
}


void first(double** array, int n, int, double* x) {

}

void second(double** array, int n, int, double* x) {

}


void copy(double**& M, int n, int m, double** M1)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            M1[i][j] = M[i][j];
}

void inver(double** M, int n, int m, double**& inv)
{

    double* x = new double[n];
    bool t = true;
    for (int i = 0; i < n; i++)
    {
        double** buff;
        NewMatr(buff, n, m);
        copy(M, n, m, buff);
        for (int j = 0; j < n; j++)
        {
            if (i == j) buff[j][m - 1] = 1;
            else buff[j][m - 1] = 0;
        }
        Solve(buff, x, n);
        for (int j = 0; j < n; j++)
            inv[j][i] = x[j];
        DelMatr(buff, n, m);
    }
    delete[] x;
    x = NULL;

}   

double check(double** M1, int n, int m, double* x)
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


int main()
{
    setlocale(LC_ALL, "Russian");
    int n = 0;
    double** array;
    double** reobr;
    cout << "Введите размерность матрицы: "; cin >> n;
    double* x = new double[n];
    NewMatr(array, n, n + 1);
    NewMatr(reobr, n, n + 1);

    GetMatr(array, n, n + 1);
    inver(array, n, n + 1, reobr);
    cout << endl << "Обратная матрица" << endl;
    OutMatr(reobr, n, n + 1);

    cout << "A:" << endl;
    OutMatr(array, n, n + 1);
    Solve(array, x, n);
    PrintVect(x, n);
    cout << endl<< "eps = " << check(array, n, n + 1, x);
    DelMatr(array, n, n + 1);
    delete[]x;
    x = nullptr;
}


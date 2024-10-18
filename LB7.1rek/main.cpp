#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void Create(int** q, const int rowCount, const int colCount, const int Low, const int High, int i, int j);
void Print(int** q, const int rowCount, const int colCount, int i, int j);
void Sort(int** q, const int rowCount, const int colCount, int i0, int i1);
void Change(int** q, const int col1, const int col2, const int rowCount, int j);
void Calc(int** q, const int rowCount, const int colCount, int& S, int& k, int i, int j);

int main()
{
    srand((unsigned)time(NULL));
    int Low = -26;
    int High = 23;
    int rowCount = 8;
    int colCount = 6;
    int** q = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        q[i] = new int[colCount];
    Create(q, rowCount, colCount, Low, High, 0, 0);
    cout << "Original Matrix:" << endl;
    Print(q, rowCount, colCount, 0, 0);
    Sort(q, rowCount, colCount, 0, 0);
    cout << "Sorted Matrix:" << endl;
    Print(q, rowCount, colCount, 0, 0);
    int S = 0;
    int k = 0;
    Calc(q, rowCount, colCount, S, k, 0, 0);
    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    cout << "Modified Matrix:" << endl;
    Print(q, rowCount, colCount, 0, 0);
    for (int i = 0; i < rowCount; i++)
        delete[] q[i];
    delete[] q;
    return 0;
}

void Create(int** q, const int rowCount, const int colCount,
    const int Low, const int High, int i, int j)
{
    q[i][j] = Low + rand() % (High - Low + 1);
    if (j < colCount - 1)
        Create(q, rowCount, colCount, Low, High, i, j + 1);
    else if (i < rowCount - 1)
        Create(q, rowCount, colCount, Low, High, i + 1, 0);
}

void Print(int** q, const int rowCount, const int colCount, int i, int j)
{
    cout << setw(4) << q[i][j];
    if (j < colCount - 1)
        Print(q, rowCount, colCount, i, j + 1);
    else if (i < rowCount - 1)
    {
        cout << endl;
        Print(q, rowCount, colCount, i + 1, 0);
    }
    else
        cout << endl << endl;
}

void Sort(int** q, const int rowCount, const int colCount, int i0, int i1)
{
    if (i0 >= colCount - 1)
        return;

    if (i1 < colCount - i0 - 1)
    {
        if ((q[0][i1] > q[0][i1 + 1])
            ||
            (q[0][i1] == q[0][i1 + 1] &&
                q[1][i1] < q[1][i1 + 1])
            ||
            (q[0][i1] == q[0][i1 + 1] &&
                q[1][i1] == q[1][i1 + 1] &&
                q[2][i1] > q[2][i1 + 1]))
            Change(q, i1, i1 + 1, rowCount, 0);

        Sort(q, rowCount, colCount, i0, i1 + 1);
    }
    else
    {
        Sort(q, rowCount, colCount, i0 + 1, 0);
    }
}

void Change(int** q, const int col1, const int col2, const int rowCount, int j = 0)
{
    int tmp;
    if (j < rowCount)
    {
        tmp = q[j][col1];
        q[j][col1] = q[j][col2];
        q[j][col2] = tmp;
        Change(q, col1, col2, rowCount, j + 1);
    }
    return;
}

void Calc(int** q, const int rowCount, const int colCount, int& S, int& k, int i = 0, int j = 0)
{
    if (i >= rowCount)
        return;

    if (j < colCount)
    {
        if (q[i][j] % 2 == 0 && (q[i][j] > 0))
        {
            S += q[i][j];
            k++;
            q[i][j] = 0;
        }
        Calc(q, rowCount, colCount, S, k, i, j + 1);
    }
    else
    {
        Calc(q, rowCount, colCount, S, k, i + 1, 0);
    }
}

//перемножение двух матриц, алгоритм Винограда

#include <iostream>
#include <vector>
#include <iomanip>
#include <time.h>
using namespace std;

//алгоритм Винограда
void winograd(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C) {
    int n = A.size();
    int half = n / 2;
    
    //обнуляем результат
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
        }
    }
    
    //сумма A[i][2k] * A[i][2k+1]
    vector<int> rowSum(n, 0);
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < half; k++) {
            rowSum[i] += A[i][2*k] * A[i][2*k+1];
        }
    }
    
    //сумма B[2k][j] * B[2k+1][j]
    vector<int> colSum(n, 0);
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < half; k++) {
            colSum[j] += B[2*k][j] * B[2*k+1][j];
        }
    }
    
    //основной цикл
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = rowSum[i] + colSum[j];
            for (int k = 0; k < half; k++) {
                C[i][j] += (A[i][2*k] + B[2*k+1][j]) * (A[i][2*k+1] + B[2*k][j]);
            }
        }
    }
    
    //если размер нечётный
    if (n % 2 == 1) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                C[i][j] += A[i][n-1] * B[n-1][j];
            }
        }
    }
}

//вывод матрицы
void print(vector<vector<int>>& M) {
    int n = M.size();
    for (int i = 0; i < n; i++) {
        cout << "  ";
        for (int j = 0; j < n; j++) {
            cout << setw(4) << M[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//заполнение случайными числами
void fill(vector<vector<int>>& M) {
    int n = M.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            M[i][j] = rand() % 10;
        }
    }
}

int main() {
    setlocale(LC_ALL, "");
    srand(time(NULL));
    
    int n;
    cout << "Введите размер матрицы: ";
    cin >> n;
    
    vector<vector<int>> A(n, vector<int>(n));
    vector<vector<int>> B(n, vector<int>(n));
    vector<vector<int>> C(n, vector<int>(n));
    
    fill(A);
    fill(B);
    
    cout << "Матрица A" << endl;
    print(A);
    cout << "Матрица B" << endl;
    print(B);

    winograd(A, B, C);

    cout << "Итоговая матрица:" << endl;
    print(C);
}
//Оптимальная расстановка скобок при перемножении матриц
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

//вывод расстановки скобок
void printParens(int i, int j, vector<vector<int>>& s, char& name) {
    if (i == j) {
        cout << name++;
        return;
    }
    
    cout << "(";
    printParens(i, s[i][j], s, name);
    printParens(s[i][j] + 1, j, s, name);
    cout << ")";
}

//вычисления для расстановки скобок
void matrixChainOrder(vector<int>& p, int n) {
    //минимальное количество умножений 
    vector<vector<int>> m(n, vector<int>(n, 0));
    
    //позиция последнего умножения
    vector<vector<int>> s(n, vector<int>(n, 0));
    
    // l = длина цепочки (количество матриц)
    for (int l = 2; l < n; l++) {
        for (int i = 1; i < n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            
            for (int k = i; k < j; k++) {
                // стоимость = стоимость левой части + правой + умножение результатов
                int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
    
    // вывод результатов
    cout << "Оптимальная расстановка скобок\n";
    
    char name = 'A';
    printParens(1, n - 1, s, name);
    cout << "\n\n";
    
    cout << "Минимальное количество умножений: " << m[1][n - 1] << endl;
}

int main() {
    setlocale(LC_ALL, "");
    
    int n;
    cout << "Введите количество матриц: ";
    cin >> n;
    
    vector<int> p(n + 1);
    cout << "Введите размеры матриц (" << n + 1 << " чисел):\n";
    for (int i = 0; i <= n; i++) {
        cout << "p[" << i << "] = ";
        cin >> p[i];
    }
    
    cout << "\nРазмеры матриц:\n";
    for (int i = 1; i <= n; i++) {
        cout << "A" << i << "[" << p[i - 1] << " x " << p[i] << "]";
        if (i < n) cout << ", ";
    }
    cout << endl;
    
    matrixChainOrder(p, n + 1);
}
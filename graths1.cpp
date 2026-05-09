// gr1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> Gr;   // список смежности
int n;                     // количество вершин
vector<bool> used;         // массив посещённых вершин 

//добавление ребра
void addEdge(int u, int v) {
     for (int i = 0; i < Gr[u].size(); i++) {
     if (Gr[u][i] == v) {
         cout << "Ребро уже существует!\n";
         return;
     }
 }
    Gr[u].push_back(v);    // из u в v
    Gr[v].push_back(u);    // из v в u
}

void print() {
    for (int i = 0; i < n; i++) {
        cout << "Вершина " << i << " : ";

        //сортировка для вывода по порядку
    sort(Gr[i].begin(), Gr[i].end());

    for (int j = 0; j < Gr[i].size(); j++) {
        cout << Gr[i][j] << " ";
        }
    cout << endl;
    }
}


void countvershin(int target) {

    if (target < 0 || target >= n) {
        cout << "\nВершины не существует!\n";
        return;
    }

    int cnt = Gr[target].size();

    cout << "Смежные вершины: ";
    if (cnt == 0) {
        cout << "(нет смежных вершин)";
    }
    else {
        cout << cnt << " ";
    }
}

//массив с посещениями
void resetUsed() {
    fill(used.begin(), used.end(), false);
}

int main() {

    setlocale(LC_ALL, "");
    n = 8;
    Gr.resize(n);
    used.resize(n, false);

    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(0, 3);
    addEdge(0, 4);
    addEdge(1, 5);
    addEdge(2, 5);
    addEdge(3, 6);
    addEdge(4, 7);
    addEdge(5, 6);
    addEdge(6, 7);
    addEdge(5, 7);

     cout << "\nНачальный граф\n";
 print();
 cout << endl;

 int a, b;
 cout << "Введите вершину A: ";
 cin >> a;
 cout << "Введите вершину B: ";
 cin >> b;

 addEdge(a, b);

 cout << "\nГраф после вставки\n";
 print();

    resetUsed();
}
//Дан ориентированный граф. Подсчитать полустепень исхода каждой вершины.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> Gr;   // список смежности 
int n;                     // количество вершин

//добавление ребра для ориентированного графа
void addEdge(int u, int v) {
    for (int i = 0; i < Gr[u].size(); i++) {
        if (Gr[u][i] == v) {
            cout << "Ребро " << u << "→" << v << " уже существует!\n";
            return;
        }
    }
    Gr[u].push_back(v);

    sort(Gr[u].begin(), Gr[u].end());
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

//подсчёт полустепени исхода
void countvershisxod() {

    cout << "Полустепени исхода для всех вершин." << endl;
    for (int i = 0; i < n; i++) {
        int out = Gr[i].size();   // количество исходящих рёбер
        cout << "Вершина " << i << " : " << out;

        if (out == 0) {
            cout << " (нет исходящих рёбер)";
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "");

    n = 8;
    Gr.resize(n);

    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(0, 3);
    addEdge(1, 4);
    addEdge(2, 4);
    addEdge(3, 4);
    addEdge(5, 6);
    addEdge(6, 5);
    addEdge(5, 7);
    addEdge(7, 0); 

    cout << "Список смежности для рёбер" << endl;
    print();

    cout << endl;

    countvershisxod();
}

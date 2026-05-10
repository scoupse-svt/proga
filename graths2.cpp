//Дан ориентированный граф. Подсчитать полустепень исхода каждой вершины.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> Gr;   // список смежности 
vector<bool> used;        //массив посещённых вершин
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

//обход в ширину
void bfs(int start) {
   
    vector<int> q; //вектор для очереди
    int head = 0;

    used[start] = true;
    q.push_back(start);

    while (head < q.size()) {
        int x = q[head];
        head++;

        for (int i = 0; i < Gr[x].size(); i++) {
            int y = Gr[x][i];
            if (!used[y]) {
                used[y] = true;
                q.push_back(y);
            }
        }
    }
}

void resetUsed() {
    for (int i = 0; i < n; i++) {
        used[i] = false;
    }
}

//вывод матрицы смежности
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

//поиск вершин, из которых достижимы все остальные
void findall() {

    vector<int> versh;

    for (int i = 0; i < n; i++) {
        resetUsed();
        bfs(i);

        // Проверяем, все ли вершины посещены
        bool allused = true;
        for (int j = 0; j < n; j++) {
            if (!used[j]) {
                allused = false;
                break;
            }
        }

        if (allused) {
            versh.push_back(i);
        }
    }

    if (versh.empty()) {
        cout << "Нет ни одной вершины, из которой достижимы все остальные.\n";
    }
    else {
        cout << "Вершины: ";
        for (int v : versh){
            cout << v << " ";
        }
        cout << endl;
    }
}


int main() {
    setlocale(LC_ALL, "");

    n = 8;
    Gr.resize(n);
    used.resize(n, false);

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

    findall();
}
